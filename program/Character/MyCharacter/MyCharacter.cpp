#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "AppSession.h"
#include "GameConductor.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Offensive/Offensive.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "CollideRealm/CollideRealm.h"
#include "KeyPushFlags.h"
#include "DebugParams.h"
#include "SoundHandles.h"
#include "Colors.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::sin;
using std::cos;
using std::numbers::pi;

const int MyCharacter::INITIAL_POSITION_X = Field::PIXEL_SIZE_X / 2;
const int MyCharacter::INITIAL_POSITION_Y = Field::PIXEL_SIZE_Y / 4;
const int MyCharacter::INITIAL_HP = 100;
const unsigned int MyCharacter::COLLIDANT_SIZE = 15;
const double MyCharacter::SLOW_MOVE_SPEED_EXTRATE = 0.5;
bool MyCharacter::SLOWMOVE_FLAG = false;


MyCharacter::MyCharacter(string character_name) :
	name(character_name),
	shot_frequency(10.0),
	move_speed(300.0),
	last_launch_ticked_clock(DxLib::GetNowCount())
{
}


void MyCharacter::update() {
	respond_to_keyinput();
	regulate_position();
	collidant->update(position);
	last_updated_clock = DxLib::GetNowHiPerformanceCount();
	DebugParams::MY_CHARACTER_INFIELD_X = position->x;
	DebugParams::MY_CHARACTER_INFIELD_Y = position->y;
	DebugParams::MY_CHARACTER_DRAW_X = position->get_draw_position().x;
	DebugParams::MY_CHARACTER_DRAW_Y = position->get_draw_position().y;
}


void MyCharacter::respond_to_keyinput() {

	if (GameConductor::GAMEOVER_FLAG == false) {

		//Zキー
		if (KeyPushFlags::Z == false && AppSession::KEY_BUFFER[KEY_INPUT_Z] == 1) {	//Zキーを今まで押していなかったが、押し始めた瞬間
			KeyPushFlags::Z = true;
			launch();
			last_launch_ticked_clock = DxLib::GetNowCount();
		}
		if (KeyPushFlags::Z == true && AppSession::KEY_BUFFER[KEY_INPUT_Z] == 0) {	//Zキーを今まで押していたが、離した瞬間
			KeyPushFlags::Z = false;
		}
		if (KeyPushFlags::Z == true && AppSession::KEY_BUFFER[KEY_INPUT_Z] == 1) {	//Zキーを今まで押していたし、今も押している
			int launch_wait = 1.0 / shot_frequency * 1000;
			if (DxLib::GetNowCount() > last_launch_ticked_clock + launch_wait) {
				launch();
				last_launch_ticked_clock = DxLib::GetNowCount();
			}
		}


		//Xキー
		if (KeyPushFlags::X == false && AppSession::KEY_BUFFER[KEY_INPUT_X] == 1) {
			KeyPushFlags::X = true;
		}
		if (KeyPushFlags::X == true && AppSession::KEY_BUFFER[KEY_INPUT_X] == 0) {
			KeyPushFlags::X = false;
		}

		//↑↓←→キー
		if (AppSession::KEY_BUFFER[KEY_INPUT_UP] == 1) {
			if (AppSession::KEY_BUFFER[KEY_INPUT_RIGHT] == 1) {
				move_uprightward();
			}
			else if (AppSession::KEY_BUFFER[KEY_INPUT_LEFT] == 1) {
				move_upleftward();
			}
			else {
				move_upward();
			}
		}
		else if (AppSession::KEY_BUFFER[KEY_INPUT_DOWN] == 1) {
			if (AppSession::KEY_BUFFER[KEY_INPUT_RIGHT] == 1) {
				move_downrightward();
			}
			else if (AppSession::KEY_BUFFER[KEY_INPUT_LEFT] == 1) {
				move_downleftward();
			}
			else {
				move_downward();
			}
		}
		else {
			if (AppSession::KEY_BUFFER[KEY_INPUT_RIGHT] == 1) {
				move_rightward();
			}
			else if (AppSession::KEY_BUFFER[KEY_INPUT_LEFT] == 1) {
				move_leftward();
			}
		}

		//左SHIFTキー
		if (AppSession::KEY_BUFFER[KEY_INPUT_LSHIFT] == 1) {
			MyCharacter::SLOWMOVE_FLAG = true;
		}
		else {
			MyCharacter::SLOWMOVE_FLAG = false;
		}
	}
}


void MyCharacter::move_upward() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	position->y += distance;
}


void MyCharacter::move_downward() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	position->y -= distance;
}


void MyCharacter::move_rightward() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	position->x += distance;
}


void MyCharacter::move_leftward() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	position->x -= distance;
}


void MyCharacter::move_uprightward() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(1.0 / 4.0 * pi);
	double distance_y = distance * sin(1.0 / 4.0 * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::move_downrightward() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(-(1.0 / 4.0) * pi);
	double distance_y = distance * sin(-(1.0 / 4.0) * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::move_upleftward() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(3.0 / 4.0 * pi);
	double distance_y = distance * sin(3.0 / 4.0 * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::move_downleftward() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(-(3.0 / 4.0) * pi);
	double distance_y = distance * sin(-(3.0 / 4.0) * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::regulate_position() {
	if (position->x < InFieldPosition::MIN_MOVABLE_BOUNDARY_X) position->x = InFieldPosition::MIN_MOVABLE_BOUNDARY_X;
	if (position->y < InFieldPosition::MIN_MOVABLE_BOUNDARY_Y) position->y = InFieldPosition::MIN_MOVABLE_BOUNDARY_Y;
	if (position->x > InFieldPosition::MAX_MOVABLE_BOUNDARY_X) position->x = InFieldPosition::MAX_MOVABLE_BOUNDARY_X;
	if (position->y > InFieldPosition::MAX_MOVABLE_BOUNDARY_Y) position->y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y;
}


void MyCharacter::launch() {;
	(*Field::MY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
		position->x,
		position->y + 30.0,
		pi / 2,
		2000,
		20,
		1,
		SkinID::ICHIGO_CHAN
	);
	DxLib::PlaySoundMem(SoundHandles::MYSHOT, DX_PLAYTYPE_BACK);
}


void MyCharacter::damaged() {
	hp += -1;
	DxLib::PlaySoundMem(SoundHandles::MYHIT, DX_PLAYTYPE_BACK);
}


bool MyCharacter::is_collided_with_enemy_offensives() {
	bool collided_with_no_less_than_one_enemy_offensive_flag = false;
	for (const auto& enemy_bullet : *Field::ENEMY_BULLETS) {
		if (collidant->is_collided_with(enemy_bullet.second->collidant)) collided_with_no_less_than_one_enemy_offensive_flag = true;
	}
	return collided_with_no_less_than_one_enemy_offensive_flag;
}


void MyCharacter::deal_collision() {

	for (const auto& enemy_bullet : *Field::ENEMY_BULLETS) {
		if (is_last_collided_with(enemy_bullet.first) == false						// 前回はそいつと衝突していなかったが、
			&& collidant->is_collided_with(enemy_bullet.second->collidant) == true)	// 現在は衝突している
		{
			damaged();
		}
	}

	last_collided_enemy_bullet_ids.clear();

	for (const auto& enemy_bullet : *Field::ENEMY_BULLETS) {
		if (collidant->is_collided_with(enemy_bullet.second->collidant) == true) {
			last_collided_enemy_bullet_ids.push_back(enemy_bullet.first);
		}
	}
}


bool MyCharacter::is_last_collided_with(unsigned int given_enemy_bullet_id) {
	bool found = false;
	for (const auto& last_collided_enemy_bullet_id : last_collided_enemy_bullet_ids) {
		if (last_collided_enemy_bullet_id == given_enemy_bullet_id) found = true;
	}
	return found;
}