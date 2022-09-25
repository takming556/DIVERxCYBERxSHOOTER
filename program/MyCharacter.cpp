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
	clock_keeper_for_move_leftward(0)
{
}


void MyCharacter::update() {
	respond_to_keyinput();
	collidant->update(position);
	//DxLib::DrawFormatString(800, 30, GetColor(255, 255, 0), "life = %d", life);
}


void MyCharacter::respond_to_keyinput() {

	//Zキー
	if (KeyPushFlags::Z == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_Z] == 1) {	//Zキーを今まで押していなかったが、押し始めた瞬間
		KeyPushFlags::Z = true;
		launch();
		clock_keeper_for_launch_ticking = DxLib::GetNowHiPerformanceCount();
	}
	if (KeyPushFlags::Z == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_Z] == 0) {	//Zキーを今まで押していたが、離した瞬間
		KeyPushFlags::Z = false;
	}
	if (KeyPushFlags::Z == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_Z] == 1) {	//Zキーを今まで押していたし、今も押している
		int launch_wait = 1.0 / shot_frequency * 1000 * 1000;
		if (DxLib::GetNowHiPerformanceCount() > clock_keeper_for_launch_ticking + launch_wait) {
			launch();
			clock_keeper_for_launch_ticking = DxLib::GetNowHiPerformanceCount();
		}
	}


	////Xキー
	//if (KeyPushFlags::X == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_X] == 1) {
	//	KeyPushFlags::X = true;
	//}
	//if (KeyPushFlags::X == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_X] == 0) {
	//	KeyPushFlags::X = false;
	//}


	//上矢印キー
	if (KeyPushFlags::UP == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_UP] == 1) {
		KeyPushFlags::UP = true;
		clock_keeper_for_move_upward = DxLib::GetNowHiPerformanceCount();
	}
	if (KeyPushFlags::UP == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_UP] == 0) {
		KeyPushFlags::UP = false;
	}
	if (KeyPushFlags::UP == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_UP] == 1) {
		LONGLONG delta_time = DxLib::GetNowHiPerformanceCount() - clock_keeper_for_move_upward;
		move_upward(delta_time);
		clock_keeper_for_move_upward = DxLib::GetNowHiPerformanceCount();
	}


	//下矢印キー
	if (KeyPushFlags::DOWN == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_DOWN] == 1) {
		KeyPushFlags::DOWN = true;
		clock_keeper_for_move_downward = DxLib::GetNowHiPerformanceCount();
	}
	if (KeyPushFlags::DOWN == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_DOWN] == 0) {
		KeyPushFlags::DOWN = false;
	}
	if (KeyPushFlags::DOWN == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_DOWN] == 1) {
		LONGLONG delta_time = DxLib::GetNowHiPerformanceCount() - clock_keeper_for_move_downward;
		move_downward(delta_time);
		clock_keeper_for_move_downward = DxLib::GetNowHiPerformanceCount();
	}


	//右矢印キー
	if (KeyPushFlags::RIGHT == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_RIGHT] == 1) {
		KeyPushFlags::RIGHT = true;
		clock_keeper_for_move_rightward = DxLib::GetNowHiPerformanceCount();
	}
	if (KeyPushFlags::RIGHT == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_RIGHT] == 0) {
		KeyPushFlags::RIGHT = false;
	}
	if (KeyPushFlags::RIGHT == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_RIGHT] == 1) {
		LONGLONG delta_time = DxLib::GetNowHiPerformanceCount() - clock_keeper_for_move_rightward;
		move_rightward(delta_time);
		clock_keeper_for_move_rightward = DxLib::GetNowHiPerformanceCount();
	}


	//左矢印キー
	if (KeyPushFlags::LEFT == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_LEFT] == 1) {
		KeyPushFlags::LEFT = true;
		clock_keeper_for_move_leftward = DxLib::GetNowHiPerformanceCount();
	}
	if (KeyPushFlags::LEFT == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_LEFT] == 0) {
		KeyPushFlags::LEFT = false;
	}
	if (KeyPushFlags::LEFT == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_LEFT] == 1) {
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


void MyCharacter::launch() {
	unique_ptr<Offensive<MyCharacter>> straight_shot = make_unique<StraightShot1<MyCharacter>>(position->x, position->y + 30.0, pi / 2, 2000.0);
	Field::MY_OFFENSIVES->push_back(move(straight_shot));
}


void MyCharacter::damaged() {
	life += -1;
}


void MyCharacter::draw_life() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::BLUE, "%d", life);
}


bool MyCharacter::is_collided_with_enemy_offensives() {
	bool collided_with_no_less_than_one_enemy_offensive_flag = false;
	for (const auto& enemy_offensive : *Field::ENEMY_OFFENSIVES) {
		if (collidant->is_collided_with(enemy_offensive->collidant)) collided_with_no_less_than_one_enemy_offensive_flag = true;
	}
	return collided_with_no_less_than_one_enemy_offensive_flag;
}