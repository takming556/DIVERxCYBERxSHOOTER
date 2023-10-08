#include <memory>
#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Position/Position.h"
#include "Position/InFieldPosition.h"
#include "CollideRealm/CollideRealm.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv3S.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::unique_ptr;
using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;

const double ZkChrStg1Wv3S::INIT_ARG = 3.0 / 2.0 * pi;
const double ZkChrStg1Wv3S::INIT_SPEED = 150;
const unsigned int ZkChrStg1Wv3S::INITIAL_HP = 15;
const unsigned int ZkChrStg1Wv3S::COLLIDANT_SIZE = 20;

const unsigned int ZkChrStg1Wv3S::TICKS = 3;
const unsigned int ZkChrStg1Wv3S::TICK_INTERVAL = 125;
const unsigned int ZkChrStg1Wv3S::SHOT_INTERVAL = 2000;
const double ZkChrStg1Wv3S::SHOT_SPEED = 200;
const unsigned int ZkChrStg1Wv3S::SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv3S::SHOT_DURABILITY = 1;

const double ZkChrStg1Wv3S::DRAW_EXTRATE = 0.07;



ZkChrStg1Wv3S::ZkChrStg1Wv3S(
	enum CharacterID given_id,
	double init_pos_x,
	double init_pos_y
) :
	Character(
		given_id,
		init_pos_x,
		init_pos_y,
		INITIAL_HP,
		make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)
	),
	arg(INIT_ARG),
	speed(INIT_SPEED),
	stay_pos_y(init_pos_y - 250),
	stay_count(0),
	stay_clock_started(DxLib::GetNowCount()),
	tick_count(0),
	last_shot_completed_clock(DxLib::GetNowCount()),
	last_tick_fired_clock(DxLib::GetNowCount()),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	status(Stg1WAVE3SMode::ENTER)
{
}


void ZkChrStg1Wv3S::update() {
	if (status == Stg1WAVE3SMode::ENTER) {
		if (position->y <= stay_pos_y) {
			status = Stg1WAVE3SMode::STAY;
		}
		arg = 3.0 / 2.0 * pi;
		speed = 150;
	}
	else if (status == Stg1WAVE3SMode::STAY) {
		if (stay_count == 0) {
			stay_clock_started = DxLib::GetNowCount();
			++stay_count;
		}
		int stay_delta_time = DxLib::GetNowCount() - stay_clock_started;
		if (stay_delta_time > 16000) {
			status = Stg1WAVE3SMode::EXIT;
		}
		speed = 0;
	}
	else if (status == Stg1WAVE3SMode::EXIT) {
		arg = 1.0 / 2.0 * pi;
		speed = 150;
	}

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	if (status == Stg1WAVE3SMode::STAY) {
		if (tick_count < TICKS) {
			int tick_fire_delta_time = DxLib::GetNowCount() - last_tick_fired_clock;
			if (tick_fire_delta_time > TICK_INTERVAL) {

				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double delta_x_mychr = my_chr_pos.x - position->x;
				double delta_y_mychr = my_chr_pos.y - position->y;
				double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr,
					SHOT_SPEED,
					SHOT_COLLIDANT_SIZE,
					SHOT_DURABILITY,
					SkinID::BUBBLE_GENERIC
					);

				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				++tick_count;
				last_tick_fired_clock = DxLib::GetNowCount();
			}
		}
		else {
			int shot_complete_delta_time = DxLib::GetNowCount() - last_shot_completed_clock;
			if (shot_complete_delta_time > SHOT_INTERVAL) {
				tick_count = 0;
				last_shot_completed_clock = DxLib::GetNowCount();
			}
		}
	}
}


void ZkChrStg1Wv3S::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KUJIRA, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}