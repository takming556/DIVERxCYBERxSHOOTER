#include <memory>
#include <cmath>
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
#include "Effect/CrashEffect/CrashEffect.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "FontHandles.h"
#include "KeyPushFlags.h"
#include "DebugParams.h"
#include "Colors.h"
#include "Scoreboard.h"

using std::unique_ptr;
using std::make_unique;
using std::pow;

class Stage1;


Stage GameConductor::CURRENT_STAGE;
unique_ptr<Scenario> GameConductor::STAGE;
const unsigned int GameConductor::SURVIVAL_BONUS_RATE = 1000;
unsigned int GameConductor::SCORE = 0;	// publicにする？
double GameConductor::SURVIVAL_TIME = 0;
unsigned int GameConductor::SURVIVAL_TIME_SCORE = 0;
unsigned int GameConductor::TECHNICAL_SCORE = 0;
bool GameConductor::IS_SURVIVAL_BONUS_ENABLED = true;
int GameConductor::SURVIVAL_BONUS_LAST_ENABLED_CLOCK = 0;
unsigned int GameConductor::CONTINUE_COUNT = 0;
unsigned int GameConductor::MAX_CONTINUE_COUNT = 5;
bool GameConductor::IS_PRACTICE_MODE_ENABLED = false;
bool GameConductor::IS_FIELD_UPDATE_ENABLED = true;
bool GameConductor::IS_FIELD_UPDATE_STOP_REQUESTED = false;
bool GameConductor::GAMEOVER_FLAG = false;
bool GameConductor::GAMECLEAR_FLAG = false;
bool GameConductor::STAGE1_CLEAR_FLAG = false;
bool GameConductor::STAGE2_CLEAR_FLAG = false;
bool GameConductor::STAGE3_CLEAR_FLAG = false;
vector<unique_ptr<NarrativePop>> GameConductor::NARRATIVE_POPS;


GameConductor::GameConductor() :
	scoreboard(make_unique<Scoreboard>()),
	gameStartedClock(DxLib::GetNowCount()),
	gameTime(0.0)
{
	GameConductor::INITIALIZE(Stage::STAGE1, false);
	Field::INITIALIZE();
	KeyPushFlags::INITIALIZE();
	//Offensive::INITIALIZE();
	Bullet::INITIALIZE();
	LaserAreaNotice::INITIALIZE();
	Laser::INITIALIZE();
	DebugParams::SURVIVAL_TIME = SURVIVAL_TIME;
	DebugParams::SURVIVAL_TIME_SCORE = SURVIVAL_TIME_SCORE;
}


GameConductor::~GameConductor() = default;


void GameConductor::INITIALIZE(Stage start_from, bool is_practice_mode) {
	switch (start_from)
	{
	case Stage::STAGE1:
		CURRENT_STAGE = Stage::STAGE1;
		STAGE = make_unique<Stage1>();
		break;
	case Stage::STAGE2:
		CURRENT_STAGE = Stage::STAGE2;
		STAGE = make_unique<Stage2>();
		break;
	case Stage::STAGE3:
		CURRENT_STAGE = Stage::STAGE3;
		STAGE = make_unique<Stage3>();
		break;
	default:
		CURRENT_STAGE = Stage::STAGE1;
		STAGE = make_unique<Stage1>();
		break;
	}

	IS_PRACTICE_MODE_ENABLED = is_practice_mode;

	SCORE = 0;
	SURVIVAL_TIME = 0.0;
	IS_FIELD_UPDATE_ENABLED = true;
	IS_FIELD_UPDATE_STOP_REQUESTED = false;
	TECHNICAL_SCORE = 0;
	SURVIVAL_TIME_SCORE = 0;
	IS_SURVIVAL_BONUS_ENABLED = true;
	SURVIVAL_BONUS_LAST_ENABLED_CLOCK = DxLib::GetNowCount();
	CONTINUE_COUNT = 0;
	GAMEOVER_FLAG = false;
	GAMECLEAR_FLAG = false;
	STAGE1_CLEAR_FLAG = false;
	STAGE2_CLEAR_FLAG = false;
	STAGE3_CLEAR_FLAG = false;
	MyCharacter::LAUNCH_SUSPENDED_FLAG = false;
	for (int i = 0; i < 256; i++) {
		AppSession::KBD_BUFFER[i] = NULL;
	}
	AppSession::PAD_BUFFER = 0x00000000;
	NARRATIVE_POPS.clear();
}


void GameConductor::Update() {

	gameTime = (double)(DxLib::GetNowCount() - gameStartedClock) / 1000;
	DebugParams::GAME_TIME = gameTime;

	//if (IS_SURVIVAL_BONUS_ENABLED == true) {
	//	SURVIVAL_TIME_SCORE = SURVIVAL_BONUS * gameTime;
	//}

	IS_FIELD_UPDATE_STOP_REQUESTED = false;

	if ( GAMECLEAR_FLAG == false ) {
		switch ( CURRENT_STAGE ) {
		case Stage::STAGE1:
			if ( STAGE1_CLEAR_FLAG == true ) {
				CURRENT_STAGE = Stage::STAGE2;
				STAGE.reset(new Stage2);
			}
			break;

		case Stage::STAGE2:
			if ( STAGE2_CLEAR_FLAG == true ) {
				CURRENT_STAGE = Stage::STAGE3;
				STAGE.reset(new Stage3);
			}
			break;

		case Stage::STAGE3:
			if ( STAGE3_CLEAR_FLAG == true ) {
				GAMECLEAR_FLAG = true;
				DISABLE_SURVIVAL_BONUS();
				SCORE += pow(Field::MY_CHARACTER->hp , 2) * 5000;
				SCORE += SURVIVAL_TIME_SCORE;
				ResultOutput::RESULT_OUTPUT();
			}
			break;

		default:
			break;
		}
	}

	if (GAMEOVER_FLAG == false) {
		if (Field::MY_CHARACTER->IsDead() == true) {
			Field::MY_CHARACTER->Crash();
			if (IS_PRACTICE_MODE_ENABLED == false) {
				// コンティニュー処理
				if (CONTINUE_COUNT >= MAX_CONTINUE_COUNT) {
					// ゲームオーバー
					GAMEOVER_FLAG = true;
					DISABLE_SURVIVAL_BONUS();
					SCORE += SURVIVAL_TIME_SCORE;
					Field::MY_BULLETS->clear();
					ResultOutput::RESULT_OUTPUT();
				}
				else {
					// 自動コンティニュー処理
					Field::MY_CHARACTER->hp = 100;
					RESET_SCORE();
					CONTINUE_COUNT += 1;
				}
			}
			else { // PRACTICEモード時
				// ゲームオーバー
				GAMEOVER_FLAG = true;
				DISABLE_SURVIVAL_BONUS();
				SCORE += SURVIVAL_TIME_SCORE;
				Field::MY_BULLETS->clear();
				// ResultOutput::RESULT_OUTPUT();
			}
		}
	}


	Field::DRAW();


	STAGE->update();


	if (KeyPushFlags::INPUT_1 == true && ((DxLib::GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1) == 0)) {
		KeyPushFlags::INPUT_1 = false;
	}


	if (NARRATIVE_POPS.empty() == true && IS_FIELD_UPDATE_STOP_REQUESTED == false) {
		ENABLE_SURVIVAL_BONUS();
		IS_FIELD_UPDATE_ENABLED = true;
	}
	else if (IS_FIELD_UPDATE_STOP_REQUESTED == true) {
		IS_FIELD_UPDATE_ENABLED = false;
	}
	else if (NARRATIVE_POPS.empty() == false) {
		DISABLE_SURVIVAL_BONUS();
		IS_FIELD_UPDATE_ENABLED = false;

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

			if (KeyPushFlags::INPUT_1 == false && ((DxLib::GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1) != 0)) {
				KeyPushFlags::INPUT_1 = true;
				NARRATIVE_POPS.erase(NARRATIVE_POPS.begin());
			}
			break;
		}

	}

	if (IS_FIELD_UPDATE_ENABLED == true) {
		Field::UPDATE();
	}
	Field::ERASE_BROKEN_OFFENSIVES();
	Field::DEAL_DEATHS();
	Field::ERASE_OUTSIDED_OBJECTS();
	Field::ERASE_EXPIRED_EFFECTS();
	Field::DEAL_COLLISION();
	


	if (KeyPushFlags::F4 == false && AppSession::KBD_BUFFER[KEY_INPUT_F4] == 1) {
		KeyPushFlags::F4 = true;
		GAMECLEAR_FLAG = true;
	}
	if (KeyPushFlags::F4 == true && AppSession::KBD_BUFFER[KEY_INPUT_F4] == 0) {
		KeyPushFlags::F4 = false;
	}

	if (KeyPushFlags::F5 == false && AppSession::KBD_BUFFER[ KEY_INPUT_F5 ] == 1) {
		KeyPushFlags::F5 = true;
		GAMEOVER_FLAG = true;
	}
	if (KeyPushFlags::F5 == true && AppSession::KBD_BUFFER[ KEY_INPUT_F5 ] == 0) {
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
	SCORE = TECHNICAL_SCORE;
	DrawScore();
	DrawMyHp();
	if (IS_PRACTICE_MODE_ENABLED == false) {
		DrawContinueCount();
	}
}


void GameConductor::DrawScore() {
	DxLib::DrawFormatStringToHandle(720, 350, Colors::RED, FontHandles::SCOREBOARD_TEXT, L"SCORE");
	DxLib::DrawFormatStringToHandle(720, 384, Colors::RED, FontHandles::SCOREBOARD_VALUE, L"%08u", GameConductor::SCORE);
}


void GameConductor::DrawMyHp() {
	DxLib::DrawFormatStringToHandle(720, 150, Colors::YELLOW, FontHandles::SCOREBOARD_TEXT, L"LIFE");
	DxLib::DrawFormatStringToHandle(720, 190, Colors::YELLOW, FontHandles::SCOREBOARD_VALUE, L"%3d", Field::MY_CHARACTER->hp);
}

void GameConductor::DrawContinueCount(){
	DxLib::DrawFormatStringToHandle(720, 250, Colors::YELLOW, FontHandles::SCOREBOARD_TEXT, L"CONTINUE");
	DxLib::DrawFormatStringToHandle(730, 290, Colors::YELLOW, FontHandles::SCOREBOARD_VALUE, L"%1d/%1d", CONTINUE_COUNT, MAX_CONTINUE_COUNT);
}


void GameConductor::ENABLE_SURVIVAL_BONUS() {
	if (IS_SURVIVAL_BONUS_ENABLED == false) {
		SURVIVAL_BONUS_LAST_ENABLED_CLOCK = DxLib::GetNowCount();
		IS_SURVIVAL_BONUS_ENABLED = true;
	}
}


void GameConductor::DISABLE_SURVIVAL_BONUS() {
	if (IS_SURVIVAL_BONUS_ENABLED == true) {
		SURVIVAL_TIME += (double)(DxLib::GetNowCount() - SURVIVAL_BONUS_LAST_ENABLED_CLOCK) / 1000;
		SURVIVAL_TIME_SCORE = SURVIVAL_TIME * SURVIVAL_BONUS_RATE;
		DebugParams::SURVIVAL_TIME = SURVIVAL_TIME;
		DebugParams::SURVIVAL_TIME_SCORE = SURVIVAL_TIME_SCORE;
		IS_SURVIVAL_BONUS_ENABLED = false;
	}
}

void GameConductor::RESET_SCORE() {
	SCORE = 0;
	SURVIVAL_TIME = 0.0;
	SURVIVAL_TIME_SCORE = 0;
	TECHNICAL_SCORE = 0;
	DISABLE_SURVIVAL_BONUS();
	ENABLE_SURVIVAL_BONUS();
}

void GameConductor::REQUEST_FIELD_UPDATE_STOP() {
	IS_FIELD_UPDATE_STOP_REQUESTED = true;
}