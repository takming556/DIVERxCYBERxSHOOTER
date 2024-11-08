#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include "DxLib.h"
#include "AppSession.h"
#include "GameConductor.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "FontHandles.h"
#include "KeyPushFlags.h"
#include "DebugParams.h"
#include "SettingParams.h"
//#include "NicknameInput.h"
#include "Screen/Screen.h"
#include "Colors.h"

using std::make_unique;
using std::to_string;
using std::ofstream;
using std::cerr;
using std::endl;
using std::stoi;

class GameConductor;

char AppSession::KEY_BUFFER[256];
bool AppSession::WINDOW_CLOSE_FLAG = false;

void AppSession::INITIALIZE() {
	for (int i = 0; i < 256; i++) {
		KEY_BUFFER[i] = NULL;
	}
}


AppSession::AppSession() :
	now_scene(Scene::TITLE),
	now_title_scene_state(TitleSceneState::INIT),
	now_main_menu_cursor_pos(MainMenuCursorPos::GAME_START),
	now_main_menu_practice_cursor_pos(MainMenuPracticeCursorPos::FROM_STAGE1),
	practice_selected_flag(false),
	game_conductor(nullptr),
	//nickname_input(nullptr),
	last_screenflipped_clock(1),		//0による除算を防止するため、あえて1で初期化
	clock_keeper_for_measure_fps(0),
	flip_count(0)
{
	//SQLConfig::INITIALIZE();
}


void AppSession::update() {

	get_keyinput_state();
	respond_to_keyinput();

	switch (now_scene) {
	case Scene::TITLE:
		DxLib::DrawGraph(0, 0, ImageHandles::SCREEN_BACKGROUND, TRUE);
		switch (now_title_scene_state)
		{
		case TitleSceneState::INIT:
			DxLib::DrawRotaGraph(
				Screen::SCREEN_RESOLUTION_X / 2 + 237,
				Screen::SCREEN_RESOLUTION_Y / 2,
				0.19,
				0,
				ImageHandles::ICHIGOCHAN_CONCEPTUAL,
				TRUE
			);
			DxLib::DrawFormatStringToHandle(300, 650, Colors::YELLOW, FontHandles::NAVIGATION_TEXT, L"PRESS Z TO DIVE");
			DxLib::DrawRotaGraph(
				Screen::SCREEN_RESOLUTION_X / 2 - 200,
				Screen::SCREEN_RESOLUTION_Y / 2 - 30,
				0.65,
				0,
				ImageHandles::LOGO_NONSILHOUETTE,
				TRUE
			);
			break;
		case TitleSceneState::SELECTABLE:
		{
			int menu_text_x = 100;
			int menu_text_y = 350;
			DxLib::DrawFormatStringToHandle(menu_text_x, menu_text_y += 50, Colors::YELLOW, FontHandles::MAIN_MENU_TEXT, L"GAME START");
			DxLib::DrawFormatStringToHandle(menu_text_x, menu_text_y += 50, Colors::YELLOW, FontHandles::MAIN_MENU_TEXT, L"PRACTICE");
			DxLib::DrawFormatStringToHandle(menu_text_x, menu_text_y += 50, Colors::YELLOW, FontHandles::MAIN_MENU_TEXT, L"GALLERY");
			DxLib::DrawFormatStringToHandle(menu_text_x, menu_text_y += 50, Colors::YELLOW, FontHandles::MAIN_MENU_TEXT, L"CREDIT");
			DxLib::DrawFormatStringToHandle(menu_text_x, menu_text_y += 50, Colors::YELLOW, FontHandles::MAIN_MENU_TEXT, L"CONFIG");
			DxLib::DrawFormatStringToHandle(menu_text_x, menu_text_y += 50, Colors::YELLOW, FontHandles::MAIN_MENU_TEXT, L"EXIT");
			switch (now_main_menu_cursor_pos)
			{
			case MainMenuCursorPos::GAME_START:
				DxLib::DrawFormatStringToHandle(menu_text_x, 400, Colors::RED, FontHandles::MAIN_MENU_TEXT, L"GAME START");
				break;
			case MainMenuCursorPos::PRACTICE:
				DxLib::DrawFormatStringToHandle(menu_text_x, 450, Colors::RED, FontHandles::MAIN_MENU_TEXT, L"PRACTICE");
				if (practice_selected_flag == true) {
					int x = 300;
					int y = 400;
					DxLib::DrawFormatStringToHandle(x, y += 50, Colors::YELLOW, FontHandles::MAIN_MENU_TEXT, L"FROM STAGE1");
					DxLib::DrawFormatStringToHandle(x, y += 50, Colors::YELLOW, FontHandles::MAIN_MENU_TEXT, L"FROM STAGE2");
					DxLib::DrawFormatStringToHandle(x, y += 50, Colors::YELLOW, FontHandles::MAIN_MENU_TEXT, L"FROM STAGE3");
					switch (now_main_menu_practice_cursor_pos)
					{
					case MainMenuPracticeCursorPos::FROM_STAGE1:
						DxLib::DrawFormatStringToHandle(x, 450, Colors::RED, FontHandles::MAIN_MENU_TEXT, L"FROM STAGE1");
						break;
					case MainMenuPracticeCursorPos::FROM_STAGE2:
						DxLib::DrawFormatStringToHandle(x, 500, Colors::RED, FontHandles::MAIN_MENU_TEXT, L"FROM STAGE2");
						break;
					case MainMenuPracticeCursorPos::FROM_STAGE3:
						DxLib::DrawFormatStringToHandle(x, 550, Colors::RED, FontHandles::MAIN_MENU_TEXT, L"FROM STAGE3");
						break;
					default:
						break;
					}
				}
				break;
			case MainMenuCursorPos::GALLERY:
				DxLib::DrawFormatStringToHandle(menu_text_x, 500, Colors::RED, FontHandles::MAIN_MENU_TEXT, L"GALLERY");
				break;
			case MainMenuCursorPos::CREDIT:
				DxLib::DrawFormatStringToHandle(menu_text_x, 550, Colors::RED, FontHandles::MAIN_MENU_TEXT, L"CREDIT");
				break;
			case MainMenuCursorPos::CONFIG:
				DxLib::DrawFormatStringToHandle(menu_text_x, 600, Colors::RED, FontHandles::MAIN_MENU_TEXT, L"CONFIG");
				break;
			case MainMenuCursorPos::EXIT:
				DxLib::DrawFormatStringToHandle(menu_text_x, 650, Colors::RED, FontHandles::MAIN_MENU_TEXT, L"EXIT");
				break;
			default:
				break;
			}
			DxLib::DrawRotaGraph(
				Screen::SCREEN_RESOLUTION_X / 2 + 237,
				Screen::SCREEN_RESOLUTION_Y / 2,
				0.19,
				0,
				ImageHandles::ICHIGOCHAN_CONCEPTUAL,
				TRUE
			);
			DxLib::DrawRotaGraph(
				Screen::SCREEN_RESOLUTION_X / 2 - 250,
				Screen::SCREEN_RESOLUTION_Y / 4,
				0.45,
				0,
				ImageHandles::LOGO_NONSILHOUETTE,
				TRUE
			);

			break;
		}
		default:
			break;
		}
		break;
	case Scene::GAMING:
		game_conductor->update();
		if (game_conductor->GAMEOVER_FLAG == true || game_conductor->GAMECLEAR_FLAG == true) {
			if (AppSession::KEY_BUFFER[KEY_INPUT_SPACE] == 1) {
				//nickname_input.reset(new NicknameInput);
				DxLib::StopSoundMem(SoundHandles::STAGE1BGM);
				DxLib::StopSoundMem(SoundHandles::STAGE2BGM);
				DxLib::StopSoundMem(SoundHandles::STAGE3BGM);
				now_scene = Scene::TITLE;
				now_title_scene_state = TitleSceneState::INIT;
				now_main_menu_cursor_pos = MainMenuCursorPos::GAME_START;
				now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE1;
			}
		}
		break;

	//case Scene::NICKNAMEINPUT:
	//	nickname_input->update();
	//	nickname_input->draw();
	//	if (nickname_input->determined_flag == true) {
	//		send_sql(nickname_input->get());
	//		//output_playlog(nickname_input->get());
	//		now_scene = Scene::TITLE;
	//	}
	//	break;

	case Scene::RESULT:
		break;

	case Scene::RANKING:
		break;

	}

	if (DebugParams::DEBUG_FLAG == true) DebugParams::DRAW();

	LONGLONG now_clock = DxLib::GetNowHiPerformanceCount();
	//DebugParams::SLEEP_TIME = (last_screenflipped_clock + ((1.0 / SettingParams::LIMIT_FPS) * 1000 * 1000) - now_clock) / 1000;
	//DxLib::WaitTimer(DebugParams::SLEEP_TIME);

	LONGLONG screenflip_postpone_time = 1.0 / SettingParams::LIMIT_FPS * 1000 * 1000;
	if (now_clock > last_screenflipped_clock + screenflip_postpone_time) {
		DxLib::ScreenFlip();		//裏画面の内容を表画面に反映
		DxLib::ClearDrawScreen();	//裏画面をクリア
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
	DxLib::GetHitKeyStateAll(AppSession::KEY_BUFFER);
}


void AppSession::respond_to_keyinput() {

	if (KeyPushFlags::F3 == false && AppSession::KEY_BUFFER[KEY_INPUT_F3] == 1) {
		KeyPushFlags::F3 = true;
		DebugParams::DEBUG_FLAG = !(DebugParams::DEBUG_FLAG);
	}
	if (KeyPushFlags::F3 == true && AppSession::KEY_BUFFER[KEY_INPUT_F3] == 0) {
		KeyPushFlags::F3 = false;
	}

	switch (now_scene) 
	{
	case Scene::TITLE:
		switch (now_title_scene_state)
		{
		case TitleSceneState::INIT:
			if (AppSession::KEY_BUFFER[ KEY_INPUT_Z ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
				now_title_scene_state = TitleSceneState::SELECTABLE;
				DxLib::PlaySoundMem(SoundHandles::FORWARD, DX_PLAYTYPE_NORMAL);
			}
			break;
		case TitleSceneState::SELECTABLE:
			switch (now_main_menu_cursor_pos)
			{
			case MainMenuCursorPos::GAME_START:
				if (AppSession::KEY_BUFFER[ KEY_INPUT_Z ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					now_scene = Scene::GAMING;
					DxLib::PlaySoundMem(SoundHandles::FORWARD, DX_PLAYTYPE_NORMAL);
					game_conductor.reset(new GameConductor);
					GameConductor::INITIALIZE(Stage::STAGE1, false);
					DebugParams::GAME_TIME = 0;
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_X ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
					now_title_scene_state = TitleSceneState::INIT;
					DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_NORMAL);
					now_main_menu_cursor_pos = MainMenuCursorPos::GAME_START;
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
					now_main_menu_cursor_pos = MainMenuCursorPos::EXIT;
					DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
					now_main_menu_cursor_pos = MainMenuCursorPos::PRACTICE;
					DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
				}
				break;
			case MainMenuCursorPos::PRACTICE:
				if (practice_selected_flag == false) {
					if (AppSession::KEY_BUFFER[ KEY_INPUT_Z ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						practice_selected_flag = true;
						DxLib::PlaySoundMem(SoundHandles::FORWARD, DX_PLAYTYPE_NORMAL);
						now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE1;
					}
					if (AppSession::KEY_BUFFER[ KEY_INPUT_X ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
						now_title_scene_state = TitleSceneState::INIT;
						DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_NORMAL);
						now_main_menu_cursor_pos = MainMenuCursorPos::GAME_START;
					}
					if (AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
						now_main_menu_cursor_pos = MainMenuCursorPos::GAME_START;
						DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
					}
					if (AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
						now_main_menu_cursor_pos = MainMenuCursorPos::GALLERY;
						DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
					}
				}
				else
				{
					switch (now_main_menu_practice_cursor_pos)
					{
					case MainMenuPracticeCursorPos::FROM_STAGE1:
						if (AppSession::KEY_BUFFER[ KEY_INPUT_Z ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
							now_scene = Scene::GAMING;
							DxLib::PlaySoundMem(SoundHandles::FORWARD, DX_PLAYTYPE_NORMAL);
							game_conductor.reset(new GameConductor);
							GameConductor::INITIALIZE(Stage::STAGE1, true);
							DebugParams::GAME_TIME = 0;
							now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE1;
							practice_selected_flag = false;
						}
						if (AppSession::KEY_BUFFER[ KEY_INPUT_X ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
							practice_selected_flag = false;
							DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_NORMAL);
						}
						if (AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
							now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE3;
							DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
						}
						if (AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
							now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE2;
							DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
						}
						break;
					case MainMenuPracticeCursorPos::FROM_STAGE2:
						if (AppSession::KEY_BUFFER[ KEY_INPUT_Z ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
							now_scene = Scene::GAMING;
							DxLib::PlaySoundMem(SoundHandles::FORWARD, DX_PLAYTYPE_NORMAL);
							game_conductor.reset(new GameConductor);
							GameConductor::INITIALIZE(Stage::STAGE2, true);
							DebugParams::GAME_TIME = 0;
							now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE1;
							practice_selected_flag = false;
						}
						if (AppSession::KEY_BUFFER[ KEY_INPUT_X ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
							practice_selected_flag = false;
							DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_NORMAL);
						}
						if (AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
							now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE1;
							DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
						}
						if (AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
							now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE3;
							DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
						}
						break;
					case MainMenuPracticeCursorPos::FROM_STAGE3:
						if (AppSession::KEY_BUFFER[ KEY_INPUT_Z ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
							now_scene = Scene::GAMING;
							DxLib::PlaySoundMem(SoundHandles::FORWARD, DX_PLAYTYPE_NORMAL);
							game_conductor.reset(new GameConductor);
							GameConductor::INITIALIZE(Stage::STAGE3, true);
							DebugParams::GAME_TIME = 0;
							now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE1;
							practice_selected_flag = false;
						}
						if (AppSession::KEY_BUFFER[ KEY_INPUT_X ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
							practice_selected_flag = false;
							DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_NORMAL);
						}
						if (AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
							now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE2;
							DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
						}
						if (AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
							now_main_menu_practice_cursor_pos = MainMenuPracticeCursorPos::FROM_STAGE1;
							DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
						}
						break;
					default:
						break;
					}
				}
				break;
			case MainMenuCursorPos::GALLERY:
				if (AppSession::KEY_BUFFER[ KEY_INPUT_X ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
					now_title_scene_state = TitleSceneState::INIT;
					DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_NORMAL);
					now_main_menu_cursor_pos = MainMenuCursorPos::GAME_START;
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
					now_main_menu_cursor_pos = MainMenuCursorPos::PRACTICE;
					DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
					now_main_menu_cursor_pos = MainMenuCursorPos::CREDIT;
					DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
				}
				break;
			case MainMenuCursorPos::CREDIT:
				if (AppSession::KEY_BUFFER[ KEY_INPUT_X ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
					now_title_scene_state = TitleSceneState::INIT;
					DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_NORMAL);
					now_main_menu_cursor_pos = MainMenuCursorPos::GAME_START;
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
					now_main_menu_cursor_pos = MainMenuCursorPos::GALLERY;
					DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
					now_main_menu_cursor_pos = MainMenuCursorPos::CONFIG;
					DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
				}
				break;
			case MainMenuCursorPos::CONFIG:
				if (AppSession::KEY_BUFFER[ KEY_INPUT_X ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
					now_title_scene_state = TitleSceneState::INIT;
					DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_NORMAL);
					now_main_menu_cursor_pos = MainMenuCursorPos::GAME_START;
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
					now_main_menu_cursor_pos = MainMenuCursorPos::CREDIT;
					DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
					now_main_menu_cursor_pos = MainMenuCursorPos::EXIT;
					DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
				}
				break;
			case MainMenuCursorPos::EXIT:
				if (AppSession::KEY_BUFFER[ KEY_INPUT_Z ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					WINDOW_CLOSE_FLAG = true;
					DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_NORMAL);
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_X ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
					now_title_scene_state = TitleSceneState::INIT;
					DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_NORMAL);
					now_main_menu_cursor_pos = MainMenuCursorPos::GAME_START;
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
					now_main_menu_cursor_pos = MainMenuCursorPos::CONFIG;
					DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
				}
				if (AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 1 || (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
					now_main_menu_cursor_pos = MainMenuCursorPos::GAME_START;
					DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_NORMAL);
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	}
}


//int AppSession::send_sql(wstring nickname) {
//	try {
//		//unique_ptr<sql::mysql::MySQL_Driver> driver;
//		//driver.reset(sql::mysql::get_mysql_driver_instance());
//		sql::ConnectOptionsMap connection_properties;
//		connection_properties["hostName"] = SQLConfig::HOST;
//		connection_properties["userName"] = SQLConfig::USER;
//		connection_properties["password"] = SQLConfig::PASSWORD;
//		connection_properties["port"] = stoi(SQLConfig::PORT);
//		//connection_properties["OPT_SSL_MODE"] = sql::SSL_MODE_DISABLED;
//
//		sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
//		//unique_ptr<sql::Connection> con(driver->connect(SQLConfig::HOST, SQLConfig::USER, SQLConfig::PASSWORD));
//		unique_ptr<sql::Connection> con(driver->connect(connection_properties));
//		unique_ptr<sql::Statement> stmt(con->createStatement());
//		stmt->execute("USE " + SQLConfig::DATABASE + ";");
//		stmt->execute("INSERT INTO " + SQLConfig::TABLE + " (nickname, score, device) VALUES(\'" + nickname + "\', " + to_string(GameConductor::SCORE) + ", \'" + SQLConfig::DEVICE + "\');");
//	}
//	catch (sql::SQLException& e) {
//		cerr << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << endl;
//		cerr << "# ERR: " << e.what() << endl;
//		cerr << "(MySQL error code: " << e.getErrorCode();
//		cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
//
//		ofstream fs_log(SQLConfig::FILENAME_LOG);
//		fs_log << "# ERR: SQLException in " << __FILE__ << " on line " << __LINE__ << endl;
//		fs_log << "# ERR: " << e.what() << endl;
//		fs_log << "(MySQL error code: " << e.getErrorCode();
//		fs_log << ", SQLState: " << e.getSQLState() << " )" << endl;
//		fs_log.close();
//		return EXIT_FAILURE;
//	}
//	catch (std::runtime_error& e) {
//		cerr << "# ERR: runtime_error in " << __FILE__ << " on line " << __LINE__ << endl;
//		cerr << "# ERR: " << e.what() << endl;
//
//		ofstream fs_log(SQLConfig::FILENAME_LOG);
//		fs_log << "# ERR: runtime_error in " << __FILE__ << " on line " << __LINE__ << endl;
//		fs_log << "# ERR: " << e.what() << endl;
//		fs_log.close();
//		return EXIT_FAILURE;
//	}
//}


//void AppSession::output_playlog(wstring nickname) {
//	DATEDATA* datedata;
//	DxLib::GetDateTime(datedata);
//
//	char yearchar[5];
//	char monchar[3];
//	char daychar[3];
//	char hourchar[3];
//	char minchar[3];
//	char secchar[3];
//	sprintf_s(yearchar, "%04d", datedata->Year);
//	sprintf_s(monchar, "%02d", datedata->Mon);
//	sprintf_s(daychar, "%02d", datedata->Day);
//	sprintf_s(hourchar, "%02d", datedata->Hour);
//	sprintf_s(minchar, "%02d", datedata->Min);
//	sprintf_s(secchar, "%02d", datedata->Sec);
//	wstring yearstr = yearchar;
//	wstring monstr = monchar;
//	wstring daystr = daychar;
//	wstring hourstr = hourchar;
//	wstring minstr = minchar;
//	wstring secstr = secchar;
//	wstring datestr = yearstr + "-" + monstr + "-" + daystr + "_" + hourstr + "-" + minstr + "-" + secstr + ".txt";
//	ofstream fs_playlog;
//	fs_playlog.open(datestr);
//	fs_playlog << nickname << endl;
//	fs_playlog << GameConductor::SCORE << endl;
//	if (GameConductor::GAMEOVER_FLAG == true) {
//		fs_playlog << 0 << endl;
//	}
//	else {
//		fs_playlog << Field::MY_CHARACTER->life << endl;
//	}
//	fs_playlog << datestr << endl;
//	fs_playlog << SQLConfig::DEVICE << endl;
//}