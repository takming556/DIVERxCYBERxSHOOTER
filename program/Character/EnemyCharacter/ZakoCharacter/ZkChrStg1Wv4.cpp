#include <memory>
#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Barrage/Emission/StraightShotEmission/SimpleStraightShotEmission.h"
#include "CollideRealm/CollideCircle.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv4.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::unique_ptr;
using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;

const double ZkChrStg1Wv4::INIT_ARG = 3.0 / 2.0 * pi;
const double ZkChrStg1Wv4::INIT_SPEED = 150;
const unsigned int ZkChrStg1Wv4::INITIAL_HP = 10;
const unsigned int ZkChrStg1Wv4::COLLIDANT_SIZE = 20;
const double ZkChrStg1Wv4::DRAW_EXTRATE = 0.085;

const unsigned int ZkChrStg1Wv4::LINES_TICKS = 3;
const unsigned int ZkChrStg1Wv4::LINES_SHOTS = 5;
const unsigned int ZkChrStg1Wv4::LINES_TICK_INTERVAL = 125;
const unsigned int ZkChrStg1Wv4::LINES_SHOT_INTERVAL = 1500;
const double ZkChrStg1Wv4::LINES_SHOT_SPEED = 200.0;
const unsigned int ZkChrStg1Wv4::LINES_SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv4::LINES_SHOT_DURABILITY = 1;

const unsigned int ZkChrStg1Wv4::BARRAGE_EMIT_NOZZLES = 5;
const unsigned int ZkChrStg1Wv4::BARRAGE_EMITS = 5;
const unsigned int ZkChrStg1Wv4::BARRAGE_EMIT_INTERVAL = 2000;
const double ZkChrStg1Wv4::BARRAGE_INIT_ARG = 0.0;
const double ZkChrStg1Wv4::BARRAGE_SHOT_SPEED = 150.0;
const unsigned int ZkChrStg1Wv4::BARRAGE_SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv4::BARRAGE_SHOT_DURABILITY = 1;



ZkChrStg1Wv4::ZkChrStg1Wv4(
	enum CharacterID given_id,
	double init_pos_x,
	double init_pos_y
):
	Character(
		given_id,
		init_pos_x,
		init_pos_y,
		INITIAL_HP,
		make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)
	),
	arg(0),
	speed(0),
	stay_pos_y(init_pos_y - 150),
	stay_count(0),
	stay_clock_started(DxLib::GetNowCount()),
	tick_count(0),
	shot_count(0),
	last_lines_tick_fired_clock(DxLib::GetNowCount()),
	last_lines_shot_completed_clock(DxLib::GetNowCount()),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	barrage(make_unique<SimpleStraightShotEmission>(
		init_pos_x,
		init_pos_y,
		BARRAGE_INIT_ARG,
		false,
		BARRAGE_EMITS,
		BARRAGE_EMIT_NOZZLES,
		BARRAGE_EMIT_INTERVAL,
		BARRAGE_SHOT_SPEED,
		BARRAGE_SHOT_COLLIDANT_SIZE,
		BARRAGE_SHOT_DURABILITY,
		TeamID::ENEMY,
		SkinID::BUBBLE_GENERIC
		)
	),
	status(Stg1WAVE4Mode::ENTER)
{
}


void ZkChrStg1Wv4::update() {
	if (status == Stg1WAVE4Mode::ENTER) {
		if (position->y <= stay_pos_y) {
			status = Stg1WAVE4Mode::STAY;
		}
		arg = 3.0 / 2.0 * pi;
		speed = 150;
	}
	else if (status == Stg1WAVE4Mode::STAY) {
		if (stay_count == 0) {
			stay_clock_started = DxLib::GetNowCount();
			++stay_count;
		}
		int stay_delta_time = DxLib::GetNowCount() - stay_clock_started;
		if (stay_delta_time > 8000) {
			status = Stg1WAVE4Mode::EXIT;
		}
		speed = 0;
	}
	else if (status == Stg1WAVE4Mode::EXIT) {
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
	barrage->update(position->x, position->y);

	if (status == Stg1WAVE4Mode::STAY) {
		if (shot_count < LINES_SHOTS) {
			if (tick_count < LINES_TICKS) {
				int tick_fire_delta_time = DxLib::GetNowCount() - last_lines_tick_fired_clock;
				if (tick_fire_delta_time > LINES_TICK_INTERVAL) {

					InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
					double delta_x_mychr = my_chr_pos.x - position->x;
					double delta_y_mychr = my_chr_pos.y - position->y;
					double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);

					(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
						position->x,
						position->y,
						arg_toward_mychr + (1.0 / 12.0) * pi,
						LINES_SHOT_SPEED,
						LINES_SHOT_COLLIDANT_SIZE,
						LINES_SHOT_DURABILITY,
						SkinID::BUBBLE_GENERIC
						);
					DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

					(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
						position->x,
						position->y,
						arg_toward_mychr,
						LINES_SHOT_SPEED,
						LINES_SHOT_COLLIDANT_SIZE,
						LINES_SHOT_DURABILITY,
						SkinID::BUBBLE_GENERIC
						);
					DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

					(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
						position->x,
						position->y,
						arg_toward_mychr - (1.0 / 12.0) * pi,
						LINES_SHOT_SPEED,
						LINES_SHOT_COLLIDANT_SIZE,
						LINES_SHOT_DURABILITY,
						SkinID::BUBBLE_GENERIC
						);
					DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);


					++tick_count;
					last_lines_tick_fired_clock = DxLib::GetNowCount();
				}
			}
			else {
				int shot_complete_delta_time = DxLib::GetNowCount() - last_lines_shot_completed_clock;
				if (shot_complete_delta_time > LINES_SHOT_INTERVAL) {
					++shot_count;
					tick_count = 0;
					last_lines_shot_completed_clock = DxLib::GetNowCount();
				}
			}
		}
	}

}


void ZkChrStg1Wv4::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KUJIRA, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}