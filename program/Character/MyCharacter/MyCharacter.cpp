#include <string>
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
#include "Effect/CrashEffect/CrashEffect.h"
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
const unsigned int MyCharacter::CRASH_EFFECT_VISIBLE_DURATION = 3000;
bool MyCharacter::LAUNCH_SUSPENDED_FLAG = false;
bool MyCharacter::SLOWMOVE_FLAG = false;
const unsigned int MyCharacter::BLINK_LIGHT_ON_DURATION = 200;
const unsigned int MyCharacter::BLINK_LIGHT_OFF_DURATION = 200;
const unsigned int MyCharacter::BLINK_DURATION = 2000;



MyCharacter::MyCharacter(wstring character_name) :
	name(character_name),
	shotFrequency(10.0),
	moveSpeed(300.0),
	lastLaunchTickedClock(DxLib::GetNowCount()),
	invincibleEndClock(DxLib::GetNowCount()),
	isInvincible(false),
	crashEffectId(0),
	lastCrashedClock(DxLib::GetNowCount()),
	isThereMyCrashEffect(false),
	isVisible(true),
	isBlinking(false),
	lastBlinkStartedClock(DxLib::GetNowCount()),
	lastBlinkSwitchedClock(DxLib::GetNowCount())
{
}


void MyCharacter::Update() {
	int current_clock = DxLib::GetNowCount();
	
	RespondToKeyInput();
	RegulatePosition();
	collidant->update(position);

	// デバッグ表示用変数更新
	DebugParams::MY_CHARACTER_INFIELD_X = position->x;
	DebugParams::MY_CHARACTER_INFIELD_Y = position->y;
	DebugParams::MY_CHARACTER_DRAW_X = position->get_draw_position().x;
	DebugParams::MY_CHARACTER_DRAW_Y = position->get_draw_position().y;

	// 無敵のとき無敵終了予定時刻を超過していたら無敵終了
	if (isInvincible && current_clock >= invincibleEndClock) {
			isInvincible = false;
	}
	
	// 点滅中のとき
	if (isBlinking) {

		int blink_end_clock = lastBlinkStartedClock + BLINK_DURATION;

		// 点滅終了時刻を過ぎていたら点滅終了
		if (current_clock > blink_end_clock) {
			isBlinking = false;
			isVisible = true;  // 表示状態に戻す
		}
		//点と滅の切り替え
		else {
			int next_blink_switch_clock;
			if (isVisible) {
				next_blink_switch_clock = lastBlinkSwitchedClock + BLINK_LIGHT_ON_DURATION;
				if (current_clock > next_blink_switch_clock) {
					isVisible = false;
					lastBlinkSwitchedClock = current_clock;
				}
			}
			else {
				next_blink_switch_clock = lastBlinkSwitchedClock + BLINK_LIGHT_OFF_DURATION;
				if (current_clock > next_blink_switch_clock) {
					isVisible = true;
					lastBlinkSwitchedClock = current_clock;
				}
			}
		}
	}
	lastUpdatedClock = DxLib::GetNowHiPerformanceCount();
}


void MyCharacter::RespondToKeyInput() {

	if (GameConductor::GAMEOVER_FLAG == false) {


		bool prev_input1_pushed = KeyPushFlags::INPUT_1;
		bool now_input1_pushed = (AppSession::PAD_BUFFER & PAD_INPUT_1) != 0;


		// INPUT1
		if ( prev_input1_pushed == false && now_input1_pushed == true ) {	//Zキーを今まで押していなかったが、押し始めた瞬間
			if (LAUNCH_SUSPENDED_FLAG == false) {
				KeyPushFlags::INPUT_1 = true;
				LaunchShot();
				lastLaunchTickedClock = DxLib::GetNowCount();
			}
		}

		if ( prev_input1_pushed == true && now_input1_pushed == false ) {	//Zキーを今まで押していたが、離した瞬間
			KeyPushFlags::INPUT_1 = false;
		}

		if (prev_input1_pushed == true && now_input1_pushed == true) {	//Zキーを今まで押していたし、今も押している
			int launch_wait = 1.0 / shotFrequency * 1000;
			if (DxLib::GetNowCount() > lastLaunchTickedClock + launch_wait) {
				if (LAUNCH_SUSPENDED_FLAG == false) {
					LaunchShot();
					lastLaunchTickedClock = DxLib::GetNowCount();
				}
			}
		}

		//Xキー
		if (KeyPushFlags::X == false && AppSession::KBD_BUFFER[KEY_INPUT_X] == 1) {
			KeyPushFlags::X = true;
		}
		if (KeyPushFlags::X == true && AppSession::KBD_BUFFER[KEY_INPUT_X] == 0) {
			KeyPushFlags::X = false;
		}


		//↑↓←→キー
		bool now_input_up_pushed = (AppSession::PAD_BUFFER & PAD_INPUT_UP) != 0;
		bool now_input_left_pushed = (AppSession::PAD_BUFFER & PAD_INPUT_LEFT) != 0;
		bool now_input_down_pushed = (AppSession::PAD_BUFFER & PAD_INPUT_DOWN) != 0;
		bool now_input_right_pushed = (AppSession::PAD_BUFFER & PAD_INPUT_RIGHT) != 0;

		if (now_input_up_pushed == true) {
			if (now_input_right_pushed == true) {
				MoveUpRight();
			}
			else if (now_input_left_pushed == true) {
				MoveUpLeft();
			}
			else {
				MoveUp();
			}
		}
		else if (now_input_down_pushed == true) {
			if (now_input_right_pushed == true) {
				MoveDownRight();
			}
			else if (now_input_left_pushed == true) {
				MoveDownLeft();
			}
			else {
				MoveDown();
			}
		}
		else {
			if (now_input_right_pushed == true) {
				MoveRight();
			}
			else if (now_input_left_pushed == true) {
				MoveLeft();
			}
		}


		//左SHIFTキー または LBボタン または RBボタン
		bool now_slowmove_pushed
			= AppSession::KBD_BUFFER[ KEY_INPUT_LSHIFT ] == 1
			|| (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0
			|| (DxLib::GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) != 0;

		if (now_slowmove_pushed == true) {
			MyCharacter::SLOWMOVE_FLAG = true;
		}
		else {
			MyCharacter::SLOWMOVE_FLAG = false;
		}
	}
}


void MyCharacter::MoveUp() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - lastUpdatedClock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = moveSpeed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = moveSpeed * update_delta_time / 1000 / 1000;
	}
	position->y += distance;
}


void MyCharacter::MoveDown() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - lastUpdatedClock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = moveSpeed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = moveSpeed * update_delta_time / 1000 / 1000;
	}
	position->y -= distance;
}


void MyCharacter::MoveRight() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - lastUpdatedClock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = moveSpeed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = moveSpeed * update_delta_time / 1000 / 1000;
	}
	position->x += distance;
}


void MyCharacter::MoveLeft() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - lastUpdatedClock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = moveSpeed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = moveSpeed * update_delta_time / 1000 / 1000;
	}
	position->x -= distance;
}


void MyCharacter::MoveUpRight() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - lastUpdatedClock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = moveSpeed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = moveSpeed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(1.0 / 4.0 * pi);
	double distance_y = distance * sin(1.0 / 4.0 * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::MoveDownRight() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - lastUpdatedClock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = moveSpeed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = moveSpeed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(-(1.0 / 4.0) * pi);
	double distance_y = distance * sin(-(1.0 / 4.0) * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::MoveUpLeft() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - lastUpdatedClock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = moveSpeed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = moveSpeed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(3.0 / 4.0 * pi);
	double distance_y = distance * sin(3.0 / 4.0 * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::MoveDownLeft() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - lastUpdatedClock;
	double distance;
	if (SLOWMOVE_FLAG == true) {
		distance = moveSpeed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = moveSpeed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(-(3.0 / 4.0) * pi);
	double distance_y = distance * sin(-(3.0 / 4.0) * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::RegulatePosition() {
	if (position->x < InFieldPosition::MIN_MOVABLE_BOUNDARY_X)
		position->x = InFieldPosition::MIN_MOVABLE_BOUNDARY_X;

	if (position->y < InFieldPosition::MIN_MOVABLE_BOUNDARY_Y)
		position->y = InFieldPosition::MIN_MOVABLE_BOUNDARY_Y;

	if (position->x > InFieldPosition::MAX_MOVABLE_BOUNDARY_X)
		position->x = InFieldPosition::MAX_MOVABLE_BOUNDARY_X;

	if (position->y > InFieldPosition::MAX_MOVABLE_BOUNDARY_Y)
		position->y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y;
}


void MyCharacter::LaunchShot() {;
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


void MyCharacter::GetDamaged() {
	if (hp > 0) {
		hp += -1;
		DxLib::PlaySoundMem(SoundHandles::MYHIT, DX_PLAYTYPE_BACK);
	}
}


//bool MyCharacter::is_collided_with_enemy_offensives() {
//	bool collided_with_no_less_than_one_enemy_offensive_flag = false;
//	for (const auto& enemy_bullet : *Field::ENEMY_BULLETS) {
//		if (collidant->is_collided_with(enemy_bullet.second->collidant)) collided_with_no_less_than_one_enemy_offensive_flag = true;
//	}
//	return collided_with_no_less_than_one_enemy_offensive_flag;
//}


void MyCharacter::DealCollision() {
	
	// ENEMY_BULLETSとの衝突
	for (const auto& enemy_bullet : *Field::ENEMY_BULLETS) {
		if (IsLastCollidedWithBullet(enemy_bullet.first) == false						// 前回はそいつと衝突していなかったが、
			&& collidant->is_collided_with(enemy_bullet.second->collidant) == true)	// 現在は衝突している
		{
			GetDamaged();
		}
	}
	lastCollisionsWithEnemyBullet.clear();
	for (const auto& enemy_bullet : *Field::ENEMY_BULLETS) {
		if (collidant->is_collided_with(enemy_bullet.second->collidant) == true) {
			lastCollisionsWithEnemyBullet.push_back(Collision<BulletID>(enemy_bullet.first));
		}
	}


	//unordered_map<CharacterID, int> damaged_clocks;
	//for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
	//	if (is_last_collided_with(enemy_character->id) == false					// 前回はそいつと衝突していなかったが、
	//		&& collidant->is_collided_with(enemy_character->collidant) == true)	// 現在は衝突している
	//	{
	//		GetDamaged();
	//	}
	//	else if (is_last_collided_with(enemy_character->id) == true				// 前回もそいつと衝突していたし、
	//		&& collidant->is_collided_with(enemy_character->collidant) == true)	// 現在も衝突している
	//	{
	//		int damage_wait = 1.0 / enemy_character->DPS * 1000;
	//		if (DxLib::GetNowCount() > last_damaged_clocks.at(enemy_character->id) + damage_wait) {
	//			GetDamaged();
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
				if (IsLastCollidedWithLaser(enemy_laser.first) == true) {
					int damage_wait = 1.0 / enemy_laser.second->dps * 1000;
					if (DxLib::GetNowCount() > GetLastCollision(enemy_laser.first).last_damaged_clock + damage_wait) {
						GetDamaged();
						now_collisions_with_enemy_laser.push_back(Collision(
							enemy_laser.first,
							GetLastCollision(enemy_laser.first).last_collided_clock));
					}
					else {
						now_collisions_with_enemy_laser.push_back(Collision(
							enemy_laser.first,
							GetLastCollision(enemy_laser.first).last_collided_clock,
							GetLastCollision(enemy_laser.first).last_damaged_clock)
						);
					}
				}
				if (IsLastCollidedWithLaser(enemy_laser.first) == false) {
					GetDamaged();
					now_collisions_with_enemy_laser.push_back(Collision(enemy_laser.first));
				}
			}
		}
	}
	lastCollisionsWithEnemyLaser.clear();
	lastCollisionsWithEnemyLaser = now_collisions_with_enemy_laser;
	//for (const auto& enemy_laser : *Field::ENEMY_LASERS) {
	//	if (collidant->is_collided_with(enemy_laser.second->collidant) == true) {
	//		GetDamaged();
	//	}
	//}


	//// ENEMY_CHARACTERSとの衝突
	//vector<Collision<CharacterID>> now_collisions_with_enemy_character;
	//for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
	//	if (enemy_character->collidant->is_collided_with(collidant) == true) {
	//		if (IsLastCollidedWithCharacter(enemy_character->id) == true) {
	//			int damage_wait = 1.0 / enemy_character->DPS * 1000;
	//			if (DxLib::GetNowCount() > GetLastCollision(enemy_character->id).last_damaged_clock + damage_wait) {
	//				GetDamaged();
	//				now_collisions_with_enemy_character.push_back(Collision(
	//					enemy_character->id,
	//					GetLastCollision(enemy_character->id).last_collided_clock));
	//			}
	//			else {
	//				now_collisions_with_enemy_character.push_back(Collision(
	//					enemy_character->id,
	//					GetLastCollision(enemy_character->id).last_collided_clock,
	//					GetLastCollision(enemy_character->id).last_damaged_clock)
	//				);
	//			}
	//		}
	//		if (IsLastCollidedWithCharacter(enemy_character->id) == false) {
	//			GetDamaged();
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
			if (IsLastCollidedWithCharacter(zako_character->id) == true) {
				int damage_wait = 1.0 / zako_character->DPS * 1000;
				if (DxLib::GetNowCount() > GetLastCollision(zako_character->id).last_damaged_clock + damage_wait) {
					GetDamaged();
					now_collisions_with_zako_character.push_back(Collision(
						zako_character->id,
						GetLastCollision(zako_character->id).last_collided_clock));
				}
				else {
					now_collisions_with_zako_character.push_back(Collision(
						zako_character->id,
						GetLastCollision(zako_character->id).last_collided_clock,
						GetLastCollision(zako_character->id).last_damaged_clock)
					);
				}
			}
			if (IsLastCollidedWithCharacter(zako_character->id) == false) {
				GetDamaged();
				now_collisions_with_zako_character.push_back(Collision(zako_character->id));
			}
		}
	}
	lastCollisionsWithZakoCharacter.clear();
	lastCollisionsWithZakoCharacter = now_collisions_with_zako_character;



	// BOSS_CHARACTERSとの衝突
	vector<Collision<CharacterID>> now_collisions_with_boss_character;
	for (const auto& boss_character : *Field::BOSS_CHARACTERS) {
		if (boss_character->collidant->is_collided_with(collidant) == true) {
			if (IsLastCollidedWithCharacter(boss_character->id) == true) {
				int damage_wait = 1.0 / boss_character->DPS * 1000;
				if (DxLib::GetNowCount() > GetLastCollision(boss_character->id).last_damaged_clock + damage_wait) {
					GetDamaged();
					now_collisions_with_boss_character.push_back(Collision(
						boss_character->id,
						GetLastCollision(boss_character->id).last_collided_clock));
				}
				else {
					now_collisions_with_boss_character.push_back(Collision(
						boss_character->id,
						GetLastCollision(boss_character->id).last_collided_clock,
						GetLastCollision(boss_character->id).last_damaged_clock)
					);
				}
			}
			if (IsLastCollidedWithCharacter(boss_character->id) == false) {
				GetDamaged();
				now_collisions_with_boss_character.push_back(Collision(boss_character->id));
			}
		}
	}
	lastCollisionsWithBossCharacter.clear();
	lastCollisionsWithBossCharacter = now_collisions_with_boss_character;
}


bool MyCharacter::IsLastCollidedWithCharacter(CharacterID given_enemy_character_id) {
	//if (last_damaged_clocks.count(given_enemy_character_id) == 0) {
	//	return false;
	//}
	//else if (last_damaged_clocks.count(given_enemy_character_id) == 1) {
	//	return true;
	//}
	bool found = false;
	for (const auto& last_collision_with_zako_character : lastCollisionsWithZakoCharacter) {
		if (last_collision_with_zako_character.id == given_enemy_character_id) found = true;
	}
	for (const auto& collision : lastCollisionsWithBossCharacter) {
		if ( collision.id == given_enemy_character_id ) found = true;
	}
	return found;
}


bool MyCharacter::IsLastCollidedWithBullet(BulletID given_bullet_id) {
	bool found = false;
	for (const auto& last_collision_with_enemy_bullet : lastCollisionsWithEnemyBullet) {
		if (last_collision_with_enemy_bullet.id == given_bullet_id) found = true;
	}
	return found;
}


bool MyCharacter::IsLastCollidedWithLaser(LaserID given_laser_id) {
	bool found = false;
	for (const auto& last_collision_with_enemy_laser : lastCollisionsWithEnemyLaser) {
		if (last_collision_with_enemy_laser.id == given_laser_id) found = true;
	}
	return found;
}


Collision<CharacterID>& MyCharacter::GetLastCollision(CharacterID given_enemy_character_id) {

	for (auto& last_collision_with_zako_character : lastCollisionsWithZakoCharacter) {
		if (last_collision_with_zako_character.id == given_enemy_character_id) {
			return last_collision_with_zako_character;
		}
	}

	for (auto& last_collision_with_boss_character : lastCollisionsWithBossCharacter) {
		if (last_collision_with_boss_character.id == given_enemy_character_id) {
			return last_collision_with_boss_character;
		}
	}

}


Collision<LaserID>& MyCharacter::GetLastCollision(LaserID given_enemy_laser_id) {
	for (auto& last_collision_with_enemy_laser : lastCollisionsWithEnemyLaser) {
		if (last_collision_with_enemy_laser.id == given_enemy_laser_id) {
			return last_collision_with_enemy_laser;
		}
	}
}

void MyCharacter::InitializePosition() {
	position->x = MyCharacter::INITIAL_POSITION_X;
	position->y = MyCharacter::INITIAL_POSITION_Y;
	collidant->update(position);
}

void MyCharacter::Crash() {
	// 自機クラッシュ時SE
	DxLib::PlaySoundMem(SoundHandles::MYCRASH, DX_PLAYTYPE_BACK);

	// 自機のクラッシュ時エフェクト
	crashEffectId = CrashEffect::GENERATE_ID();
	(*Field::MY_EFFECTS)[ crashEffectId ] = make_unique<CrashEffect>(
		position->x,
		position->y
	);
	lastCrashedClock = DxLib::GetNowCount();
	isThereMyCrashEffect = true;

	// 自機位置リセット
	InitializePosition();
	
	// 無敵開始
	ReserveInvincible(3000);
	
	// 自機点滅
	StartBlinking();
}

void MyCharacter::ReserveInvincible(int invincible_time) {
	invincibleEndClock = DxLib::GetNowCount() + invincible_time;
	isInvincible = true;
}


void MyCharacter::StartBlinking() {
	isBlinking = true;
	lastBlinkStartedClock = DxLib::GetNowCount();
	lastBlinkSwitchedClock = DxLib::GetNowCount();
	isVisible = true;  // 最初は見える状態からスタート
}
