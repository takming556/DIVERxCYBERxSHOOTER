#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


GameConductor::GameConductor() :
	now_stage(Stage::STAGE1),
	scoreboard(make_unique<Scoreboard>()),
	stage1(make_unique<Stage1>())
{
	Field::INITIALIZE();
}


void GameConductor::update() {
	check_keyinput();
	Field::UPDATE();
	Field::DRAW();
	Field::DEAL_COLLISION();
	
	switch (now_stage) {
	case Stage::STAGE1:
		stage1->update();
		break;
	}
}


void GameConductor::check_keyinput() {
	DxLib::GetHitKeyStateAll(KeyPushFlags::KEY_BUFFER);
}