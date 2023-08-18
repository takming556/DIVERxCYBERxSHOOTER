#include <memory>
#include <cmath>
#include "DxLib.h"
#include "AppSession.h"
#include "GameConductor.h"
#include "Field.h"
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


const unsigned int GameConductor::SURVIVAL_BONUS = 1000;
unsigned int GameConductor::SCORE = 0;
bool GameConductor::SURVIVAL_BONUS_ENABLE_FLAG = true;
bool GameConductor::GAMEOVER_FLAG = false;
bool GameConductor::GAMECLEAR_FLAG = false;


GameConductor::GameConductor() :
	now_stage(Stage::STAGE3),
	scoreboard(make_unique<Scoreboard>()),
	stage(make_unique<Stage3>()),
	last_updated_clock(DxLib::GetNowCount()),
	game_time(0.0)
{
	GameConductor::INITIALIZE();
	Field::INITIALIZE();
	KeyPushFlags::INITIALIZE();
}


GameConductor::~GameConductor() = default;


void GameConductor::INITIALIZE() {

	SCORE = 0;
	SURVIVAL_BONUS_ENABLE_FLAG = true;
	GAMEOVER_FLAG = false;
	GAMECLEAR_FLAG = false;
	for (int i = 0; i < 256; i++) {
		AppSession::KEY_BUFFER[i] = NULL;
	}

}


void GameConductor::update() {
	int update_delta_time = DxLib::GetNowCount() - last_updated_clock;
	DebugParams::GAME_TIME += (double)update_delta_time / 1000;
	game_time += (double)update_delta_time / 1000;

	if (SURVIVAL_BONUS_ENABLE_FLAG == true) {
		SCORE += SURVIVAL_BONUS * update_delta_time / 1000;
	}

	if (GAMEOVER_FLAG == false) {
		if (Field::MY_CHARACTER->is_dead() == true) {
			GAMEOVER_FLAG = true;
			SURVIVAL_BONUS_ENABLE_FLAG = false;
			Field::MY_OFFENSIVES->clear();
		}
	}

	if (GAMECLEAR_FLAG == false) {
		if ((*Field::DEAD_FLAGS)[CharacterID::MOFU] == true) {
			GAMECLEAR_FLAG = true;
			SURVIVAL_BONUS_ENABLE_FLAG = false;
			Field::ENEMY_OFFENSIVES->clear();
			Field::ENEMY_CHARACTERS->clear();
			Field::IDENTIFIABLE_ENEMY_CHARACTERS->clear();
			SCORE += pow(Field::MY_CHARACTER->life, 2) * 100;
		}
	}


	Field::DRAW();
	Field::UPDATE();
	Field::ERASE_BROKEN_OFFENSIVES();
	Field::ERASE_DEAD_CHARACTERS();
	Field::ERASE_OUTSIDED_OBJECTS();
	Field::DEAL_COLLISION();
	
	stage->update();

	if (KeyPushFlags::F4 == false && AppSession::KEY_BUFFER[KEY_INPUT_F4] == 1) {
		KeyPushFlags::F4 = true;
		GAMECLEAR_FLAG = true;
	}
	if (KeyPushFlags::F4 == true && AppSession::KEY_BUFFER[KEY_INPUT_F4] == 0) {
		KeyPushFlags::F4 = false;
	}


	if (GAMEOVER_FLAG == true) {
		DxLib::DrawFormatStringToHandle(265, 200, Colors::RED, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "GAME OVER");
		DxLib::DrawFormatStringToHandle(220, 600, Colors::RED, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "PRESS SPACE KEY");
	}

	if (GAMECLEAR_FLAG == true) {
		DxLib::DrawFormatStringToHandle(255, 200, Colors::CYAN, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "GAME CLEAR");
		DxLib::DrawFormatStringToHandle(220, 600, Colors::CYAN, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "PRESS SPACE KEY");
	}


	DxLib::DrawGraph(0, 0, ImageHandles::SCREEN_BACKGROUND_CROPPED, TRUE);
	DxLib::DrawRotaGraph(850, 630, 0.4, 0, ImageHandles::LOGO, TRUE);
	draw_score();
	draw_my_hp();

	last_updated_clock = DxLib::GetNowCount();

}


void GameConductor::draw_score() {
	DxLib::DrawFormatStringToHandle(720, 350, Colors::RED, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_16, "SCORE");
	DxLib::DrawFormatStringToHandle(720, 384, Colors::RED, FontHandles::DSEG14, "%08u", GameConductor::SCORE);
}


void GameConductor::draw_my_hp() {
	DxLib::DrawFormatStringToHandle(720, 150, Colors::YELLOW, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_16, "LIFE");
	DxLib::DrawFormatStringToHandle(720, 190, Colors::YELLOW, FontHandles::DSEG14, "%3d", Field::MY_CHARACTER->life);
}