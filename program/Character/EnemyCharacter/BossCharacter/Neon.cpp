#include <memory>
#include <string>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "GameConductor.h"
#include "Field.h"
#include "Character/Character.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2BsNm4.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/Neon.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Offensive/Bullet/CurvingShot.h"
#include "Offensive/Bullet/HomingShot/HomingShot.h"
#include "Offensive/Bullet/StraightShot/RefractShot.h"
#include "Offensive/Laser/PolarLaser.h"
#include "Offensive/Laser/CartesianLaser/CartesianLaser.h"
#include "Offensive/Laser/CartesianLaser/LeidenLaser.h"
#include "Character/EnemyCharacter/ZakoCharacter/LeidenJar.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"
#include "FontHandles.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::wstring;
using std::numbers::pi;

const wstring Neon::NAME(L"雷ねおん");
const wstring Neon::SP1_NAME(L"「東風飛梅」");
const wstring Neon::SP2_NAME(L"「天神さまの祟り」");
const wstring Neon::SP3_NAME(L"「狂気を帯びるライデンスパーク」");
const wstring Neon::SP4_NAME(L"「シャッフルトレイン」");
NeonStatus Neon::STATUS;

const int Neon::INITIAL_POS_X = 310;
const int Neon::INITIAL_POS_Y = 620;
const unsigned int Neon::INITIAL_COLLIDANT_SIZE = 60;
const double Neon::DRAW_EXTRATE = 0.07;

const unsigned int Neon::NM2_STRAIGHT_NOZZLES = 12;
const unsigned int Neon::NM2_STRAIGHT_INTERVAL = 300;
const double Neon::NM2_STRAIGHT_SHOT_SPEED = 80;
const unsigned int Neon::NM2_STRAIGHT_COLLIDANT_SIZE = 7;

const double Neon::NM2_LASER_INIT_ARG = 3.0 / 4.0 * pi;
const unsigned int Neon::NM2_LASER_LENGTH = 800;
const unsigned int Neon::NM2_LASER_WIDTH = 30;
const double Neon::NM2_LASER_DPS = 5.0;
const unsigned int Neon::NM2_LASER_AWAIT_INTERVAL = 3000;
const unsigned int Neon::NM2_LASER_NOTIFY_INTERVAL = 2000;
const unsigned int Neon::NM2_LASER_EMIT_INTERVAL = 3000;

const unsigned int Neon::NM3_NOZZLES = 9;
const double Neon::NM3_NOZZLES_ROTATE_SPEED = 1.0 / 10.0 * pi;
const double Neon::NM3_SHOT_SPEED = 300;
const unsigned int Neon::NM3_COLLIDANT_SIZE = 10;
const unsigned int Neon::NM3_INTERVAL = 120;

const double Neon::NM4_CRYSTAL_SPEED = 200;
const unsigned int Neon::NM4_CRYSTAL_COLLIDANT_SIZE = 10;
const unsigned int Neon::NM4_CRYSTAL_NOZZLES = 16;
const unsigned int Neon::NM4_TICK_INTERVAL = 200;
const unsigned int Neon::NM4_FIRE_INTERVAL = 600;

const unsigned int Neon::SP2_GHOST_NOZZLES = 27;
const unsigned int Neon::SP2_GHOST_INTERVAL = 1000;
const double Neon::SP2_GHOST_INIT_ARG = 1.0 / 27.0 * 2.0 * pi;
const double Neon::SP2_GHOST_INIT_SPEED = 100;
const double Neon::SP2_GHOST_INIT_CURVE_SPEED = 1.0 / 16.0 * pi;
const unsigned int Neon::SP2_GHOST_COLLIDANT_SIZE = 8;

const double Neon::SP2_LASER_INIT_ARG = 3.0 / 4.0 * pi;
const unsigned int Neon::SP2_LASER_LENGTH = 800;
const unsigned int Neon::SP2_LASER_WIDTH = 150;
const double Neon::SP2_LASER_DPS = 10.0;
const unsigned int Neon::SP2_LASER_AWAIT_INTERVAL = 2000;
const unsigned int Neon::SP2_LASER_NOTIFY_INTERVAL = 2000;
const unsigned int Neon::SP2_LASER_EMIT_INTERVAL = 2000;

const unsigned int Neon::SP3_LEIDENJAR_EXPLODE_WAIT_TIME = 2000;
const unsigned int Neon::SP3_LEIDENJAR_EXPLODE_NOZZLES = 24;
const unsigned int Neon::SP3_LEIDENJAR_EXPLODE_SHOT_SPEED = 200;
const unsigned int Neon::SP3_LEIDENJAR_EXPLODE_SHOT_COLLIDANT_SIZE = 17;

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
const double Neon::SP4_TRAIN_INIT_SPEED = 200;
const unsigned int Neon::SP4_TRAIN_COLLIDANT_SIZE = 10;
const unsigned int Neon::SP4_TRAIN_TICK_INTERVAL = 100;
const unsigned int Neon::SP4_TRAIN_FIRE_INTERVAL = 7000;
const unsigned int Neon::SP4_TRAIN_TICK_COUNT_MAX = 5;

const unsigned int Neon::INITIAL_HP = 2000;

// 100% -  90% NORMAL1
//  90% -  75% SP1
//  75% -  65% NORMAL2
//  65% -  50% SP2
//  50% -  40% NORMAL3
//  40% -  25% SP3
//  25% -  15% NORMAL4
//  15% -   0% SP4

//const double Neon::NM1_ACTIVATE_HP_RATIO = 100.0 / 100.0;
//const double Neon::SP1_ACTIVATE_HP_RATIO = 90.0 / 100.0;
//const double Neon::NM2_ACTIVATE_HP_RATIO = 75.0 / 100.0;
//const double Neon::SP2_ACTIVATE_HP_RATIO = 65.0 / 100.0;
//const double Neon::NM3_ACTIVATE_HP_RATIO = 50.0 / 100.0;
//const double Neon::SP3_ACTIVATE_HP_RATIO = 40.0 / 100.0;
//const double Neon::NM4_ACTIVATE_HP_RATIO = 25.0 / 100.0;
//const double Neon::SP4_ACTIVATE_HP_RATIO = 15.0 / 100.0;

const double Neon::NM1_ACTIVATE_HP_RATIO = 100.0 / 100.0;
const double Neon::SP1_ACTIVATE_HP_RATIO = 90.0 / 100.0;

const double Neon::NM2_ACTIVATE_HP_RATIO = 100.0 / 100.0;
const double Neon::SP2_ACTIVATE_HP_RATIO = 87.0 / 100.0;
const double Neon::NM3_ACTIVATE_HP_RATIO = 67.0 / 100.0;
const double Neon::SP3_ACTIVATE_HP_RATIO = 54.0 / 100.0;
const double Neon::NM4_ACTIVATE_HP_RATIO = 34.0 / 100.0;
const double Neon::SP4_ACTIVATE_HP_RATIO = 20.0 / 100.0;

const unsigned int Neon::CRUSH_BONUS = 750000;
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
	BossCharacter(NAME, INITIAL_HP, CRUSH_BONUS),
	kept_clock(DxLib::GetNowCount()),
	nm2_straight_last_generated_clock(DxLib::GetNowCount()),
	nm2_laser_arg(NM2_LASER_INIT_ARG),
	nm2_laser_id(0),
	nm2_laser_notify_count(0),
	nm2_laser_emit_count(0),
	nm2_laser_kept_clock(DxLib::GetNowCount()),
	nm2_laser_status(NeonNormal2LaserStatus::AWAIT),
	nm3_shot_arg(0.0),
	nm3_last_generated_clock(DxLib::GetNowCount()),
	nm4_zk_generate_count(1),
	nm4_crystal_skin_id(SkinID::NEON_NM4_CRYSTAL_RED),
	nm4_tick_count(0),
	nm4_last_tick_clock(DxLib::GetNowCount()),
	nm4_last_fire_clock(DxLib::GetNowCount()),
	sp2_ghost_curve_speed(0.0),
	sp2_ghost_last_generated_clock(DxLib::GetNowCount()),
	sp2_laser_arg(SP2_LASER_INIT_ARG),
	sp2_laser_id(0),
	sp2_laser_notify_count(0),
	sp2_laser_emit_count(0),
	sp2_laser_kept_clock(DxLib::GetNowCount()),
	sp2_laser_status(NeonSp2LaserStatus::AWAIT),
	sp3_leidenjar_emitted_flag(false),
	sp3_leidenlaser_generated_flag(false),
	sp3_leidenlaser_a_id(0),
	sp3_leidenlaser_b_id(0),
	sp3_leidenlaser_c_id(0),
	sp3_leidenlaser_a_erased_flag(false),
	sp3_leidenlaser_b_erased_flag(false),
	sp3_leidenlaser_c_erased_flag(false),
	sp3_leidenjar_a_explode_reserved_flag(false),
	sp3_leidenjar_b_explode_reserved_flag(false),
	sp3_leidenjar_c_explode_reserved_flag(false),
	sp3_leidenjar_a_explode_reserved_clock(0),
	sp3_leidenjar_b_explode_reserved_clock(0),
	sp3_leidenjar_c_explode_reserved_clock(0),
	sp3_leidenjar_a_explode_initialized_flag(false),
	sp3_leidenjar_b_explode_initialized_flag(false),
	sp3_leidenjar_c_explode_initialized_flag(false),
	sp3_leidenjar_a_explode_initialized_clock(0),
	sp3_leidenjar_b_explode_initialized_clock(0),
	sp3_leidenjar_c_explode_initialized_clock(0),
	sp3_leidenjar_a_explode_finalized_flag(false),
	sp3_leidenjar_b_explode_finalized_flag(false),
	sp3_leidenjar_c_explode_finalized_flag(false),
	sp4_shuffle_arg(SP4_SHUFFLE_INIT_ARG),
	sp4_shuffle_speed(SP4_SHUFFLE_INIT_SPEED),
	sp4_shuffle_ids(0),
	sp4_shuffles_ids(0),
	sp4_shuffle_tick_count(0),
	sp4_shuffle_fire_count(0),
	sp4_shuffle_tick_last_generated_clock(DxLib::GetNowCount()),
	sp4_shuffle_fire_last_generated_clock(DxLib::GetNowCount()),
	sp4_shuffle_down_last_changed_clock(DxLib::GetNowCount()),
	sp4_train_tick_count(0),
	sp4_train_tick_last_generated_clock(DxLib::GetNowCount()),
	sp4_train_fire_last_generated_clock(0)
{
	STATUS = NeonStatus::SP3;

	switch (STATUS)
	{
	case NeonStatus::NORMAL1:
		hp = INITIAL_HP * NM1_ACTIVATE_HP_RATIO;
		break;
	case NeonStatus::SP1:
		hp = INITIAL_HP * SP1_ACTIVATE_HP_RATIO;
		break;
	case NeonStatus::NORMAL2:
		hp = INITIAL_HP * NM2_ACTIVATE_HP_RATIO;
		break;
	case NeonStatus::SP2:
		hp = INITIAL_HP * SP2_ACTIVATE_HP_RATIO;
		break;
	case NeonStatus::NORMAL3:
		hp = INITIAL_HP * NM3_ACTIVATE_HP_RATIO;
		break;
	case NeonStatus::SP3:
		hp = INITIAL_HP * SP3_ACTIVATE_HP_RATIO;
		break;
	case NeonStatus::NORMAL4:
		hp = INITIAL_HP * NM4_ACTIVATE_HP_RATIO;
		break;
	case NeonStatus::SP4:
		hp = INITIAL_HP * SP4_ACTIVATE_HP_RATIO;
		break;
	default:
		break;
	}
}

void Neon::update() {
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	switch (STATUS) {
	case NeonStatus::NORMAL1:
		nm1();
		break;

	case NeonStatus::SP1:		// 「東風飛梅」
		if (elapsed_time > 3000) {
			sp1();
		}
		break;

	case NeonStatus::NORMAL2:
		if (elapsed_time > 3000) {
			nm2();
		}
		break;

	case NeonStatus::SP2:		// 「天神さまの祟り」
		if (elapsed_time > 5000) {
			sp2();
		}
		break;

	case NeonStatus::NORMAL3:
		if (elapsed_time > 6000) {
			nm3();
		}
		break;

	case NeonStatus::SP3:		// 「狂気を帯びるライデンスパーク」
		if (elapsed_time > 3000) {
			sp3();
		}
		break;

	case NeonStatus::NORMAL4:
		if (elapsed_time > 3000) {
			nm4();
		}
		break;

	case NeonStatus::SP4:		// 「シャッフルトレイン」
		if (elapsed_time > 3000) {
			sp4();
		}
		break;
	}
	collidant->update(position);
	last_updated_clock = DxLib::GetNowHiPerformanceCount();
}

void Neon::draw() {
	draw_hp_donut();
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_NEON, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}

void Neon::nm1() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP1_ACTIVATE_HP_RATIO) {
	}
	else {
		STATUS = NeonStatus::SP1;
		kept_clock = GetNowCount();
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP1_NAME));
	}
}

void Neon::nm2() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP2_ACTIVATE_HP_RATIO) {
		int nm2_straight_generated_delta_time = DxLib::GetNowCount() - nm2_straight_last_generated_clock;	// 直進弾
		if (nm2_straight_generated_delta_time > NM2_STRAIGHT_INTERVAL) {
			for (int i = 0; i < NM2_STRAIGHT_NOZZLES; ++i) {
				double random_arg = 2.0 / 360.0 * pi * DxLib::GetRand(360);
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
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
		int nm2_laser_elaspsed_time = DxLib::GetNowCount() - nm2_laser_kept_clock;		// レーザー弾
		if (nm2_laser_status == NeonNormal2LaserStatus::AWAIT) {
			if (nm2_laser_elaspsed_time > NM2_LASER_AWAIT_INTERVAL) {
				nm2_laser_status = NeonNormal2LaserStatus::NOTIFY;
				nm2_laser_kept_clock = DxLib::GetNowCount();
			}
		}
		else if (nm2_laser_status == NeonNormal2LaserStatus::NOTIFY) {						// 予告線
			if (nm2_laser_notify_count == 0) {														// ここを通る1回目だけ自キャラの座標を取得
				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double nm2_laser_delta_x_mychr = my_chr_pos.x - position->x;
				double nm2_laser_delta_y_mychr = my_chr_pos.y - position->y;
				nm2_laser_arg = atan2(nm2_laser_delta_y_mychr, nm2_laser_delta_x_mychr);			// ねおんから自機へ向いた角度
				++nm2_laser_notify_count;
			}
			double nm2_laser_notify_end_x = position->x + cos(nm2_laser_arg) * NM2_LASER_LENGTH;	// InFieldPositionで終端座標の算出
			double nm2_laser_notify_end_y = position->y + sin(nm2_laser_arg) * NM2_LASER_LENGTH;
			InFieldPosition position_end(nm2_laser_notify_end_x, nm2_laser_notify_end_y);

			Position draw_position_begin = position->get_draw_position();							// InFieldPostionからPositionに変換
			Position draw_position_end = position_end.get_draw_position();
			
			unsigned int NM2_LASER_NOTIFY_COLOR = (GetColor(255, 0, 255));							// 予告線の色指定
			
			DxLib::DrawLine(																		//　予告線を描画
				draw_position_begin.x,
				draw_position_begin.y,
				draw_position_end.x,
				draw_position_end.y,
				NM2_LASER_NOTIFY_COLOR
			);
	
			if (nm2_laser_elaspsed_time > NM2_LASER_NOTIFY_INTERVAL) {
				nm2_laser_notify_count = 0;
				nm2_laser_status = NeonNormal2LaserStatus::EMIT;
				nm2_laser_kept_clock = DxLib::GetNowCount();
			}
		}
		else if (nm2_laser_status == NeonNormal2LaserStatus::EMIT) {		// レーザー弾
			if (nm2_laser_emit_count == 0) {
				nm2_laser_id = Laser::GENERATE_ID();
				(*Field::ENEMY_LASERS)[nm2_laser_id] = make_unique<PolarLaser>(
					position->x,
					position->y,
					nm2_laser_arg,
					NM2_LASER_LENGTH,
					NM2_LASER_WIDTH,
					NM2_LASER_DPS,
					true,
					SkinID::NEON_NM2_LASER
					);
				++nm2_laser_emit_count;
			}
			if (nm2_laser_elaspsed_time > NM2_LASER_EMIT_INTERVAL) {
				(*Field::ENEMY_LASERS).erase(nm2_laser_id);
				nm2_laser_emit_count = 0;
				nm2_laser_status = NeonNormal2LaserStatus::AWAIT;
				nm2_laser_kept_clock = DxLib::GetNowCount();
			}
		}
	}
	else {
		(*Field::ENEMY_LASERS).erase(nm2_laser_id);
		STATUS = NeonStatus::SP2;
		kept_clock = GetNowCount();
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP2_NAME));
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
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
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
		STATUS = NeonStatus::SP3;
		kept_clock = GetNowCount();
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP3_NAME));
	}
}

void Neon::nm4() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP4_ACTIVATE_HP_RATIO) {
		if (nm4_zk_generate_count == 1) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2BsNm4>(
				CharacterID::ZKCHRSTG2BSNM4_1,
				position->x,
				position->y
				));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2BsNm4>(
				CharacterID::ZKCHRSTG2BSNM4_2,
				position->x,
				position->y
				));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2BsNm4>(
				CharacterID::ZKCHRSTG2BSNM4_3,
				position->x,
				position->y
				));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2BsNm4>(
				CharacterID::ZKCHRSTG2BSNM4_4,
				position->x,
				position->y
				));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2BsNm4>(
				CharacterID::ZKCHRSTG2BSNM4_5,
				position->x,
				position->y
				));
			++nm4_zk_generate_count;
		}
		int nm4_fire_delta_time = DxLib::GetNowCount() - nm4_last_fire_clock;	// 全周攻撃2連弾
		if (nm4_fire_delta_time > NM4_FIRE_INTERVAL) {
			if (nm4_tick_count == 0) {
				nm4_crystal_skin_id = SkinID::NEON_NM4_CRYSTAL_RED;
			}
			else {
				nm4_crystal_skin_id = SkinID::NEON_NM4_CRYSTAL_BLUE;
			}
			int nm4_tick_delta_time = DxLib::GetNowCount() - nm4_last_tick_clock;
			if (nm4_tick_delta_time > NM4_TICK_INTERVAL && nm4_tick_count < 2) {
				for (int i = 0; i < NM4_CRYSTAL_NOZZLES; ++i) {
					double theta = 2.0 * pi / NM4_CRYSTAL_NOZZLES * i;

					(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<RefractShot>(
						position->x,
						position->y,
						theta,
						NM4_CRYSTAL_SPEED,
						NM4_CRYSTAL_COLLIDANT_SIZE,
						1,
						nm4_crystal_skin_id
						);
				}
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
				nm4_last_tick_clock = DxLib::GetNowCount();
				++nm4_tick_count;
			}
			if (nm4_tick_count == 2) {
				nm4_tick_count = 0;
				nm4_last_fire_clock = DxLib::GetNowCount();
			}
		}
	}
	else {
		ZkChrStg2BsNm4::ESCAPE_FLAG = true;
		STATUS = NeonStatus::SP4;
		kept_clock = GetNowCount();
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP4_NAME));
	}
}

void Neon::sp1() {		// 「東風飛梅」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * NM2_ACTIVATE_HP_RATIO) {
	}
	else {
		GameConductor::TECHNICAL_SCORE += SP1_ACCOMPLISH_BONUS;
		STATUS = NeonStatus::NORMAL2;
	}
}

void Neon::sp2() {		// 「天神さまの祟り」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * NM3_ACTIVATE_HP_RATIO) {
		int sp2_laser_elaspsed_time = DxLib::GetNowCount() - sp2_laser_kept_clock;		// レーザー弾
		if (sp2_laser_status == NeonSp2LaserStatus::AWAIT) {
			if (sp2_laser_elaspsed_time > SP2_LASER_AWAIT_INTERVAL) {
				sp2_laser_status = NeonSp2LaserStatus::NOTIFY;
				sp2_laser_kept_clock = DxLib::GetNowCount();
			}
		}
		else if (sp2_laser_status == NeonSp2LaserStatus::NOTIFY) {
			if (sp2_laser_notify_count == 0) {
				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double sp2_laser_delta_x_mychr = my_chr_pos.x - position->x;
				double sp2_laser_delta_y_mychr = my_chr_pos.y - position->y;
				sp2_laser_arg = atan2(sp2_laser_delta_y_mychr, sp2_laser_delta_x_mychr);
				++sp2_laser_notify_count;
			}
			double sp2_laser_notify_end_x = position->x + cos(sp2_laser_arg) * SP2_LASER_LENGTH;
			double sp2_laser_notify_end_y = position->y + sin(sp2_laser_arg) * SP2_LASER_LENGTH;
			InFieldPosition position_end(sp2_laser_notify_end_x, sp2_laser_notify_end_y);

			Position draw_position_begin = position->get_draw_position();
			Position draw_position_end = position_end.get_draw_position();

			unsigned int SP2_LASER_NOTIFY_COLOR = (GetColor(255, 255, 0));

			DxLib::DrawLine(
				draw_position_begin.x,
				draw_position_begin.y,
				draw_position_end.x,
				draw_position_end.y,
				SP2_LASER_NOTIFY_COLOR
			);

			if (sp2_laser_elaspsed_time > SP2_LASER_NOTIFY_INTERVAL) {
				sp2_laser_notify_count = 0;
				sp2_laser_status = NeonSp2LaserStatus::EMIT;
				sp2_laser_kept_clock = DxLib::GetNowCount();
			}
		}
		else if (sp2_laser_status == NeonSp2LaserStatus::EMIT) {
			if (sp2_laser_emit_count == 0) {
				sp2_laser_id = Laser::GENERATE_ID();
				(*Field::ENEMY_LASERS)[sp2_laser_id] = make_unique<PolarLaser>(
					position->x,
					position->y,
					sp2_laser_arg,
					SP2_LASER_LENGTH,
					SP2_LASER_WIDTH,
					SP2_LASER_DPS,
					true,
					SkinID::NEON_SP2_LASER
					);
				++sp2_laser_emit_count;
			}
			if (sp2_laser_elaspsed_time > SP2_LASER_EMIT_INTERVAL) {
				(*Field::ENEMY_LASERS).erase(sp2_laser_id);
				sp2_laser_emit_count = 0;
				sp2_laser_status = NeonSp2LaserStatus::AWAIT;
				sp2_laser_kept_clock = DxLib::GetNowCount();
			}
		}
		int sp2_generated_delta_time = DxLib::GetNowCount() - sp2_ghost_last_generated_clock;
		if (sp2_generated_delta_time > SP2_GHOST_INTERVAL) {		// 幽霊弾
			for (int i = 0; i < SP2_GHOST_NOZZLES; ++i) {
				double arg = SP2_GHOST_INIT_ARG * i;
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<CurvingShot>(
					position->x,
					position->y,
					arg,
					SP2_GHOST_INIT_SPEED,
					SP2_GHOST_INIT_CURVE_SPEED,
					SP2_GHOST_COLLIDANT_SIZE,
					1,
					SkinID::NEON_SP2_GHOST
				);
			}
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			sp2_ghost_last_generated_clock = DxLib::GetNowCount();
		}
	}
	else {
		(*Field::ENEMY_LASERS).erase(sp2_laser_id);
		GameConductor::TECHNICAL_SCORE += SP2_ACCOMPLISH_BONUS;
		STATUS = NeonStatus::NORMAL3;
		kept_clock = GetNowCount();
	}
}

void Neon::sp3() {		// 「狂気を帯びるライデンスパーク」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * NM4_ACTIVATE_HP_RATIO) {


		if ( sp3_leidenjar_emitted_flag == false ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<LeidenJar>(
				position->x,
				position->y,
				CharacterID::LEIDENJAR_A
			));
			Field::ZAKO_CHARACTERS->push_back(make_unique<LeidenJar>(
				position->x,
				position->y,
				CharacterID::LEIDENJAR_B
			));
			Field::ZAKO_CHARACTERS->push_back(make_unique<LeidenJar>(
				position->x,
				position->y,
				CharacterID::LEIDENJAR_C
			));
			sp3_leidenjar_emitted_flag = true;
		}


		if (sp3_leidenlaser_generated_flag == false) {

			LaserID temp_id;

			temp_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[temp_id] = make_unique<LeidenLaser>(
				position->x,
				position->y,
				Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_A)->position->x,
				Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_A)->position->y
			);
			sp3_leidenlaser_a_id = temp_id;

			temp_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[temp_id] = make_unique<LeidenLaser>(
				position->x,
				position->y,
				Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_B)->position->x,
				Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_B)->position->y
			);
			sp3_leidenlaser_b_id = temp_id;

			temp_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[temp_id] = make_unique<LeidenLaser>(
				position->x,
				position->y,
				Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_C)->position->x,
				Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_C)->position->y
			);
			sp3_leidenlaser_c_id = temp_id;


			sp3_leidenlaser_generated_flag = true;

		}

		if ( sp3_leidenlaser_a_erased_flag == false ) {
			if (Field::IS_THERE(CharacterID::LEIDENJAR_A) == false) {
				Field::ENEMY_LASERS->erase(sp3_leidenlaser_a_id);
				sp3_leidenlaser_a_erased_flag = true;
			}
		}

		if ( sp3_leidenlaser_b_erased_flag == false ) {
			if (Field::IS_THERE(CharacterID::LEIDENJAR_B) == false) {
				Field::ENEMY_LASERS->erase(sp3_leidenlaser_b_id);
				sp3_leidenlaser_b_erased_flag = true;
			}
		}

		if ( sp3_leidenlaser_c_erased_flag == false ) {
			if (Field::IS_THERE(CharacterID::LEIDENJAR_C) == false) {
				Field::ENEMY_LASERS->erase(sp3_leidenlaser_c_id);
				sp3_leidenlaser_c_erased_flag = true;
			}
		}


		if (sp3_leidenlaser_a_erased_flag == false) {

			LeidenLaser* leidenlaser = dynamic_cast<LeidenLaser*> ((*Field::ENEMY_LASERS)[sp3_leidenlaser_a_id].get());
			leidenlaser->set_begin_pos(*position);
			leidenlaser->set_end_pos(*Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_A)->position);

			LeidenJar* leidenjar = dynamic_cast<LeidenJar*>(Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_A).get());
			switch (leidenlaser->collide_count) {
			case 0:
				leidenjar->status = LeidenJarStatus::INITIAL;
				break;
			case 1:
				leidenjar->status = LeidenJarStatus::FIRST;
				break;
			case 2:
				leidenjar->status = LeidenJarStatus::SECOND;
				break;
			case 3:
				leidenjar->status = LeidenJarStatus::FINAL;
				break;
			}

			if (sp3_leidenjar_a_explode_reserved_flag == false) {
				if (leidenjar->status == LeidenJarStatus::FINAL) {
					sp3_leidenjar_a_explode_reserved_clock = DxLib::GetNowCount();
					sp3_leidenjar_a_explode_reserved_flag = true;
				}
			}

			if (sp3_leidenjar_a_explode_reserved_flag == true) {
				if (sp3_leidenjar_a_explode_initialized_flag == false) {
					int delta_time_explode_reserve = DxLib::GetNowCount() - sp3_leidenjar_a_explode_reserved_clock;
					if (delta_time_explode_reserve > SP3_LEIDENJAR_EXPLODE_WAIT_TIME) {


						for (int i = 0; i < SP3_LEIDENJAR_EXPLODE_NOZZLES; i++) {
							double this_arg = 2 * pi / SP3_LEIDENJAR_EXPLODE_NOZZLES * i;

							(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
								leidenjar->position->x,
								leidenjar->position->y,
								this_arg,
								SP3_LEIDENJAR_EXPLODE_SHOT_SPEED,
								SP3_LEIDENJAR_EXPLODE_SHOT_COLLIDANT_SIZE,
								1,
								SkinID::NEON_SP3_EXPLOSION
							);


						}

						//sp3_leidenjar_a_explosion = make_unique<RotatingStraightShotEmission>(
						//	leidenjar->position->x,
						//	leidenjar->position->y,
						//	0,
						//	pi,
						//	true,
						//	114514,
						//	24,
						//	200,
						//	150,
						//	15,
						//	1,
						//	TeamID::ENEMY,
						//	SkinID::NEON_SP3_EXPLOSION
						//);

						Field::ERASE_ZAKO_CHARACTER(CharacterID::LEIDENJAR_A);
						Field::ENEMY_LASERS->erase(sp3_leidenlaser_a_id);

						sp3_leidenjar_a_explode_initialized_flag = true;
						sp3_leidenjar_a_explode_initialized_clock = DxLib::GetNowCount();
					}
				}
			}

			if (sp3_leidenjar_a_explode_initialized_flag == true) {
				if (sp3_leidenjar_a_explode_finalized_flag == false) {
					int delta_time_explode_initialized = DxLib::GetNowCount() - sp3_leidenjar_a_explode_initialized_clock;
					if (delta_time_explode_initialized < 4000) {
						//sp3_leidenjar_a_explosion->update();
					}
					else {
						sp3_leidenjar_a_explode_finalized_flag = true;
					}
				}
			}

		}

		if (sp3_leidenlaser_b_erased_flag == false) {

			LeidenLaser* leidenlaser = dynamic_cast<LeidenLaser*> ((*Field::ENEMY_LASERS)[sp3_leidenlaser_b_id].get());
			leidenlaser->set_begin_pos(*position);
			leidenlaser->set_end_pos(*Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_B)->position);

			LeidenJar* leidenjar = dynamic_cast<LeidenJar*>(Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_B).get());
			switch (leidenlaser->collide_count) {
			case 0:
				leidenjar->status = LeidenJarStatus::INITIAL;
				break;
			case 1:
				leidenjar->status = LeidenJarStatus::FIRST;
				break;
			case 2:
				leidenjar->status = LeidenJarStatus::SECOND;
				break;
			case 3:
				leidenjar->status = LeidenJarStatus::FINAL;
				break;
			}

			if (sp3_leidenjar_b_explode_reserved_flag == false) {
				if (leidenjar->status == LeidenJarStatus::FINAL) {
					sp3_leidenjar_b_explode_reserved_clock = DxLib::GetNowCount();
					sp3_leidenjar_b_explode_reserved_flag = true;
				}
			}

			if (sp3_leidenjar_b_explode_reserved_flag == true) {
				if (sp3_leidenjar_b_explode_initialized_flag == false) {
					int delta_time_explode_reserve = DxLib::GetNowCount() - sp3_leidenjar_b_explode_reserved_clock;
					if (delta_time_explode_reserve > SP3_LEIDENJAR_EXPLODE_WAIT_TIME) {

						for (int i = 0; i < SP3_LEIDENJAR_EXPLODE_NOZZLES; i++) {
							double this_arg = 2 * pi / SP3_LEIDENJAR_EXPLODE_NOZZLES * i;

							(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
								leidenjar->position->x,
								leidenjar->position->y,
								this_arg,
								SP3_LEIDENJAR_EXPLODE_SHOT_SPEED,
								SP3_LEIDENJAR_EXPLODE_SHOT_COLLIDANT_SIZE,
								1,
								SkinID::NEON_SP3_EXPLOSION
							);

						}

						//sp3_leidenjar_b_explosion = make_unique<RotatingStraightShotEmission>(
						//	leidenjar->position->x,
						//	leidenjar->position->y,
						//	0,
						//	pi,
						//	true,
						//	114514,
						//	24,
						//	200,
						//	150,
						//	15,
						//	1,
						//	TeamID::ENEMY,
						//	SkinID::NEON_SP3_EXPLOSION
						//);

						Field::ERASE_ZAKO_CHARACTER(CharacterID::LEIDENJAR_B);
						Field::ENEMY_LASERS->erase(sp3_leidenlaser_b_id);

						sp3_leidenjar_b_explode_initialized_flag = true;
						sp3_leidenjar_b_explode_initialized_clock = DxLib::GetNowCount();
					}
				}
			}

			if (sp3_leidenjar_b_explode_initialized_flag == true) {
				if (sp3_leidenjar_b_explode_finalized_flag == false) {
					int delta_time_explode_initialized = DxLib::GetNowCount() - sp3_leidenjar_b_explode_initialized_clock;
					if (delta_time_explode_initialized < 4000) {
						//sp3_leidenjar_b_explosion->update();
					}
					else {
						sp3_leidenjar_b_explode_finalized_flag = true;
					}
				}
			}

		}

		if (sp3_leidenlaser_c_erased_flag == false) {

			LeidenLaser* leidenlaser = dynamic_cast<LeidenLaser*> ((*Field::ENEMY_LASERS)[sp3_leidenlaser_c_id].get());
			leidenlaser->set_begin_pos(*position);
			leidenlaser->set_end_pos(*Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_C)->position);

			LeidenJar* leidenjar = dynamic_cast<LeidenJar*>(Field::GET_ZAKO_CHARACTER(CharacterID::LEIDENJAR_C).get());
			switch (leidenlaser->collide_count) {
			case 0:
				leidenjar->status = LeidenJarStatus::INITIAL;
				break;
			case 1:
				leidenjar->status = LeidenJarStatus::FIRST;
				break;
			case 2:
				leidenjar->status = LeidenJarStatus::SECOND;
				break;
			case 3:
				leidenjar->status = LeidenJarStatus::FINAL;
				break;
			}

			if (sp3_leidenjar_c_explode_reserved_flag == false) {
				if (leidenjar->status == LeidenJarStatus::FINAL) {
					sp3_leidenjar_c_explode_reserved_clock = DxLib::GetNowCount();
					sp3_leidenjar_c_explode_reserved_flag = true;
				}
			}

			if (sp3_leidenjar_c_explode_reserved_flag == true) {
				if (sp3_leidenjar_c_explode_initialized_flag == false) {
					int delta_time_explode_reserve = DxLib::GetNowCount() - sp3_leidenjar_c_explode_reserved_clock;
					if (delta_time_explode_reserve > SP3_LEIDENJAR_EXPLODE_WAIT_TIME) {

						for (int i = 0; i < SP3_LEIDENJAR_EXPLODE_NOZZLES; i++) {
							double this_arg = 2 * pi / SP3_LEIDENJAR_EXPLODE_NOZZLES * i;

							(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
								leidenjar->position->x,
								leidenjar->position->y,
								this_arg,
								SP3_LEIDENJAR_EXPLODE_SHOT_SPEED,
								SP3_LEIDENJAR_EXPLODE_SHOT_COLLIDANT_SIZE,
								1,
								SkinID::NEON_SP3_EXPLOSION
							);

						}

						//sp3_leidenjar_c_explosion = make_unique<RotatingStraightShotEmission>(
						//	leidenjar->position->x,
						//	leidenjar->position->y,
						//	0,
						//	pi,
						//	true,
						//	114514,
						//	24,
						//	200,
						//	150,
						//	15,
						//	1,
						//	TeamID::ENEMY,
						//	SkinID::NEON_SP3_EXPLOSION
						//);

						Field::ERASE_ZAKO_CHARACTER(CharacterID::LEIDENJAR_C);
						Field::ENEMY_LASERS->erase(sp3_leidenlaser_c_id);

						sp3_leidenjar_c_explode_initialized_flag = true;
						sp3_leidenjar_c_explode_initialized_clock = DxLib::GetNowCount();
					}
				}
			}

			if (sp3_leidenjar_c_explode_initialized_flag == true) {
				if (sp3_leidenjar_c_explode_finalized_flag == false) {
					int delta_time_explode_initialized = DxLib::GetNowCount() - sp3_leidenjar_c_explode_initialized_clock;
					if (delta_time_explode_initialized < 4000) {
						//sp3_leidenjar_c_explosion->update();
					}
					else {
						sp3_leidenjar_c_explode_finalized_flag = true;
					}
				}
			}

		}

		bool repeat_flag =
			(sp3_leidenlaser_a_erased_flag || sp3_leidenjar_a_explode_initialized_flag) &&
			(sp3_leidenlaser_b_erased_flag || sp3_leidenjar_b_explode_initialized_flag) &&
			(sp3_leidenlaser_c_erased_flag || sp3_leidenjar_c_explode_initialized_flag);
		if (repeat_flag == true) {
			sp3_leidenjar_emitted_flag = false;
			sp3_leidenlaser_generated_flag = false;
			sp3_leidenlaser_a_erased_flag = false;
			sp3_leidenlaser_b_erased_flag = false;
			sp3_leidenlaser_c_erased_flag = false;
			sp3_leidenjar_a_explode_reserved_flag = false;
			sp3_leidenjar_b_explode_reserved_flag = false;
			sp3_leidenjar_c_explode_reserved_flag = false;
			sp3_leidenjar_a_explode_initialized_flag = false;
			sp3_leidenjar_b_explode_initialized_flag = false;
			sp3_leidenjar_c_explode_initialized_flag = false;
			sp3_leidenjar_a_explode_finalized_flag = false;
			sp3_leidenjar_b_explode_finalized_flag = false;
			sp3_leidenjar_c_explode_finalized_flag = false;
		}

	}
	else {
		Field::ZAKO_CHARACTERS->clear();
		Field::ENEMY_LASERS->clear();
		GameConductor::TECHNICAL_SCORE += SP3_ACCOMPLISH_BONUS;
		STATUS = NeonStatus::NORMAL4;
		kept_clock = GetNowCount();
		ZkChrStg2BsNm4::ESCAPE_FLAG = false;
	}
}

void Neon::sp4() {		// 「シャッフルトレイン」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > 0) {
		int sp4_shuffle_fire_generated_delta_time = DxLib::GetNowCount() - sp4_shuffle_fire_last_generated_clock;	// シャッフル弾
		if (sp4_shuffle_fire_generated_delta_time > SP4_SHUFFLE_FIRE_INTERVAL) {
			int sp4_shuffle_tick_generated_delta_time = DxLib::GetNowCount() - sp4_shuffle_tick_last_generated_clock;
			if (sp4_shuffle_tick_generated_delta_time > SP4_SHUFFLE_TICK_INTERVAL) {
				for (int j = 0; j < SP4_SHUFFLE_CARD_NUM; ++j) {
					int shuffle_x = Field::PIXEL_SIZE_X + 100;
					int shuffle_y = Field::PIXEL_SIZE_Y - 250 + (SP4_SHUFFLE_CARD_DISTANCE * (j + 1));
					unsigned int shuffle_offensive_id = Bullet::GENERATE_ID();
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
		for (auto& shuffle_ids : sp4_shuffles_ids) {							// シャッフル処理
			auto id = shuffle_ids.at(0);
			if (Field::ENEMY_BULLETS->count(id) == 1
				&& (*Field::ENEMY_BULLETS)[id]->position->x < SP4_SHUFFLE_DOWN_CRITERION_X
				&& (*Field::ENEMY_BULLETS)[id]->arg >= 2.0 / 3.0 * pi
				&& (*Field::ENEMY_BULLETS)[id]->arg <= 4.0 / 3.0 * pi)
			{
				for (auto& shuffle_id : shuffle_ids) {
					if (Field::ENEMY_BULLETS->count(shuffle_id) == 1) {
						(*Field::ENEMY_BULLETS)[shuffle_id]->set_arg(SP4_SHUFFLE_DOWN_ARG);		// フィールドに弾が存在しているので偏角と速度を変える
						(*Field::ENEMY_BULLETS)[shuffle_id]->set_speed(SP4_SHUFFLE_DOWN_SPEED);
					}
				}
			}
			if (Field::ENEMY_BULLETS->count(id) == 1							// EXIT処理
				&& (*Field::ENEMY_BULLETS)[id]->position->y < SP4_SHUFFLE_EXIT_CRITERION_Y
				&& (*Field::ENEMY_BULLETS)[id]->arg >= 4.0 / 3.0 * pi
				&& (*Field::ENEMY_BULLETS)[id]->arg <= 5.0 / 3.0 * pi)
			{
				for (auto& shuffle_id : shuffle_ids) {
					if (Field::ENEMY_BULLETS->count(shuffle_id) == 1) {
						(*Field::ENEMY_BULLETS)[shuffle_id]->set_arg(SP4_SHUFFLE_EXIT_ARG);		// フィールドに弾が存在しているので偏角と速度を変える
						(*Field::ENEMY_BULLETS)[shuffle_id]->set_speed(SP4_SHUFFLE_EXIT_SPEED);
					}
				}
			}
		}
		int sp4_train_fire_generated_delta_time = DxLib::GetNowCount() - sp4_train_fire_last_generated_clock;	// トレイン(追尾)弾
		if (sp4_train_fire_generated_delta_time > SP4_TRAIN_FIRE_INTERVAL) {
			int sp4_train_tick_generated_delta_time = DxLib::GetNowCount() - sp4_train_tick_last_generated_clock;
			if (sp4_train_tick_generated_delta_time > SP4_TRAIN_TICK_INTERVAL) {
				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double sp4_train_delta_x_mychr = my_chr_pos.x - position->x;
				double sp4_train_delta_y_mychr = my_chr_pos.y - position->y;
				double sp4_train_arg_toward_mychr = atan2(sp4_train_delta_y_mychr, sp4_train_delta_x_mychr);
				unsigned int train_offensive_id = Bullet::GENERATE_ID();
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
			if (Field::ENEMY_BULLETS->count(id) == 1){															// 現在フィールド上に弾があるかどうか
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
		GameConductor::TECHNICAL_SCORE += SP4_ACCOMPLISH_BONUS;
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