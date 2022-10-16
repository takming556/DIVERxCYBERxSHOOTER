#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


GameConductor::GameConductor() :
	now_stage(Stage::STAGE1),
	scoreboard(make_unique<Scoreboard>()),
	stage1(make_unique<Stage1>()),
	last_updated_clock(DxLib::GetNowCount())
{
	Field::INITIALIZE();
}


void GameConductor::update() {
	DebugParams::GAME_TIME += (double)(DxLib::GetNowCount() - last_updated_clock) / 1000;
	last_updated_clock = DxLib::GetNowCount();
	Field::UPDATE();
	Field::DRAW();
	Field::DEAL_COLLISION();
	Field::ERASE_BROKEN_OFFENSIVES();
	Field::ERASE_DEAD_CHARACTERS();
	Field::ERASE_OUTSIDED_OBJECTS();
	
	switch (now_stage) {
	case Stage::STAGE1:
		stage1->update();
		break;
	}
}