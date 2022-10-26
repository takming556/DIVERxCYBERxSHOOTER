#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


const unsigned int GameConductor::SURVIVAL_BONUS = 1000;
unsigned int GameConductor::SCORE = 0;
bool GameConductor::SURVIVAL_BONUS_ENABLE_FLAG = true;


GameConductor::GameConductor() :
	now_stage(Stage::STAGE1),
	scoreboard(make_unique<Scoreboard>()),
	stage1(make_unique<Stage1>()),
	last_updated_clock(DxLib::GetNowCount()),
	game_time(0.0)
{
	GameConductor::INITIALIZE();
	Field::INITIALIZE();
}


void GameConductor::INITIALIZE() {
	SCORE = 0;
	SURVIVAL_BONUS_ENABLE_FLAG = true;
}


void GameConductor::update() {
	int elapsed_time_since_last_updated = DxLib::GetNowCount() - last_updated_clock;
	DebugParams::GAME_TIME += (double)elapsed_time_since_last_updated / 1000;
	game_time += (double)elapsed_time_since_last_updated / 1000;

	if (SURVIVAL_BONUS_ENABLE_FLAG == true) {
		GameConductor::SCORE += SURVIVAL_BONUS * elapsed_time_since_last_updated / 1000;
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

	DxLib::DrawGraph(0, 0, ImageHandles::SCREEN_BACKGROUND_CROPPED, TRUE);
	DxLib::DrawRotaGraph(850, 630, 0.4, 0, ImageHandles::LOGO, TRUE);
	draw_score();

	last_updated_clock = DxLib::GetNowCount();

}


void GameConductor::draw_score() {
	DxLib::DrawFormatStringToHandle(720, 384, Colors::RED, FontHandles::DSEG14, "%08u", GameConductor::SCORE);
}