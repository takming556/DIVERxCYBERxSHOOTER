#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv4C.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/Bullet.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Offensive/Laser/PolarLaser.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;

const unsigned int ZkChrStg3Wv4C::INIT_POS_X = Field::PIXEL_SIZE_X / 2;
const unsigned int ZkChrStg3Wv4C::INIT_POS_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y + 100;
const double ZkChrStg3Wv4C::INIT_ARG = 3.0 / 2.0 * pi;
const double ZkChrStg3Wv4C::INIT_SPEED = 100;
const unsigned int ZkChrStg3Wv4C::INIT_HP = 30;
const unsigned int ZkChrStg3Wv4C::COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg3Wv4C::PORTAL_POS_Y = 625;
const double ZkChrStg3Wv4C::PORTAL_INIT_ARG = 0.0 * pi;	// 関数化
const double ZkChrStg3Wv4C::PORTAL_INIT_SPEED = 100;
const unsigned int ZkChrStg3Wv4C::PORTAL_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv4C::LASER_LENGTH = 800;
const unsigned int ZkChrStg3Wv4C::LASER_WIDTH = 30;
const double ZkChrStg3Wv4C::LASER_DPS = 10.0;
const unsigned int ZkChrStg3Wv4C::LASER_NOTIFY_COLOR = (GetColor(100, 100, 100));	// 予告線の色指定

const double ZkChrStg3Wv4C::DRAW_EXTRATE = 0.07;

vector<unsigned int> ZkChrStg3Wv4C::PORTAL_IDS;
vector<LaserID> ZkChrStg3Wv4C::LASER_IDS;
Stg3WAVE4CMode ZkChrStg3Wv4C::MODE = Stg3WAVE4CMode::ENTER;

ZkChrStg3Wv4C::ZkChrStg3Wv4C(CharacterID given_id) :
	Character(
		given_id,
		INIT_POS_X,
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)
	),
	arg(INIT_ARG),
	speed(INIT_SPEED),
	portal_arg(PORTAL_INIT_ARG),
	portal_speed(PORTAL_INIT_SPEED),
	portal_id_count(0),
	draw_position_begin(0,0),
	draw_position_end(0,0),
	laser_notify_count(0),
	laser_emit_count(0),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	kept_clock(DxLib::GetNowCount()),
	last_tick_generated_clock(DxLib::GetNowCount())
	// mode(Stg3WAVE4CMode::ENTER)
{
	for (int i = 0; i < 6; ++i) {
		int pos_x = Field::PIXEL_SIZE_X / 2;
		if (i < 3) {
			pos_x += -100 + (-80) * i;
		}
		else {
			pos_x += 100 + 80 * (i - 3);
		}
		portal_poses_x.push_back(pos_x);
	}
}

void ZkChrStg3Wv4C::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;

	if (MODE == Stg3WAVE4CMode::ENTER) {
		if (elapsed_time > 2000) {
			speed = 0;
			MODE = Stg3WAVE4CMode::PORTAL;
			kept_clock = DxLib::GetNowCount();
		}
	}
	else if (MODE == Stg3WAVE4CMode::PORTAL) {
		if (tick_generated_delta_time > 800 && portal_id_count < 6) {
			portal_arg = 0.0 * pi;
			unsigned int portal_offensive_id = Bullet::GENERATE_ID();
			(*Field::ENEMY_BULLETS)[portal_offensive_id] = make_unique<StraightShot>(
				position->x,
				position->y,
				portal_arg,
				portal_speed,
				PORTAL_COLLIDANT_SIZE,
				1,
				SkinID::STG3_WAVE4_C_PORTAL
				);
			++portal_id_count;
			PORTAL_IDS.push_back(portal_offensive_id);

			portal_arg = 1.0 * pi;
			// portal_id[portal_id_count] = Bullet::GENERATE_ID();
			portal_offensive_id = Bullet::GENERATE_ID();
			(*Field::ENEMY_BULLETS)[portal_offensive_id] = make_unique<StraightShot>(
				position->x,
				position->y,
				portal_arg,
				portal_speed,
				PORTAL_COLLIDANT_SIZE,
				1,
				SkinID::STG3_WAVE4_C_PORTAL
				);
			++portal_id_count;
			PORTAL_IDS.push_back(portal_offensive_id);

			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

			last_tick_generated_clock = DxLib::GetNowCount();
		}
		if (elapsed_time > 2600 && portal_id_count >= 6) {
			portal_speed = 0;
			for (auto& portal_id : PORTAL_IDS) {
				if (Field::ENEMY_BULLETS->count(portal_id) == 1) {
					(*Field::ENEMY_BULLETS)[portal_id]->set_speed(portal_speed);
				}
			}
			MODE = Stg3WAVE4CMode::NOTIFY;
			kept_clock = DxLib::GetNowCount();
		}
	}
	else if (MODE == Stg3WAVE4CMode::NOTIFY) {
		if (elapsed_time > 1000){
			if (laser_notify_count == 0) {														// ここを通る1回目だけ自キャラの座標を取得
				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				for (int i = 0; i < 6; ++i) {
					double laser_delta_x_mychr = my_chr_pos.x - portal_poses_x.at(i);
					double laser_delta_y_mychr = my_chr_pos.y - PORTAL_POS_Y;
					double laser_arg = atan2(laser_delta_y_mychr, laser_delta_x_mychr);			// 根源から自機へ向いた角度

					double laser_notify_end_x = portal_poses_x.at(i) + cos(laser_arg) * LASER_LENGTH;	// InFieldPositionで終端座標の算出
					double laser_notify_end_y = PORTAL_POS_Y + sin(laser_arg) * LASER_LENGTH;

					InFieldPosition position_begin(portal_poses_x.at(i), PORTAL_POS_Y);
					InFieldPosition position_end(laser_notify_end_x, laser_notify_end_y);

					draw_position_begin = position_begin.get_draw_position();			// InFieldPostionからPositionに変換
					draw_position_end = position_end.get_draw_position();
					draw_positions_begin.push_back(draw_position_begin);
					draw_positions_end.push_back(draw_position_end);
					laser_args.push_back(laser_arg);
				}
				++laser_notify_count;
			}
			for (int i = 0; i < 6; ++i) {
				DxLib::DrawLine(	//　予告線を描画
					draw_positions_begin.at(i).x,
					draw_positions_begin.at(i).y,
					draw_positions_end.at(i).x,
					draw_positions_end.at(i).y,
					LASER_NOTIFY_COLOR
				);
			}
		}
		if (elapsed_time > 3000) {
			MODE = Stg3WAVE4CMode::LASER;
			kept_clock = DxLib::GetNowCount();
		}
	}
	else if (MODE == Stg3WAVE4CMode::LASER) {
		if (laser_emit_count == 0) {
			for (int i = 0; i < 6; ++i) {
				LaserID laser_id = Laser::GENERATE_ID();
				(*Field::ENEMY_LASERS)[laser_id] = make_unique<PolarLaser>(
					portal_poses_x.at(i),
					PORTAL_POS_Y,
					laser_args.at(i),
					LASER_LENGTH,
					LASER_WIDTH,
					LASER_DPS,
					true,
					SkinID::STG3_WAVE4_C_LASER
					);
				LASER_IDS.push_back(laser_id);
			}
			++laser_emit_count;
		}

		if (elapsed_time > 3000) {
			for (auto& portal_id : PORTAL_IDS) {	// 根源を消す
				(*Field::ENEMY_BULLETS).erase(portal_id);
			}
			for (auto& laser_id : LASER_IDS) {	// レーザーを消す
				(*Field::ENEMY_LASERS).erase(laser_id);

			}
			portal_poses_x.clear();
			laser_args.clear();
			draw_positions_begin.clear();
			draw_positions_end.clear();
			PORTAL_IDS.clear();
			LASER_IDS.clear();				// vector全部clear()してみたけどだめだった
			MODE = Stg3WAVE4CMode::EXIT;
			kept_clock = DxLib::GetNowCount();
		}
	}
	else if (MODE == Stg3WAVE4CMode::EXIT) {
		arg = 1.0 / 2.0 * pi;
		speed = 100;
	}

	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);

	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}

void ZkChrStg3Wv4C::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_GOZGOK, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}