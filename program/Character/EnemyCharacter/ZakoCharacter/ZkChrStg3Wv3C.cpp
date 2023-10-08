#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv3C.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg3Wv3C::INIT_POS_X = Field::PIXEL_SIZE_X / 2;
const double ZkChrStg3Wv3C::INIT_POS_Y = Field::PIXEL_SIZE_Y + 100;
const double ZkChrStg3Wv3C::INIT_SPEED = 200;
const double ZkChrStg3Wv3C::INIT_ARG = 3.0 / 2.0 * pi;
const unsigned int ZkChrStg3Wv3C::INIT_HP = 50;
const unsigned int ZkChrStg3Wv3C::COLLIDANT_SIZE = 25;
const double ZkChrStg3Wv3C::SHOT_SPEED = 100;
const unsigned int ZkChrStg3Wv3C::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv3C::ENTER_TIME = 1000;
const unsigned int ZkChrStg3Wv3C::STAY_TIME = 12000;
const unsigned int ZkChrStg3Wv3C::TICKS = 1;
const unsigned int ZkChrStg3Wv3C::SHOTS = 3;
const unsigned int ZkChrStg3Wv3C::TICK_INTERVAL = 2000;
const unsigned int ZkChrStg3Wv3C::SHOT_INTERVAL = 100;


const double ZkChrStg3Wv3C::DRAW_EXTRATE = 0.07;

ZkChrStg3Wv3C::ZkChrStg3Wv3C() :
	Character(
		CharacterID::ZKCHRSTG3WV3_C,
		INIT_POS_X,
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)
	),
	speed(INIT_SPEED),
	arg(INIT_ARG),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	move_clock(DxLib::GetNowCount()),
	last_tick_generated_clock(DxLib::GetNowCount()),
	last_shot_completed_clock(DxLib::GetNowCount()),
	tick_count(0),
	shot_count(0),
	move_status(Stg3WAVE3MoveFlag::ENTER)
{
}

void ZkChrStg3Wv3C::update() {
	int elapsed_time = DxLib::GetNowCount() - move_clock;
	if (move_status == Stg3WAVE3MoveFlag::ENTER) {
		if (elapsed_time > ENTER_TIME) {
			speed = 0;
			move_status = Stg3WAVE3MoveFlag::STAY;
		}
	}
	else if (move_status == Stg3WAVE3MoveFlag::STAY) {
		if (elapsed_time > ENTER_TIME + STAY_TIME) {
			speed = 100;
			arg = 1.0 / 2.0 * pi;
			move_status = Stg3WAVE3MoveFlag::EXIT;
		}
		if (shot_count < SHOTS) {
			if (tick_count < TICKS) {
				int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;
				if (tick_generated_delta_time > TICK_INTERVAL) {
					for (int i = 0; i < 12; ++i) {
						arg = 1.0 / 6.0 * pi * i;
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
							position->x,
							position->y,
							arg,
							SHOT_SPEED,
							SHOT_COLLIDANT_SIZE,
							1,
							SkinID::STG3_WAVE3_C
						);
					}
					DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
					++tick_count;
					last_tick_generated_clock = DxLib::GetNowCount();
				}
			}
			else {
				int shot_complete_delta_time = DxLib::GetNowCount() - last_shot_completed_clock;
				if (shot_complete_delta_time > SHOT_INTERVAL) {
					++shot_count;
					tick_count = 0;
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

void ZkChrStg3Wv3C::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_MEZDOROGON, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}