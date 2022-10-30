#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include "DxLib.h"
#include "class.h"
#include "mysql/jdbc.h"

using std::make_unique;
using std::to_string;
using std::ofstream;
using std::cerr;
using std::endl;


AppSession::AppSession() :
	now_scene(Scene::TITLE),
	game_conductor(nullptr),
	nickname_input(nullptr),
	last_screenflipped_clock(1),		//0‚É‚æ‚éœŽZ‚ð–hŽ~‚·‚é‚½‚ßA‚ ‚¦‚Ä1‚Å‰Šú‰»
	clock_keeper_for_measure_fps(0),
	flip_count(0)
{
	SQLConfig::INITIALIZE();
}


void AppSession::update() {

	get_keyinput_state();
	respond_to_keyinput();

	switch (now_scene) {
	case Scene::TITLE:
		DxLib::DrawGraph(0, 0, ImageHandles::SCREEN_BACKGROUND, TRUE);
		DxLib::DrawRotaGraph(
			Screen::SCREEN_RESOLUTION_X / 2 + 237, 
			Screen::SCREEN_RESOLUTION_Y / 2, 
			0.19,
			0, 
			ImageHandles::ICHIGOCHAN_CONCEPTUAL, 
			TRUE
		);
		DxLib::DrawFormatStringToHandle(350, 650, Colors::MAZENTA, FontHandles::DSEG14, "PRESS Z TO DIVE");
		DxLib::DrawRotaGraph(
			Screen::SCREEN_RESOLUTION_X / 2 - 200,
			Screen::SCREEN_RESOLUTION_Y / 2 - 30, 
			0.65,
			0,
			ImageHandles::LOGO_NONSILHOUETTE,
			TRUE
		);
		break;
	case Scene::GAMING:
		game_conductor->update();
		if (game_conductor->GAMEOVER_FLAG == true || game_conductor->GAMECLEAR_FLAG == true) {
			if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_SPACE] == 1) {
				nickname_input.reset(new NicknameInput);
				now_scene = Scene::NICKNAMEINPUT;
			}
		}
		break;

	case Scene::NICKNAMEINPUT:
		nickname_input->update();
		nickname_input->draw();
		if (nickname_input->determined_flag == true) {
			send_sql(nickname_input->get());
			now_scene = Scene::TITLE;
		}
		break;

	case Scene::RESULT:
		break;

	case Scene::RANKING:
		break;

	}

	if (DebugParams::DEBUG_FLAG == true) DebugParams::DRAW();

	LONGLONG now_clock = DxLib::GetNowHiPerformanceCount();
	DebugParams::SLEEP_TIME = (last_screenflipped_clock + ((1.0 / SettingParams::LIMIT_FPS) * 1000 * 1000) - now_clock) / 1000;
	DxLib::WaitTimer(DebugParams::SLEEP_TIME);

	LONGLONG screenflip_postpone_time = 1.0 / SettingParams::LIMIT_FPS * 1000 * 1000;
	if (now_clock > last_screenflipped_clock + screenflip_postpone_time) {
		DxLib::ScreenFlip();		//— ‰æ–Ê‚Ì“à—e‚ð•\‰æ–Ê‚É”½‰f
		DxLib::ClearDrawScreen();	//— ‰æ–Ê‚ðƒNƒŠƒA
		LONGLONG delta_time = now_clock - last_screenflipped_clock;
		DebugParams::INSTANT_FPS = 1.0 * 1000 * 1000 / delta_time;
		flip_count++;
		last_screenflipped_clock = DxLib::GetNowHiPerformanceCount();
	}

	if (DxLib::GetNowCount() > clock_keeper_for_measure_fps + 1000) {
		DebugParams::ACTUAL_FPS = flip_count;
		flip_count = 0;
		clock_keeper_for_measure_fps = DxLib::GetNowCount();
	}
}


void AppSession::get_keyinput_state() {
	DxLib::GetHitKeyStateAll(KeyPushFlags::KEY_BUFFER);
}


void AppSession::respond_to_keyinput() {

	if (KeyPushFlags::F3 == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_F3] == 1) {
		KeyPushFlags::F3 = true;
		DebugParams::DEBUG_FLAG = !(DebugParams::DEBUG_FLAG);
	}
	if (KeyPushFlags::F3 == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_F3] == 0) {
		KeyPushFlags::F3 = false;
	}

	switch (now_scene) {
	case Scene::TITLE:
		if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_Z] == 1) {
			now_scene = Scene::GAMING;
			DxLib::PlaySoundMem(SoundHandles::FORWARD, DX_PLAYTYPE_NORMAL);
		}
		GameConductor::INITIALIZE();
		game_conductor.reset(new GameConductor);
		DebugParams::GAME_TIME = 0;
		break;
	}
}


int AppSession::send_sql(string nickname) {
	try {
		//unique_ptr<sql::mysql::MySQL_Driver> driver;
		//driver.reset(sql::mysql::get_mysql_driver_instance());
		sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
		unique_ptr<sql::Connection> con(driver->connect(SQLConfig::HOST, SQLConfig::USER, SQLConfig::PASSWORD));
		unique_ptr<sql::Statement> stmt(con->createStatement());
		stmt->execute("USE " + SQLConfig::DATABASE + ";");
		stmt->execute("INSERT INTO ranking (nickname, score, sent_from) VALUES (\'" + nickname + "\', " + to_string(GameConductor::SCORE) + ", \'" + SQLConfig::USER + "\');");
	}
	catch (sql::SQLException& e) {
		cerr << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << endl;
		cerr << "# ERR: " << e.what() << endl;
		cerr << "(MySQL error code: " << e.getErrorCode();
		cerr << ", SQLState: " << e.getSQLState() << " )" << endl;

		ofstream fs_log(SQLConfig::FILENAME_LOG);
		fs_log << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << endl;
		fs_log << "# ERR: " << e.what() << endl;
		fs_log << "(MySQL error code: " << e.getErrorCode();
		fs_log << ", SQLState: " << e.getSQLState() << " )" << endl;
		fs_log.close();
		return EXIT_FAILURE;
	}
	catch (std::runtime_error& e) {
		cerr << "# ERR: runtime_error in " << __FILE__ << " on line " << __LINE__ << endl;
		cerr << "# ERR: " << e.what() << endl;

		ofstream fs_log(SQLConfig::FILENAME_LOG);
		fs_log << "# ERR: runtime_error in " << __FILE__ << " on line " << __LINE__ << endl;
		fs_log << "# ERR: " << e.what() << endl;
		fs_log.close();
		return EXIT_FAILURE;
	}
}