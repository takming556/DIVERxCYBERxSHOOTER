#include <string>
#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Character/Character.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/Neon.h"
#include "CollideRealm/CollideCircle.h"
#include "Position/InFieldPosition.h"
#include "FontHandles.h"
#include "Colors.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"
#include "Field.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Offensive/Bullet/CurvingShot.h"
#include "Offensive/Bullet/HomingShot/HomingShot.h"
#include "Offensive/Laser/PolarLaser.h"

using std::string;
using std::make_unique;
using std::numbers::pi;

const string Neon::NAME("雷ねおん");
const int Neon::INITIAL_POS_X = 310;
const int Neon::INITIAL_POS_Y = 620;
const unsigned int Neon::INITIAL_COLLIDANT_SIZE = 60;
const double Neon::DRAW_EXTRATE = 0.07;

const unsigned int Neon::NM2_STRAIGHT_NOZZLES = 12;
const unsigned int Neon::NM2_STRAIGHT_INTERVAL = 300;
const double Neon::NM2_STRAIGHT_SHOT_SPEED = 80;
const unsigned int Neon::NM2_STRAIGHT_COLLIDANT_SIZE = 7;

const unsigned int Neon::NM2_LASER_LENGTH = 700;
const unsigned int Neon::NM2_LASER_WIDTH = 50;
const double Neon::NM2_LASER_INIT_ARG = 3.0 / 4.0 * pi;
const unsigned int Neon::NM2_LASER_AWAIT_INTERVAL = 3000;
const unsigned int Neon::NM2_LASER_NOTIFY_INTERVAL = 2000;
const unsigned int Neon::NM2_LASER_EMIT_INTERVAL = 3000;

const unsigned int Neon::NM3_NOZZLES = 9;
const double Neon::NM3_NOZZLES_ROTATE_SPEED = 1.0 / 10.0 * pi;
const unsigned int Neon::NM3_INTERVAL = 120;
const double Neon::NM3_SHOT_SPEED = 300;
const unsigned int Neon::NM3_COLLIDANT_SIZE = 10;

const unsigned int Neon::SP2_HAIL_NOZZLES = 27;
const unsigned int Neon::SP2_HAIL_INTERVAL = 1000;
const double Neon::SP2_HAIL_INIT_ARG = 1.0 / 27.0 * 2.0 * pi;
const double Neon::SP2_HAIL_INIT_SPEED = 100;
const double Neon::SP2_HAIL_INIT_CURVE_SPEED = 1.0 / 16.0 * pi;
const unsigned int Neon::SP2_HAIL_COLLIDANT_SIZE = 8;

const unsigned int Neon::SP4_SHUFFLE_CARD_NUM = 2;
const unsigned int Neon::SP4_SHUFFLE_CARD_DISTANCE = 100;
const unsigned int Neon::SP4_SHUFFLE_TICK_INTERVAL = 300;
const unsigned int Neon::SP4_SHUFFLE_FIRE_INTERVAL = 200;
const unsigned int Neon::SP4_SHUFFLE_TICK_COUNT_MAX = 10;
const double Neon::SP4_SHUFFLE_INIT_ARG = 1.0 * pi;
const double Neon::SP4_SHUFFLE_INIT_SPEED = 200;
const double Neon::SP4_SHUFFLE_DOWN_ARG = 3.0 / 2.0 * pi;
const double Neon::SP4_SHUFFLE_DOWN_SPEED = 80;
const double Neon::SP4_SHUFFLE_EXIT_ARG = 0.0 * pi;
const double Neon::SP4_SHUFFLE_EXIT_SPEED = 200;
const unsigned int Neon::SP4_SHUFFLE_COLLIDANT_SIZE = 10;
const unsigned int Neon::SP4_SHUFFLE_DOWN_CRITERION_X = 40;
const unsigned int Neon::SP4_SHUFFLE_EXIT_CRITERION_Y = 40;

const double Neon::SP4_TRAIN_INIT_ARG = 3.0 / 2.0 * pi;
const double Neon::SP4_TRAIN_INIT_SPEED = 150;
const unsigned int Neon::SP4_TRAIN_COLLIDANT_SIZE = 10;
const unsigned int Neon::SP4_TRAIN_TICK_INTERVAL = 100;
const unsigned int Neon::SP4_TRAIN_FIRE_INTERVAL = 10000;
const unsigned int Neon::SP4_TRAIN_TICK_COUNT_MAX = 5;

const unsigned int Neon::INITIAL_HP = 1000;

// 100% -  90% NORMAL1
//  90% -  75% SP1
//  75% -  65% NORMAL2
//  65% -  50% SP2
//  50% -  40% NORMAL3
//  40% -  25% SP3
//  25% -  15% NORMAL4
//  15% -   0% SP4

const double Neon::SP1_ACTIVATE_HP_RATIO = 90.0 / 100.0;
const double Neon::SP1_TERMINATE_HP_RATIO = 75.0 / 100.0;
const double Neon::SP2_ACTIVATE_HP_RATIO = 65.0 / 100.0;
const double Neon::SP2_TERMINATE_HP_RATIO = 50.0 / 100.0;
const double Neon::SP3_ACTIVATE_HP_RATIO = 40.0 / 100.0;
const double Neon::SP3_TERMINATE_HP_RATIO = 25.0 / 100.0;
const double Neon::SP4_ACTIVATE_HP_RATIO = 15.0 / 100.0;


const unsigned int Neon::SP1_ACCOMPLISH_BONUS = 150000;
const unsigned int Neon::SP2_ACCOMPLISH_BONUS = 200000;
const unsigned int Neon::SP3_ACCOMPLISH_BONUS = 350000;
const unsigned int Neon::SP4_ACCOMPLISH_BONUS = 500000;

Neon::Neon() :
	Character(
		CharacterID::NEON,
		INITIAL_POS_X,
		INITIAL_POS_Y,
		INITIAL_HP,
		make_unique<CollideCircle>(INITIAL_POS_X, INITIAL_POS_Y, INITIAL_COLLIDANT_SIZE)
	),
	BossCharacter(NAME),
	status(NeonStatus::NORMAL2),
	nm2_straight_last_generated_clock(DxLib::GetNowCount()),
	nm2_laser_arg(NM2_LASER_INIT_ARG),
	nm2_laser_notify_count(0),
	nm2_laser_kept_clock(DxLib::GetNowCount()),
	nm2_laser_status(NeonNormal2LaserStatus::AWAIT),
	nm3_shot_arg(0.0),
	nm3_last_generated_clock(DxLib::GetNowCount()),
	sp2_hail_curve_speed(0.0),
	sp2_hail_last_generated_clock(DxLib::GetNowCount()),
	sp4_shuffle_tick_last_generated_clock(DxLib::GetNowCount()),
	sp4_shuffle_fire_last_generated_clock(DxLib::GetNowCount()),
	sp4_shuffle_tick_count(0),
	sp4_shuffle_fire_count(0),
	sp4_shuffle_down_last_changed_clock(DxLib::GetNowCount()),
	sp4_shuffle_arg(SP4_SHUFFLE_INIT_ARG),
	sp4_shuffle_speed(SP4_SHUFFLE_INIT_SPEED),
	sp4_train_tick_last_generated_clock(DxLib::GetNowCount()),
	sp4_train_fire_last_generated_clock(0),
	sp4_train_tick_count(0)

{
}

void Neon::update() {
	switch (status) {
	case NeonStatus::NORMAL1:
		nm1();
		break;

	case NeonStatus::SP1:		// 「東風飛梅」
		sp1();
		break;

	case NeonStatus::NORMAL2:
		nm2();
		break;

	case NeonStatus::SP2:		// 「天神さまの祟り」
		sp2();
		break;

	case NeonStatus::NORMAL3:
		nm3();
		break;

	case NeonStatus::SP3:		// 「狂気を帯びるライデンスパーク」
		sp3();
		break;

	case NeonStatus::NORMAL4:
		nm4();
		break;

	case NeonStatus::SP4:		// 「シャッフルトレイン」
		sp4();
		break;
	}
	collidant->update(position);
	last_updated_clock = DxLib::GetNowHiPerformanceCount();
}

void Neon::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_NEON, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}

void Neon::nm1() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP1_ACTIVATE_HP_RATIO) {
	}
	else {
		status = NeonStatus::SP1;
	}
}

void Neon::nm2() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP2_ACTIVATE_HP_RATIO) {
		// 直進弾
		int nm2_straight_generated_delta_time = DxLib::GetNowCount() - nm2_straight_last_generated_clock;
		if (nm2_straight_generated_delta_time > NM2_STRAIGHT_INTERVAL) {
			for (int i = 0; i < NM2_STRAIGHT_NOZZLES; ++i) {
				double random_arg = 2.0 / 360.0 * pi * DxLib::GetRand(360);
				(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
					position->x,
					position->y,
					random_arg,
					NM2_STRAIGHT_SHOT_SPEED,
					NM2_STRAIGHT_COLLIDANT_SIZE,
					1,
					SkinID::NEON_NM2_STRAIGHT
				);
			}
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			nm2_straight_last_generated_clock = DxLib::GetNowCount();
		}
		// レーザー弾
		int nm2_laser_elaspsed_time = DxLib::GetNowCount() - nm2_laser_kept_clock;
		if (nm2_laser_status == NeonNormal2LaserStatus::AWAIT) {
			if (nm2_laser_elaspsed_time > NM2_LASER_AWAIT_INTERVAL) {
				nm2_laser_status = NeonNormal2LaserStatus::NOTIFY;
			}
		}
		else if (nm2_laser_status == NeonNormal2LaserStatus::NOTIFY) {				// 予告線の描画
			if (nm2_laser_notify_count == 0) {// ここを通る1回目だけ自キャラの座標を取得したい
				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double sp2_laser_delta_x_mychr = my_chr_pos.x - position->x;
				double sp2_laser_delta_y_mychr = my_chr_pos.y - position->y;
				nm2_laser_arg = atan2(sp2_laser_delta_y_mychr, sp2_laser_delta_x_mychr);	// ねおんから自機へ向いた角度
			}

			double nm2_laser_notify_end_x = position->x + cos(nm2_laser_arg) * NM2_LASER_LENGTH;	// InFieldPositionで終端座標の算出
			double nm2_laser_notify_end_y = position->y + sin(nm2_laser_arg) * NM2_LASER_LENGTH;
			InFieldPosition position_end(nm2_laser_notify_end_x, nm2_laser_notify_end_y);

			Position draw_position_begin = position->get_draw_position();				// InFieldPostionからPositionに変換
			Position draw_position_end = position_end.get_draw_position();
			
			unsigned int NM2_LASER_NOTIFY_COLOR = (GetColor(255, 0, 255));				// 予告線の色指定
			
			DxLib::DrawLine(	//　予告線を描画
				draw_position_begin.x,
				draw_position_begin.y,
				draw_position_end.x,
				draw_position_end.y,
				NM2_LASER_NOTIFY_COLOR
			);
			++nm2_laser_notify_count;
			if (nm2_laser_elaspsed_time > NM2_LASER_AWAIT_INTERVAL + NM2_LASER_NOTIFY_INTERVAL) {
				nm2_laser_status = NeonNormal2LaserStatus::EMIT;
				nm2_laser_notify_count = 0;
			}
		}
		else if (nm2_laser_status == NeonNormal2LaserStatus::EMIT) {		// レーザー弾の発射
			// GENERATE_IDを記録しておいて、遷移時にそのIDのレーザーを消す？
			(*Field::ENEMY_LASERS)[Offensive::GENERATE_ID()] = make_unique<PolarLaser>(
				position->x,
				position->y,
				nm2_laser_arg,
				NM2_LASER_LENGTH,
				NM2_LASER_WIDTH,
				10.0,
				true,
				SkinID::NEON_NM2_LASER
				);
			// レーザーが残る問題
			if (nm2_laser_elaspsed_time > NM2_LASER_AWAIT_INTERVAL + NM2_LASER_NOTIFY_INTERVAL + NM2_LASER_EMIT_INTERVAL) {
				nm2_laser_status = NeonNormal2LaserStatus::AWAIT;
				nm2_laser_kept_clock = DxLib::GetNowCount();
			}
		}
	}
	else {
		status = NeonStatus::SP2;
	}
}

void Neon::nm3() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP3_ACTIVATE_HP_RATIO) {
		int nm3_generated_delta_time = DxLib::GetNowCount() - nm3_last_generated_clock;
		if (nm3_generated_delta_time > NM3_INTERVAL){
			for (int i = 0; i < NM3_NOZZLES; ++i) {
				SkinID oval_handles = Neon::get_nm3_oval_image_handles(i+1);
				double arg = nm3_shot_arg + 2.0 / (1.0 * NM3_NOZZLES) * pi * i;
				(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
					position->x,
					position->y,
					arg,
					NM3_SHOT_SPEED,
					NM3_COLLIDANT_SIZE,
					1,
					oval_handles
				);
			}
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			nm3_shot_arg += NM3_NOZZLES_ROTATE_SPEED;
			nm3_last_generated_clock = DxLib::GetNowCount();
		}
	}
	else {
		status = NeonStatus::SP3;
	}
}

void Neon::nm4() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP4_ACTIVATE_HP_RATIO) {
	}
	else {
		status = NeonStatus::SP4;
	}
}

void Neon::sp1() {		// 「東風飛梅」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP1_TERMINATE_HP_RATIO) {
	}
	else {
		status = NeonStatus::NORMAL2;
	}
}

void Neon::sp2() {		// 「天神さまの祟り」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP2_TERMINATE_HP_RATIO) {
		int sp2_generated_delta_time = DxLib::GetNowCount() - sp2_hail_last_generated_clock;
		if (sp2_generated_delta_time > SP2_HAIL_INTERVAL) {
			// 雹弾（諸事情により）
			for (int i = 0; i < SP2_HAIL_NOZZLES; ++i) {
				double arg = SP2_HAIL_INIT_ARG * i;
				(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<CurvingShot>(
					position->x,
					position->y,
					arg,
					SP2_HAIL_INIT_SPEED,
					SP2_HAIL_INIT_CURVE_SPEED,
					SP2_HAIL_COLLIDANT_SIZE,
					1,
					SkinID::NEON_SP2_HAIL
				);
			}
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			sp2_hail_last_generated_clock = DxLib::GetNowCount();
			// ここにレーザー弾を入力
		}
		
	}
	else {
		status = NeonStatus::NORMAL3;
	}
}

void Neon::sp3() {		// 「狂気を帯びるライデンスパーク」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP3_TERMINATE_HP_RATIO) {
	}
	else {
		status = NeonStatus::NORMAL4;
	}
}

void Neon::sp4() {		// 「シャッフルトレイン」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > 0) {
		// シャッフル弾
		int sp4_shuffle_fire_generated_delta_time = DxLib::GetNowCount() - sp4_shuffle_fire_last_generated_clock;
		if (sp4_shuffle_fire_generated_delta_time > SP4_SHUFFLE_FIRE_INTERVAL) {
			int sp4_shuffle_tick_generated_delta_time = DxLib::GetNowCount() - sp4_shuffle_tick_last_generated_clock;
			if (sp4_shuffle_tick_generated_delta_time > SP4_SHUFFLE_TICK_INTERVAL) {
				for (int j = 0; j < SP4_SHUFFLE_CARD_NUM; ++j) {
					int shuffle_x = Field::PIXEL_SIZE_X + 100;
					int shuffle_y = Field::PIXEL_SIZE_Y - 250 + (SP4_SHUFFLE_CARD_DISTANCE * (j + 1));
					unsigned int shuffle_offensive_id = Offensive::GENERATE_ID();
					(*Field::ENEMY_BULLETS)[shuffle_offensive_id] = make_unique<StraightShot>(
						shuffle_x,
						shuffle_y,
						sp4_shuffle_arg,
						sp4_shuffle_speed,
						SP4_SHUFFLE_COLLIDANT_SIZE,
						1,
						SkinID::NEON_SP4_SHUFFLE
						);
					sp4_shuffle_ids.push_back(shuffle_offensive_id);
				}
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
				sp4_shuffle_tick_last_generated_clock = DxLib::GetNowCount();
				++sp4_shuffle_tick_count;
			}
			if (sp4_shuffle_tick_count == SP4_SHUFFLE_TICK_COUNT_MAX) {
				sp4_shuffle_fire_last_generated_clock = DxLib::GetNowCount();
				sp4_shuffle_tick_count = 0;
				sp4_shuffles_ids.push_back(sp4_shuffle_ids);
				sp4_shuffle_ids.clear();
			}
		}

		for (auto& shuffle_ids : sp4_shuffles_ids) {
			auto id = shuffle_ids.at(0);
			// DOWN処理
			if (Field::ENEMY_BULLETS->count(id) == 1
				&& (*Field::ENEMY_BULLETS)[id]->position->x < SP4_SHUFFLE_DOWN_CRITERION_X
				&& (*Field::ENEMY_BULLETS)[id]->arg >= 2.0 / 3.0 * pi
				&& (*Field::ENEMY_BULLETS)[id]->arg <= 4.0 / 3.0 * pi)
			{
				for (auto& shuffle_id : shuffle_ids) {
					if (Field::ENEMY_BULLETS->count(shuffle_id) == 1) {
						// フィールドに弾が存在しているので偏角と速度を変える
						(*Field::ENEMY_BULLETS)[shuffle_id]->set_arg(SP4_SHUFFLE_DOWN_ARG);
						(*Field::ENEMY_BULLETS)[shuffle_id]->set_speed(SP4_SHUFFLE_DOWN_SPEED);
					}
				}
			}
			// EXIT処理
			if (Field::ENEMY_BULLETS->count(id) == 1
				&& (*Field::ENEMY_BULLETS)[id]->position->y < SP4_SHUFFLE_EXIT_CRITERION_Y
				&& (*Field::ENEMY_BULLETS)[id]->arg >= 4.0 / 3.0 * pi
				&& (*Field::ENEMY_BULLETS)[id]->arg <= 5.0 / 3.0 * pi)
			{
				for (auto& shuffle_id : shuffle_ids) {
					if (Field::ENEMY_BULLETS->count(shuffle_id) == 1) {
						// フィールドに弾が存在しているので偏角と速度を変える
						(*Field::ENEMY_BULLETS)[shuffle_id]->set_arg(SP4_SHUFFLE_EXIT_ARG);
						(*Field::ENEMY_BULLETS)[shuffle_id]->set_speed(SP4_SHUFFLE_EXIT_SPEED);
					}
				}
			}
		}

		// トレイン(追尾)弾
		int sp4_train_fire_generated_delta_time = DxLib::GetNowCount() - sp4_train_fire_last_generated_clock;
		if (sp4_train_fire_generated_delta_time > SP4_TRAIN_FIRE_INTERVAL) {
			int sp4_train_tick_generated_delta_time = DxLib::GetNowCount() - sp4_train_tick_last_generated_clock;
			if (sp4_train_tick_generated_delta_time > SP4_TRAIN_TICK_INTERVAL) {
				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double sp4_train_delta_x_mychr = my_chr_pos.x - position->x;
				double sp4_train_delta_y_mychr = my_chr_pos.y - position->y;
				double sp4_train_arg_toward_mychr = atan2(sp4_train_delta_y_mychr, sp4_train_delta_x_mychr);
				unsigned int train_offensive_id = Offensive::GENERATE_ID();
				(*Field::ENEMY_BULLETS)[train_offensive_id] = make_unique<StraightShot>(
					position->x,
					position->y,
					sp4_train_arg_toward_mychr,
					SP4_TRAIN_INIT_SPEED,
					SP4_TRAIN_COLLIDANT_SIZE,
					1,
					SkinID::NEON_SP4_TRAIN
					);
				sp4_train_ids.push_back(train_offensive_id);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
				sp4_train_tick_last_generated_clock = DxLib::GetNowCount();
				++sp4_train_tick_count;
			}
			if (sp4_train_tick_count == SP4_TRAIN_TICK_COUNT_MAX) {
				sp4_train_fire_last_generated_clock = DxLib::GetNowCount();
				sp4_train_tick_count = 0;
				sp4_trains_ids.push_back(sp4_train_ids);
				sp4_train_ids.clear();
			}
		}

		for (auto& train_ids : sp4_trains_ids) {
			auto id = train_ids.at(0);
			if (Field::ENEMY_BULLETS->count(id) == 1){						// 現在フィールド上に弾があるかどうか
				if ((*Field::ENEMY_BULLETS)[id]->position->x < InFieldPosition::MIN_MOVABLE_BOUNDARY_X - 50		// 画面外に弾が出た場合
					|| (*Field::ENEMY_BULLETS)[id]->position->x > InFieldPosition::MAX_MOVABLE_BOUNDARY_X + 50
					|| (*Field::ENEMY_BULLETS)[id]->position->y < InFieldPosition::MIN_MOVABLE_BOUNDARY_Y - 50
					|| (*Field::ENEMY_BULLETS)[id]->position->y > InFieldPosition::MAX_MOVABLE_BOUNDARY_Y + 50)
				{
					for (auto& train_id : train_ids) {
						if (Field::ENEMY_BULLETS->count(train_id) == 1) {
							InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
							double sp4_train_delta_x_mychr = my_chr_pos.x - (*Field::ENEMY_BULLETS)[id]->position->x;
							double sp4_train_delta_y_mychr = my_chr_pos.y - (*Field::ENEMY_BULLETS)[id]->position->y;
							double sp4_train_arg_toward_mychr = atan2(sp4_train_delta_y_mychr, sp4_train_delta_x_mychr);
							(*Field::ENEMY_BULLETS)[train_id]->set_arg(sp4_train_arg_toward_mychr);
						}
					}
				}
			}
		}

	}
	else {

	}
}

enum SkinID Neon::get_nm3_oval_image_handles(int count) {
	SkinID OvalHandles = SkinID::NEON_NM3_RED;
	
	switch (count) {
	case 1:
		OvalHandles = SkinID::NEON_NM3_RED;
		++count;
		break;
	case 2:
		OvalHandles = SkinID::NEON_NM3_ORANGE;
		++count;
		break;
	case 3:
		OvalHandles = SkinID::NEON_NM3_YELLOW;
		++count;
		break;
	case 4:
		OvalHandles = SkinID::NEON_NM3_GREEN;
		++count;
		break;
	case 5:
		OvalHandles = SkinID::NEON_NM3_TEAL;
		++count;
		break;
	case 6:
		OvalHandles = SkinID::NEON_NM3_AQUA;
		++count;
		break;
	case 7:
		OvalHandles = SkinID::NEON_NM3_BLUE;
		++count;
		break;
	case 8:
		OvalHandles = SkinID::NEON_NM3_PURPLE;
		++count;
		break;
	case 9:
		OvalHandles = SkinID::NEON_NM3_FUCHSIA;
		++count;
		break;
	}
	return OvalHandles;
}