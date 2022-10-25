#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


const unsigned int GameConductor::SURVIVAL_BONUS = 1000;


GameConductor::GameConductor() :
	now_stage(Stage::STAGE1),
	scoreboard(make_unique<Scoreboard>()),
	stage1(make_unique<Stage1>()),
	last_updated_clock(DxLib::GetNowCount())
{
	Field::INITIALIZE();
}


void GameConductor::update() {
	int elapsed_time_since_last_updated = DxLib::GetNowCount() - last_updated_clock;
	DebugParams::GAME_TIME += (double)elapsed_time_since_last_updated / 1000;
	game_time += (double)elapsed_time_since_last_updated / 1000;
	AppSession::SCORE += SURVIVAL_BONUS * elapsed_time_since_last_updated / 1000;

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

	draw_score();

	last_updated_clock = DxLib::GetNowCount();

}


void GameConductor::draw_score() {
	DxLib::DrawFormatStringToHandle(640, 384, Colors::RED, FontHandles::DSEG14, "%08u", AppSession::SCORE);
}