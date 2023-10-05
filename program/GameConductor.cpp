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
#include "ImageHandles.h"
#include "FontHandles.h"
#include "KeyPushFlags.h"
#include "DebugParams.h"
#include "Colors.h"
#include "Scoreboard.h"

using std::make_unique;
using std::pow;

class Stage1;


Stage GameConductor::NOW_STAGE;
unique_ptr<Scenario> GameConductor::STAGE;
const unsigned int GameConductor::SURVIVAL_BONUS = 1000;
unsigned int GameConductor::SCORE = 0;	// publicにする？
unsigned int GameConductor::TECHNICAL_SCORE = 0;
bool GameConductor::SURVIVAL_BONUS_ENABLE_FLAG = true;
bool GameConductor::GAMEOVER_FLAG = false;
bool GameConductor::GAMECLEAR_FLAG = false;


GameConductor::GameConductor() :
	scoreboard(make_unique<Scoreboard>()),
	game_started_clock(DxLib::GetNowCount()),
	game_time(0.0),
	survival_time_score(0)
{
	GameConductor::INITIALIZE();
	Field::INITIALIZE();
	KeyPushFlags::INITIALIZE();
	Offensive::INITIALIZE();
}


GameConductor::~GameConductor() = default;


void GameConductor::INITIALIZE() {

	SCORE = 0;
	NOW_STAGE = Stage::STAGE3;
	STAGE = make_unique<Stage3>();
	TECHNICAL_SCORE = 0;
	SURVIVAL_BONUS_ENABLE_FLAG = true;
	GAMEOVER_FLAG = false;
	GAMECLEAR_FLAG = false;
	for (int i = 0; i < 256; i++) {
		AppSession::KEY_BUFFER[i] = NULL;
	}

}


void GameConductor::update() {
	game_time = (double)(DxLib::GetNowCount() - game_started_clock) / 1000;
	DebugParams::GAME_TIME = game_time;

	if (SURVIVAL_BONUS_ENABLE_FLAG == true) {
		survival_time_score = SURVIVAL_BONUS * game_time;

	}

	if (GAMEOVER_FLAG == false) {
		if (Field::MY_CHARACTER->is_dead() == true) {
			GAMEOVER_FLAG = true;
			SURVIVAL_BONUS_ENABLE_FLAG = false;
			Field::MY_BULLETS->clear();
			// ゲームオーバー時にリザルトを出力
			ResultOutput::RESULT_OUTPUT();
			
		}
	}

	if (GAMECLEAR_FLAG == false) {
		if ((*Field::DEAD_FLAGS)[CharacterID::MOFU] == true) {
			GAMECLEAR_FLAG = true;
			SURVIVAL_BONUS_ENABLE_FLAG = false;
			Field::ENEMY_BULLETS->clear();
			Field::ENEMY_CHARACTERS->clear();
			//Field::IDENTIFIABLE_ENEMY_CHARACTERS->clear();
			SCORE += pow(Field::MY_CHARACTER->hp, 2) * 100;
		}

		//TOROIの中でもリザルト出力する
	}


	Field::DRAW();
	Field::UPDATE();
	Field::ERASE_BROKEN_OFFENSIVES();
	Field::ERASE_DEAD_CHARACTERS();
	Field::ERASE_OUTSIDED_OBJECTS();
	Field::DEAL_COLLISION();
	
	STAGE->update();

	if (KeyPushFlags::F4 == false && AppSession::KEY_BUFFER[KEY_INPUT_F4] == 1) {
		KeyPushFlags::F4 = true;
		GAMECLEAR_FLAG = true;
	}
	if (KeyPushFlags::F4 == true && AppSession::KEY_BUFFER[KEY_INPUT_F4] == 0) {
		KeyPushFlags::F4 = false;
	}


	if (GAMEOVER_FLAG == true) {
		DxLib::DrawFormatStringToHandle(265, 200, Colors::RED, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, L"GAME OVER");
		DxLib::DrawFormatStringToHandle(220, 600, Colors::RED, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, L"PRESS SPACE KEY");
	}

	if (GAMECLEAR_FLAG == true) {
		DxLib::DrawFormatStringToHandle(255, 200, Colors::CYAN, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, L"GAME CLEAR");
		DxLib::DrawFormatStringToHandle(220, 600, Colors::CYAN, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, L"PRESS SPACE KEY");
	}


	DxLib::DrawGraph(0, 0, ImageHandles::SCREEN_BACKGROUND_CROPPED, TRUE);
	DxLib::DrawRotaGraph(850, 630, 0.4, 0, ImageHandles::LOGO, TRUE);
	SCORE = survival_time_score + TECHNICAL_SCORE;
	draw_score();
	draw_my_hp();
}


void GameConductor::draw_score() {
	DxLib::DrawFormatStringToHandle(720, 350, Colors::RED, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_16, L"SCORE");
	DxLib::DrawFormatStringToHandle(720, 384, Colors::RED, FontHandles::DSEG14, L"%08u", GameConductor::SCORE);
}


void GameConductor::draw_my_hp() {
	DxLib::DrawFormatStringToHandle(720, 150, Colors::YELLOW, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_16, L"LIFE");
	DxLib::DrawFormatStringToHandle(720, 190, Colors::YELLOW, FontHandles::DSEG14, L"%3d", Field::MY_CHARACTER->hp);
}