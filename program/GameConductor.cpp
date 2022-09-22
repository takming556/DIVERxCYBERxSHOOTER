#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


GameConductor::GameConductor() :
	now_stage(Stage::STAGE1),
	//field(make_unique<Field>()),
	scoreboard(make_unique<Scoreboard>()),
	//key_buffer({ NULL }),
	is_up_key_pushed(false),
	is_down_key_pushed(false),
	is_right_key_pushed(false),
	is_left_key_pushed(false),
	is_z_key_pushed(false)
{
	Field::INITIALIZE();
}


void GameConductor::update() {
	check_keyinput();
	Field::UPDATE(key_buffer);
	Field::DRAW();
	Field::DEAL_COLLISION();
}


void GameConductor::check_keyinput() {
	DxLib::GetHitKeyStateAll(key_buffer);
}