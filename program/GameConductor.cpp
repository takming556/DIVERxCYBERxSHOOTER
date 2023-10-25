#include <memory>
#include <cmath>
#include <memory>
#include "DxLib.h"
#include "AppSession.h"
#include "GameConductor.h"
#include "Field.h"
#include "ResultOutput.h"
#include "Scenario/Scenario.h"
#include "Scenario/Stage1.h"
#include "Scenario/Stage2.h"
#include "Scenario/Stage3.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "ImageHandles.h"
#include "FontHandles.h"
#include "KeyPushFlags.h"
#include "DebugParams.h"
#include "Colors.h"
#include "Scoreboard.h"

using std::unique_ptr;
using std::make_unique;
using std::pow;

class Stage1;


Stage GameConductor::NOW_STAGE;
unique_ptr<Scenario> GameConductor::STAGE;
const unsigned int GameConductor::SURVIVAL_BONUS_RATE = 1000;
unsigned int GameConductor::SCORE = 0;	// publicにする？
double GameConductor::SURVIVAL_TIME = 0;
unsigned int GameConductor::SURVIVAL_TIME_SCORE = 0;
unsigned int GameConductor::TECHNICAL_SCORE = 0;
bool GameConductor::SURVIVAL_BONUS_ENABLE_FLAG = true;
int GameConductor::SURVIVAL_BONUS_LAST_ENABLED_CLOCK = 0;
bool GameConductor::FIELD_UPDATE_ENABLE_FLAG = true;
bool GameConductor::FIELD_UPDATE_STOP_REQUESTED_FLAG = false;
bool GameConductor::GAMEOVER_FLAG = false;
bool GameConductor::GAMECLEAR_FLAG = false;
bool GameConductor::STAGE1_CLEAR_FLAG = false;
bool GameConductor::STAGE2_CLEAR_FLAG = false;
bool GameConductor::STAGE3_CLEAR_FLAG = false;
vector<unique_ptr<NarrativePop>> GameConductor::NARRATIVE_POPS;


GameConductor::GameConductor() :
	scoreboard(make_unique<Scoreboard>()),
	game_started_clock(DxLib::GetNowCount()),
	game_time(0.0)
{
	GameConductor::INITIALIZE();
	Field::INITIALIZE();
	KeyPushFlags::INITIALIZE();
	//Offensive::INITIALIZE();
	Bullet::INITIALIZE();
	Laser::INITIALIZE();
	DebugParams::SURVIVAL_TIME = SURVIVAL_TIME;
	DebugParams::SURVIVAL_TIME_SCORE = SURVIVAL_TIME_SCORE;
}


GameConductor::~GameConductor() = default;


void GameConductor::INITIALIZE() {

	SCORE = 0;
	SURVIVAL_TIME = 0.0;
	NOW_STAGE = Stage::STAGE2;
	STAGE = make_unique<Stage2>();
	FIELD_UPDATE_ENABLE_FLAG = true;
	FIELD_UPDATE_STOP_REQUESTED_FLAG = false;
	TECHNICAL_SCORE = 0;
	SURVIVAL_TIME_SCORE = 0;
	SURVIVAL_BONUS_ENABLE_FLAG = true;
	SURVIVAL_BONUS_LAST_ENABLED_CLOCK = DxLib::GetNowCount();
	GAMEOVER_FLAG = false;
	GAMECLEAR_FLAG = false;
	STAGE1_CLEAR_FLAG = false;
	STAGE2_CLEAR_FLAG = false;
	STAGE3_CLEAR_FLAG = false;
	for (int i = 0; i < 256; i++) {
		AppSession::KEY_BUFFER[i] = NULL;
	}
	NARRATIVE_POPS.clear();
}


void GameConductor::update() {

	game_time = (double)(DxLib::GetNowCount() - game_started_clock) / 1000;
	DebugParams::GAME_TIME = game_time;

	//if (SURVIVAL_BONUS_ENABLE_FLAG == true) {
	//	SURVIVAL_TIME_SCORE = SURVIVAL_BONUS * game_time;
	//}

	FIELD_UPDATE_STOP_REQUESTED_FLAG = false;

	if ( GAMECLEAR_FLAG == false ) {
		switch ( NOW_STAGE ) {
		case Stage::STAGE1:
			if ( STAGE1_CLEAR_FLAG == true ) {
				NOW_STAGE = Stage::STAGE2;
				STAGE.reset(new Stage2);
			}
			break;

		case Stage::STAGE2:
			if ( STAGE2_CLEAR_FLAG == true ) {
				NOW_STAGE = Stage::STAGE3;
				STAGE.reset(new Stage3);
			}
			break;

		case Stage::STAGE3:
			if ( STAGE3_CLEAR_FLAG == true ) {
				GAMECLEAR_FLAG = true;
				DISABLE_SURVIVAL_BONUS();
				SCORE += pow(Field::MY_CHARACTER->hp , 2) * 100;
				ResultOutput::RESULT_OUTPUT();
			}
			break;

		default:
			break;
		}
	}

	if (GAMEOVER_FLAG == false) {
		if (Field::MY_CHARACTER->is_dead() == true) {
			GAMEOVER_FLAG = true;
			DISABLE_SURVIVAL_BONUS();
			Field::MY_BULLETS->clear();
			// ゲームオーバー時にリザルトを出力
			ResultOutput::RESULT_OUTPUT();
			
		}
	}

	Field::DRAW();


	STAGE->update();


	if (KeyPushFlags::Z == true && AppSession::KEY_BUFFER[ KEY_INPUT_Z ] == 0) {
		KeyPushFlags::Z = false;
	}


	if (NARRATIVE_POPS.empty() == true && FIELD_UPDATE_STOP_REQUESTED_FLAG == false) {
		ENABLE_SURVIVAL_BONUS();
		FIELD_UPDATE_ENABLE_FLAG = true;
	}
	else if (FIELD_UPDATE_STOP_REQUESTED_FLAG == true) {
		FIELD_UPDATE_ENABLE_FLAG = false;
	}
	else if (NARRATIVE_POPS.empty() == false) {
		DISABLE_SURVIVAL_BONUS();
		FIELD_UPDATE_ENABLE_FLAG = false;

		switch (NARRATIVE_POPS.at(0)->state) {
		case NarrativePopState::READY:
			NARRATIVE_POPS.at(0)->activate();
			break;

		case NarrativePopState::ROLLING:
			NARRATIVE_POPS.at(0)->draw();
			NARRATIVE_POPS.at(0)->update();
			break;

		case NarrativePopState::AWAITING:

			NARRATIVE_POPS.at(0)->draw();
			NARRATIVE_POPS.at(0)->update();

			if (KeyPushFlags::Z == false && AppSession::KEY_BUFFER[KEY_INPUT_Z] == 1) {
				KeyPushFlags::Z = true;
				NARRATIVE_POPS.erase(NARRATIVE_POPS.begin());
			}
			break;
		}

	}

	if (FIELD_UPDATE_ENABLE_FLAG == true) {
		Field::UPDATE();
	}
	Field::ERASE_BROKEN_OFFENSIVES();
	Field::DEAL_DEATHS();
	Field::ERASE_OUTSIDED_OBJECTS();
	Field::DEAL_COLLISION();
	


	if (KeyPushFlags::F4 == false && AppSession::KEY_BUFFER[KEY_INPUT_F4] == 1) {
		KeyPushFlags::F4 = true;
		GAMECLEAR_FLAG = true;
	}
	if (KeyPushFlags::F4 == true && AppSession::KEY_BUFFER[KEY_INPUT_F4] == 0) {
		KeyPushFlags::F4 = false;
	}

	if (KeyPushFlags::F5 == false && AppSession::KEY_BUFFER[ KEY_INPUT_F5 ] == 1) {
		KeyPushFlags::F5 = true;
		GAMEOVER_FLAG = true;
	}
	if (KeyPushFlags::F5 == true && AppSession::KEY_BUFFER[ KEY_INPUT_F5 ] == 0) {
		KeyPushFlags::F5 = false;
	}


	if (GAMEOVER_FLAG == true) {
		DxLib::DrawFormatStringToHandle(206, 200, Colors::RED, FontHandles::NAVIGATION_TEXT, L"GAME OVER");
		DxLib::DrawFormatStringToHandle(138, 600, Colors::RED, FontHandles::NAVIGATION_TEXT, L"PRESS SPACE KEY");
	}

	if (GAMECLEAR_FLAG == true) {
		DxLib::DrawFormatStringToHandle(194, 200, Colors::CYAN, FontHandles::NAVIGATION_TEXT, L"GAME CLEAR");
		DxLib::DrawFormatStringToHandle(138, 600, Colors::CYAN, FontHandles::NAVIGATION_TEXT, L"PRESS SPACE KEY");
	}


	DxLib::DrawGraph(0, 0, ImageHandles::SCREEN_BACKGROUND_CROPPED, TRUE);
	DxLib::DrawRotaGraph(850, 630, 0.4, 0, ImageHandles::LOGO, TRUE);
	SCORE = SURVIVAL_TIME_SCORE + TECHNICAL_SCORE;
	draw_score();
	draw_my_hp();
}


void GameConductor::draw_score() {
	DxLib::DrawFormatStringToHandle(720, 350, Colors::RED, FontHandles::SCOREBOARD_TEXT, L"SCORE");
	DxLib::DrawFormatStringToHandle(720, 384, Colors::RED, FontHandles::SCOREBOARD_VALUE, L"%08u", GameConductor::SCORE);
}


void GameConductor::draw_my_hp() {
	DxLib::DrawFormatStringToHandle(720, 150, Colors::YELLOW, FontHandles::SCOREBOARD_TEXT, L"LIFE");
	DxLib::DrawFormatStringToHandle(720, 190, Colors::YELLOW, FontHandles::SCOREBOARD_VALUE, L"%3d", Field::MY_CHARACTER->hp);
}


void GameConductor::ENABLE_SURVIVAL_BONUS() {
	if (SURVIVAL_BONUS_ENABLE_FLAG == false) {
		SURVIVAL_BONUS_LAST_ENABLED_CLOCK = DxLib::GetNowCount();
		SURVIVAL_BONUS_ENABLE_FLAG = true;
	}
}


void GameConductor::DISABLE_SURVIVAL_BONUS() {
	if (SURVIVAL_BONUS_ENABLE_FLAG == true) {
		SURVIVAL_TIME += (double)(DxLib::GetNowCount() - SURVIVAL_BONUS_LAST_ENABLED_CLOCK) / 1000;
		SURVIVAL_TIME_SCORE = SURVIVAL_TIME * SURVIVAL_BONUS_RATE;
		DebugParams::SURVIVAL_TIME = SURVIVAL_TIME;
		DebugParams::SURVIVAL_TIME_SCORE = SURVIVAL_TIME_SCORE;
		SURVIVAL_BONUS_ENABLE_FLAG = false;
	}
}


void GameConductor::REQUEST_FIELD_UPDATE_STOP() {
	FIELD_UPDATE_STOP_REQUESTED_FLAG = true;
}