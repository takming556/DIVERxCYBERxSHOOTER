﻿#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <numbers>
//#include <unordered_map>
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
#include "enum.h"
#include "Collision.h"

using std::wstring;
using std::vector;
//using std::unordered_map;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::sin;
using std::cos;
using std::numbers::pi;

const int MyCharacter::INITIAL_POSITION_X = Field::PIXEL_SIZE_X / 2;
const int MyCharacter::INITIAL_POSITION_Y = Field::PIXEL_SIZE_Y / 4;
const int MyCharacter::INITIAL_HP = 100;
const unsigned int MyCharacter::COLLIDANT_SIZE = 12;
const double MyCharacter::SLOW_MOVE_SPEED_EXTRATE = 0.5;
bool MyCharacter::SLOWMOVE_FLAG = false;


MyCharacter::MyCharacter(wstring character_name) :
	name(character_name),
	shot_frequency(10.0),
	move_speed(300.0),
	last_launch_ticked_clock(DxLib::GetNowCount()),
	end_invincible_clock(DxLib::GetNowCount()),
	is_invincible(false)
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
	// 無敵のとき無敵終了予定時刻を超過しているか
	if (is_invincible && DxLib::GetNowCount() >= end_invincible_clock) {
			is_invincible = false;
	}
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
	(*Field::MY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
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


//bool MyCharacter::is_collided_with_enemy_offensives() {
//	bool collided_with_no_less_than_one_enemy_offensive_flag = false;
//	for (const auto& enemy_bullet : *Field::ENEMY_BULLETS) {
//		if (collidant->is_collided_with(enemy_bullet.second->collidant)) collided_with_no_less_than_one_enemy_offensive_flag = true;
//	}
//	return collided_with_no_less_than_one_enemy_offensive_flag;
//}


void MyCharacter::deal_collision() {
	
	// ENEMY_BULLETSとの衝突
	for (const auto& enemy_bullet : *Field::ENEMY_BULLETS) {
		if (is_last_collided_with_bullet(enemy_bullet.first) == false						// 前回はそいつと衝突していなかったが、
			&& collidant->is_collided_with(enemy_bullet.second->collidant) == true)	// 現在は衝突している
		{
			damaged();
		}
	}
	last_collisions_with_enemy_bullet.clear();
	for (const auto& enemy_bullet : *Field::ENEMY_BULLETS) {
		if (collidant->is_collided_with(enemy_bullet.second->collidant) == true) {
			last_collisions_with_enemy_bullet.push_back(Collision<BulletID>(enemy_bullet.first));
		}
	}


	//unordered_map<CharacterID, int> damaged_clocks;
	//for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
	//	if (is_last_collided_with(enemy_character->id) == false					// 前回はそいつと衝突していなかったが、
	//		&& collidant->is_collided_with(enemy_character->collidant) == true)	// 現在は衝突している
	//	{
	//		damaged();
	//	}
	//	else if (is_last_collided_with(enemy_character->id) == true				// 前回もそいつと衝突していたし、
	//		&& collidant->is_collided_with(enemy_character->collidant) == true)	// 現在も衝突している
	//	{
	//		int damage_wait = 1.0 / enemy_character->DPS * 1000;
	//		if (DxLib::GetNowCount() > last_damaged_clocks.at(enemy_character->id) + damage_wait) {
	//			damaged();
	//			damaged_clocks[enemy_character->id] = DxLib::GetNowCount();
	//		}
	//	}
	//}
	//for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
	//	if (collidant->is_collided_with(enemy_character->collidant) == true) {
	//		if (is_last_collided_with(enemy_character->id) == false) {
	//			damaged_clocks[enemy_character->id] = DxLib::GetNowCount();
	//		}
	//		if (is_last_collided_with(enemy_character->id) == true) {

	//		}
	//	}
	//}
	//last_damaged_clocks.clear();
	//last_damaged_clocks = damaged_clocks;


	// ENEMY_LASERSとの衝突
	vector<Collision<LaserID>> now_collisions_with_enemy_laser;
	for (const auto& enemy_laser : *Field::ENEMY_LASERS) {
		if (enemy_laser.second->is_active() == true) {
			if (enemy_laser.second->collidant->is_collided_with(collidant) == true) {
				if (is_last_collided_with_laser(enemy_laser.first) == true) {
					int damage_wait = 1.0 / enemy_laser.second->dps * 1000;
					if (DxLib::GetNowCount() > get_last_collision(enemy_laser.first).last_damaged_clock + damage_wait) {
						damaged();
						now_collisions_with_enemy_laser.push_back(Collision(
							enemy_laser.first,
							get_last_collision(enemy_laser.first).last_collided_clock));
					}
					else {
						now_collisions_with_enemy_laser.push_back(Collision(
							enemy_laser.first,
							get_last_collision(enemy_laser.first).last_collided_clock,
							get_last_collision(enemy_laser.first).last_damaged_clock)
						);
					}
				}
				if (is_last_collided_with_laser(enemy_laser.first) == false) {
					damaged();
					now_collisions_with_enemy_laser.push_back(Collision(enemy_laser.first));
				}
			}
		}
	}
	last_collisions_with_enemy_laser.clear();
	last_collisions_with_enemy_laser = now_collisions_with_enemy_laser;
	//for (const auto& enemy_laser : *Field::ENEMY_LASERS) {
	//	if (collidant->is_collided_with(enemy_laser.second->collidant) == true) {
	//		damaged();
	//	}
	//}


	//// ENEMY_CHARACTERSとの衝突
	//vector<Collision<CharacterID>> now_collisions_with_enemy_character;
	//for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
	//	if (enemy_character->collidant->is_collided_with(collidant) == true) {
	//		if (is_last_collided_with_character(enemy_character->id) == true) {
	//			int damage_wait = 1.0 / enemy_character->DPS * 1000;
	//			if (DxLib::GetNowCount() > get_last_collision(enemy_character->id).last_damaged_clock + damage_wait) {
	//				damaged();
	//				now_collisions_with_enemy_character.push_back(Collision(
	//					enemy_character->id,
	//					get_last_collision(enemy_character->id).last_collided_clock));
	//			}
	//			else {
	//				now_collisions_with_enemy_character.push_back(Collision(
	//					enemy_character->id,
	//					get_last_collision(enemy_character->id).last_collided_clock,
	//					get_last_collision(enemy_character->id).last_damaged_clock)
	//				);
	//			}
	//		}
	//		if (is_last_collided_with_character(enemy_character->id) == false) {
	//			damaged();
	//			now_collisions_with_enemy_character.push_back(Collision(enemy_character->id));
	//		}
	//	}
	//}
	//last_collisions_with_enemy_character.clear();
	//last_collisions_with_enemy_character = now_collisions_with_enemy_character;



	// ZAKO_CHARACTERSとの衝突
	vector<Collision<CharacterID>> now_collisions_with_zako_character;
	for (const auto& zako_character : *Field::ZAKO_CHARACTERS) {
		if (zako_character->collidant->is_collided_with(collidant) == true) {
			if (is_last_collided_with_character(zako_character->id) == true) {
				int damage_wait = 1.0 / zako_character->DPS * 1000;
				if (DxLib::GetNowCount() > get_last_collision(zako_character->id).last_damaged_clock + damage_wait) {
					damaged();
					now_collisions_with_zako_character.push_back(Collision(
						zako_character->id,
						get_last_collision(zako_character->id).last_collided_clock));
				}
				else {
					now_collisions_with_zako_character.push_back(Collision(
						zako_character->id,
						get_last_collision(zako_character->id).last_collided_clock,
						get_last_collision(zako_character->id).last_damaged_clock)
					);
				}
			}
			if (is_last_collided_with_character(zako_character->id) == false) {
				damaged();
				now_collisions_with_zako_character.push_back(Collision(zako_character->id));
			}
		}
	}
	last_collisions_with_zako_character.clear();
	last_collisions_with_zako_character = now_collisions_with_zako_character;



	// BOSS_CHARACTERSとの衝突
	vector<Collision<CharacterID>> now_collisions_with_boss_character;
	for (const auto& boss_character : *Field::BOSS_CHARACTERS) {
		if (boss_character->collidant->is_collided_with(collidant) == true) {
			if (is_last_collided_with_character(boss_character->id) == true) {
				int damage_wait = 1.0 / boss_character->DPS * 1000;
				if (DxLib::GetNowCount() > get_last_collision(boss_character->id).last_damaged_clock + damage_wait) {
					damaged();
					now_collisions_with_boss_character.push_back(Collision(
						boss_character->id,
						get_last_collision(boss_character->id).last_collided_clock));
				}
				else {
					now_collisions_with_boss_character.push_back(Collision(
						boss_character->id,
						get_last_collision(boss_character->id).last_collided_clock,
						get_last_collision(boss_character->id).last_damaged_clock)
					);
				}
			}
			if (is_last_collided_with_character(boss_character->id) == false) {
				damaged();
				now_collisions_with_boss_character.push_back(Collision(boss_character->id));
			}
		}
	}
	last_collisions_with_boss_character.clear();
	last_collisions_with_boss_character = now_collisions_with_boss_character;
}


bool MyCharacter::is_last_collided_with_character(CharacterID given_enemy_character_id) {
	//if (last_damaged_clocks.count(given_enemy_character_id) == 0) {
	//	return false;
	//}
	//else if (last_damaged_clocks.count(given_enemy_character_id) == 1) {
	//	return true;
	//}
	bool found = false;
	for (const auto& last_collision_with_zako_character : last_collisions_with_zako_character) {
		if (last_collision_with_zako_character.id == given_enemy_character_id) found = true;
	}
	for (const auto& collision : last_collisions_with_boss_character) {
		if ( collision.id == given_enemy_character_id ) found = true;
	}
	return found;
}


bool MyCharacter::is_last_collided_with_bullet(BulletID given_bullet_id) {
	bool found = false;
	for (const auto& last_collision_with_enemy_bullet : last_collisions_with_enemy_bullet) {
		if (last_collision_with_enemy_bullet.id == given_bullet_id) found = true;
	}
	return found;
}


bool MyCharacter::is_last_collided_with_laser(LaserID given_laser_id) {
	bool found = false;
	for (const auto& last_collision_with_enemy_laser : last_collisions_with_enemy_laser) {
		if (last_collision_with_enemy_laser.id == given_laser_id) found = true;
	}
	return found;
}


Collision<CharacterID>& MyCharacter::get_last_collision(CharacterID given_enemy_character_id) {

	for (auto& last_collision_with_zako_character : last_collisions_with_zako_character) {
		if (last_collision_with_zako_character.id == given_enemy_character_id) {
			return last_collision_with_zako_character;
		}
	}

	for (auto& last_collision_with_boss_character : last_collisions_with_boss_character) {
		if (last_collision_with_boss_character.id == given_enemy_character_id) {
			return last_collision_with_boss_character;
		}
	}

}


Collision<LaserID>& MyCharacter::get_last_collision(LaserID given_enemy_laser_id) {
	for (auto& last_collision_with_enemy_laser : last_collisions_with_enemy_laser) {
		if (last_collision_with_enemy_laser.id == given_enemy_laser_id) {
			return last_collision_with_enemy_laser;
		}
	}
}

void MyCharacter::reset_position() {
	position->x = MyCharacter::INITIAL_POSITION_X;
	position->y = MyCharacter::INITIAL_POSITION_Y;
	collidant->update(position);
}

void MyCharacter::request_invincible(int invincible_time) {
	end_invincible_clock = DxLib::GetNowCount() + invincible_time;
	is_invincible = true;
}