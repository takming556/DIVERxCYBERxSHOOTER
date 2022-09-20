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
	name(character_name),
	life(100),
	shot_frequency(10.0),
	move_speed(300.0),
	clock_keeper_for_launch_ticking(0),
	clock_keeper_for_move_upward(0),
	clock_keeper_for_move_downward(0),
	clock_keeper_for_move_rightward(0),
	clock_keeper_for_move_leftward(0),
	is_z_key_pushed(false),
	is_x_key_pushed(false),
	is_up_key_pushed(false),
	is_down_key_pushed(false),
	is_right_key_pushed(false),
	is_left_key_pushed(false)
{
}


void MyCharacter::update(char key_buffer[], unique_ptr<vector<unique_ptr<Offensive>>>& my_offensives) {
	respond_to_keyinput(key_buffer, my_offensives);
	collidant->update(position);
	DxLib::DrawFormatString(800, 30, GetColor(255, 255, 0), "life = %d", life);
}


void MyCharacter::respond_to_keyinput(char key_buffer[], unique_ptr<vector<unique_ptr<Offensive>>>& my_offensive) {

	//Zキー
	if (is_z_key_pushed == false && key_buffer[KEY_INPUT_Z] == 1) {	//Zキーを今まで押していなかったが、押し始めた瞬間
		is_z_key_pushed = true;
		launch(my_offensive);
		clock_keeper_for_launch_ticking = DxLib::GetNowHiPerformanceCount();
	}
	if (is_z_key_pushed == true && key_buffer[KEY_INPUT_Z] == 0) {	//Zキーを今まで押していたが、離した瞬間
		is_z_key_pushed = false;
	}
	if (is_z_key_pushed == true && key_buffer[KEY_INPUT_Z] == 1) {	//Zキーを今まで押していたし、今も押している
		int launch_wait = 1.0 / shot_frequency * 1000 * 1000;
		if (DxLib::GetNowHiPerformanceCount() > clock_keeper_for_launch_ticking + launch_wait) {
			launch(my_offensive);
			clock_keeper_for_launch_ticking = DxLib::GetNowHiPerformanceCount();
		}
	}


	//Xキー
	if (is_x_key_pushed == false && key_buffer[KEY_INPUT_X] == 1) {
		is_x_key_pushed = true;
	}
	if (is_x_key_pushed == true && key_buffer[KEY_INPUT_X] == 0) {
		is_x_key_pushed = false;
	}


	//上矢印キー
	if (is_up_key_pushed == false && key_buffer[KEY_INPUT_UP] == 1) {
		is_up_key_pushed = true;
		clock_keeper_for_move_upward = DxLib::GetNowHiPerformanceCount();
	}
	if (is_up_key_pushed == true && key_buffer[KEY_INPUT_UP] == 0) {
		is_up_key_pushed = false;
	}
	if (is_up_key_pushed == true && key_buffer[KEY_INPUT_UP] == 1) {
		LONGLONG delta_time = DxLib::GetNowHiPerformanceCount() - clock_keeper_for_move_upward;
		move_upward(delta_time);
		clock_keeper_for_move_upward = DxLib::GetNowHiPerformanceCount();
	}


	//下矢印キー
	if (is_down_key_pushed == false && key_buffer[KEY_INPUT_DOWN] == 1) {
		is_down_key_pushed = true;
		clock_keeper_for_move_downward = DxLib::GetNowHiPerformanceCount();
	}
	if (is_down_key_pushed == true && key_buffer[KEY_INPUT_DOWN] == 0) {
		is_down_key_pushed = false;
	}
	if (is_down_key_pushed == true && key_buffer[KEY_INPUT_DOWN] == 1) {
		LONGLONG delta_time = DxLib::GetNowHiPerformanceCount() - clock_keeper_for_move_downward;
		move_downward(delta_time);
		clock_keeper_for_move_downward = DxLib::GetNowHiPerformanceCount();
	}


	//右矢印キー
	if (is_right_key_pushed == false && key_buffer[KEY_INPUT_RIGHT] == 1) {
		is_right_key_pushed = true;
		clock_keeper_for_move_rightward = DxLib::GetNowHiPerformanceCount();
	}
	if (is_right_key_pushed == true && key_buffer[KEY_INPUT_RIGHT] == 0) {
		is_right_key_pushed = false;
	}
	if (is_right_key_pushed == true && key_buffer[KEY_INPUT_RIGHT] == 1) {
		LONGLONG delta_time = DxLib::GetNowHiPerformanceCount() - clock_keeper_for_move_rightward;
		move_rightward(delta_time);
		clock_keeper_for_move_rightward = DxLib::GetNowHiPerformanceCount();
	}


	//左矢印キー
	if (is_left_key_pushed == false && key_buffer[KEY_INPUT_LEFT] == 1) {
		is_left_key_pushed = true;
		clock_keeper_for_move_leftward = DxLib::GetNowHiPerformanceCount();
	}
	if (is_left_key_pushed == true && key_buffer[KEY_INPUT_LEFT] == 0) {
		is_left_key_pushed = false;
	}
	if (is_left_key_pushed == true && key_buffer[KEY_INPUT_LEFT] == 1) {
		LONGLONG delta_time = DxLib::GetNowHiPerformanceCount() - clock_keeper_for_move_leftward;
		move_leftward(delta_time);
		clock_keeper_for_move_leftward = DxLib::GetNowHiPerformanceCount();
	}

}


void MyCharacter::move_upward(LONGLONG delta_time) {
	double distance = move_speed * delta_time / 1000 / 1000;
	position->y += distance;
}


void MyCharacter::move_downward(LONGLONG delta_time) {
	double distance = move_speed * delta_time / 1000 / 1000;
	position->y += -distance;
}


void MyCharacter::move_leftward(LONGLONG delta_time) {
	double distance = move_speed * delta_time / 1000 / 1000;
	position->x += -distance;
}


void MyCharacter::move_rightward(LONGLONG delta_time) {
	double distance = move_speed * delta_time / 1000 / 1000;
	position->x += distance;
}


void MyCharacter::launch(unique_ptr<vector<unique_ptr<Offensive>>>& my_offensives) {
	unique_ptr<Offensive> straight_shot = make_unique<StraightShot>(position->x, position->y + 30.0, pi / 2, 2000.0);
	my_offensives->push_back(move(straight_shot));
	my_offensives->pop_back();
}


void MyCharacter::damaged() {
	life += -1;
}