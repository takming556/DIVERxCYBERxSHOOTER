#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


const unsigned int GameConductor::SURVIVAL_BONUS = 1000;
unsigned int GameConductor::SCORE = 0;
bool GameConductor::SURVIVAL_BONUS_ENABLE_FLAG = true;
bool GameConductor::GAMEOVER_FLAG = false;
bool GameConductor::GAMECLEAR_FLAG = false;


GameConductor::GameConductor() :
	now_stage(Stage::STAGE1),
	scoreboard(make_unique<Scoreboard>()),
	stage1(make_unique<Stage1>()),
	last_updated_clock(DxLib::GetNowCount()),
	game_time(0.0)
{
	GameConductor::INITIALIZE();
	Field::INITIALIZE();
	KeyPushFlags::INITIALIZE();
}


void GameConductor::INITIALIZE() {
	SCORE = 0;
	SURVIVAL_BONUS_ENABLE_FLAG = true;
	GAMEOVER_FLAG = false;
	GAMECLEAR_FLAG = false;
}


void GameConductor::update() {
	int elapsed_time_since_last_updated = DxLib::GetNowCount() - last_updated_clock;
	DebugParams::GAME_TIME += (double)elapsed_time_since_last_updated / 1000;
	game_time += (double)elapsed_time_since_last_updated / 1000;

	if (SURVIVAL_BONUS_ENABLE_FLAG == true) {
		GameConductor::SCORE += SURVIVAL_BONUS * elapsed_time_since_last_updated / 1000;
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
		}
	}


	Field::UPDATE();
	Field::DRAW();
	Field::ERASE_BROKEN_OFFENSIVES();
	Field::ERASE_DEAD_CHARACTERS();
	Field::ERASE_OUTSIDED_OBJECTS();
	Field::DEAL_COLLISION();
	
	switch (now_stage) {
	case Stage::STAGE1:
		stage1->update();
		break;
	}

	if (GAMEOVER_FLAG == true) {
		DxLib::DrawFormatStringToHandle(200, 200, Colors::RED, FontHandles::DSEG14, "GAME OVER");
		DxLib::DrawFormatStringToHandle(150, 600, Colors::RED, FontHandles::DSEG14, "PRESS SPACE KEY");
	}

	if (GAMECLEAR_FLAG == true) {
		DxLib::DrawFormatStringToHandle(100, 100, Colors::RED, FontHandles::DSEG14, "GAME CLEAR");
		DxLib::DrawFormatStringToHandle(100, 500, Colors::RED, FontHandles::DSEG14, "PRESS SPACE KEY");
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