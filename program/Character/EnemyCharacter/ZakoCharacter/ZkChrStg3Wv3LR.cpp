#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv3LR.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg3Wv3LR::L_INIT_POS_X = Field::PIXEL_SIZE_X / 2 - 200;
const double ZkChrStg3Wv3LR::R_INIT_POS_X = Field::PIXEL_SIZE_X / 2 + 200;
const double ZkChrStg3Wv3LR::INIT_POS_Y = Field::PIXEL_SIZE_Y - 100;
const double ZkChrStg3Wv3LR::INIT_SPEED = 100;
const double ZkChrStg3Wv3LR::INIT_ARG = 3.0 / 2.0 * pi;
const unsigned int ZkChrStg3Wv3LR::INIT_HP = 30;
const unsigned int ZkChrStg3Wv3LR::COLLIDANT_SIZE = 20;
const double ZkChrStg3Wv3LR::SHOT_SPEED = 300;
const unsigned int ZkChrStg3Wv3LR::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv3LR::TICKS = 4;
const unsigned int ZkChrStg3Wv3LR::SHOTS = 3;
const unsigned int ZkChrStg3Wv3LR::TICK_INTERVAL = 100;
const unsigned int ZkChrStg3Wv3LR::SHOT_INTERVAL = 5000;
const double ZkChrStg3Wv3LR::SHIFT_ARG = 2.0 / 360.0 * 2.0 * pi;
const unsigned int ZkChrStg3Wv3LR::ENTER_TIME = 1000;
const unsigned int ZkChrStg3Wv3LR::STAY_TIME = 12000;

const double ZkChrStg3Wv3LR::DRAW_EXTRATE = 0.07;

int ZkChrStg3Wv3LR::INIT_POS_X(enum CharacterID id) {
	if (id == CharacterID::ZKCHRSTG3WV3_L) {
		return L_INIT_POS_X;
	}
	else if (id == CharacterID::ZKCHRSTG3WV3_R) {
		return R_INIT_POS_X;
	}
}

ZkChrStg3Wv3LR::ZkChrStg3Wv3LR(enum CharacterID given_id) :
	Character(
		given_id,
		INIT_POS_X(given_id),
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X(given_id), INIT_POS_Y, COLLIDANT_SIZE)
	),
	speed(INIT_SPEED),
	arg(INIT_ARG),
	shot_count(0),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_tick_generated_clock(DxLib::GetNowCount()),
	last_shot_completed_clock(DxLib::GetNowCount()),
	move_clock(DxLib::GetNowCount()),
	move_status(Stg3WAVE3MoveFlag::ENTER),
	launch_ways(7)
{
}

void ZkChrStg3Wv3LR::update() {
	int elapsed_time = DxLib::GetNowCount() - move_clock;

	if (move_status == Stg3WAVE3MoveFlag::ENTER) {
		if (elapsed_time > ENTER_TIME) {
			speed = 0;
			move_status = Stg3WAVE3MoveFlag::STAY;
		}
	}
	else if (move_status == Stg3WAVE3MoveFlag::STAY) {
		if (elapsed_time > ENTER_TIME + STAY_TIME) {
			arg = 1.0 / 2.0 * pi;
			speed = 100;
			move_status = Stg3WAVE3MoveFlag::EXIT;
		}
		if (shot_count < SHOTS) {
			if (tick_count < TICKS) {
				int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;
				if (tick_generated_delta_time > TICK_INTERVAL) {
					InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
					double delta_x_mychr = my_chr_pos.x - position->x;
					double delta_y_mychr = my_chr_pos.y - position->y;
					double arg_toword_mychr = atan2(delta_y_mychr, delta_x_mychr);

					(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
						position->x,
						position->y,
						arg_toword_mychr,
						SHOT_SPEED,
						SHOT_COLLIDANT_SIZE,
						1,
						SkinID::STG3_WAVE3_LR
					);

					for (int dup_count = 1; dup_count <= launch_ways / 2; ++dup_count) {
						double arg_toword_mychr_add = arg_toword_mychr + SHIFT_ARG * dup_count;
						double arg_toword_mychr_sub = arg_toword_mychr - SHIFT_ARG * dup_count;
						(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
							position->x,
							position->y,
							arg_toword_mychr_add,
							SHOT_SPEED,
							SHOT_COLLIDANT_SIZE,
							1,
							SkinID::STG3_WAVE3_LR
						);
						(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
							position->x,
							position->y,
							arg_toword_mychr_sub,
							SHOT_SPEED,
							SHOT_COLLIDANT_SIZE,
							1,
							SkinID::STG3_WAVE3_LR
						);
					}

					DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
					++tick_count;
					launch_ways -= 2;
					last_tick_generated_clock = DxLib::GetNowCount();
				}
			}
			else {
				int shot_complete_delta_time = DxLib::GetNowCount() - last_shot_completed_clock;
				if (shot_complete_delta_time > SHOT_INTERVAL) {
					++shot_count;
					tick_count = 0;
					launch_ways = 7;
					last_shot_completed_clock = DxLib::GetNowCount();
				}
			}
		}
	}
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}

void ZkChrStg3Wv3LR::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_GOZGOK, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}