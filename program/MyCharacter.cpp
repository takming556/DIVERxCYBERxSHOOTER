#include <string>
#include <vector>
#include <memory>
#include "DxLib.h"
#include "class.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;

MyCharacter::MyCharacter(string character_name) :
	Character(INITIAL_POSITION_X, INITIAL_POSITION_Y),
	collidant(make_unique<CollideCircle>(INITIAL_POSITION_X, INITIAL_POSITION_Y, COLLIDANT_SIZE)),
	SPS(4.0),
	is_z_key_pushed(false),
	is_x_key_pushed(false),
	clock_keeper_for_launch_ticking(0),
	name(character_name),
	life(3)
{
}


void MyCharacter::update(char key_buffer[], vector<unique_ptr<Offensive>>& my_offensives) {
	respond_to_keyinput(key_buffer, my_offensives);
	collidant->update(position);
}


void MyCharacter::respond_to_keyinput(char key_buffer[], vector<unique_ptr<Offensive>>& my_offensive) {

	//Zキー
	if (is_z_key_pushed == false && key_buffer[KEY_INPUT_Z] == 1) {	//Zキーを今まで押していなかったが、押し始めた瞬間
		is_z_key_pushed = true;
		launch(my_offensive);
		clock_keeper_for_launch_ticking = GetNowCount();

	}
	else if (is_z_key_pushed == true && key_buffer[KEY_INPUT_Z] == 0) {	//Zキーを今まで押していたが、離した瞬間
		is_z_key_pushed = false;
	}
	else if (is_z_key_pushed == true && key_buffer[KEY_INPUT_Z] == 1) {	//Zキーを今まで押していたし、今も押している
		int launch_wait = 1.0 / SPS * 1000;
		if (GetNowCount() > clock_keeper_for_launch_ticking + launch_wait) {
			launch(my_offensive);
			clock_keeper_for_launch_ticking = GetNowCount();
		}
	}


	//Xキー
	if (is_x_key_pushed == false && key_buffer[KEY_INPUT_X] == 1) {
		is_x_key_pushed = true;
	}
	else if (is_x_key_pushed == true && key_buffer[KEY_INPUT_X] == 0) {
		is_x_key_pushed = false;
	}


	//上矢印キー
	if (key_buffer[KEY_INPUT_UP] == 1) move_upward();


	//下矢印キー
	if (key_buffer[KEY_INPUT_DOWN] == 1) move_downward();


	//左矢印キー
	if (key_buffer[KEY_INPUT_LEFT] == 1) move_leftward();


	//右矢印キー
	if (key_buffer[KEY_INPUT_RIGHT] == 1) move_rightward();

}


void MyCharacter::move_upward() {
	position->y += 5;
}


void MyCharacter::move_downward() {
	position->y += -5;
}


void MyCharacter::move_leftward() {
	position->x += -5;
}


void MyCharacter::move_rightward() {
	position->x += 5;
}


void MyCharacter::launch(vector<unique_ptr<Offensive>>& my_offensive) {
	unique_ptr<Offensive> straight_shot = make_unique<StraightShot>(position->x, position->y - 30.0);
	my_offensive.push_back(move(straight_shot));
}