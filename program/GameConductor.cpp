#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


GameConductor::GameConductor() :
	now_stage(Stage::STAGE1),
	field(make_unique<Field>()),
	scoreboard(make_unique<Scoreboard>()),
	//key_buffer({ NULL }),
	is_up_key_pushed(false),
	is_down_key_pushed(false),
	is_right_key_pushed(false),
	is_left_key_pushed(false),
	is_z_key_pushed(false)
{

}


void GameConductor::update() {
	check_keyinput();
	field->update(key_buffer);
	field->draw();
}


void GameConductor::check_keyinput() {
	GetHitKeyStateAll(key_buffer);
}