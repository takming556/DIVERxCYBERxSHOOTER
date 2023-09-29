#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Barrage/Emission/StraightShotEmission/RotatingStraightShotEmission.h"
#include "CollideRealm/CollideCircle.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv3L.h"
#include "ImageHandles.h"
#include "DebugParams.h"

using std::unique_ptr;
using std::make_unique;
using std::numbers::pi;

const unsigned int ZkChrStg1Wv3L::STAY_POS_Y = 575;
const double ZkChrStg1Wv3L::INIT_ARG = 3.0 / 2.0 * pi;
const double ZkChrStg1Wv3L::INIT_SPEED = 100;

const unsigned int ZkChrStg1Wv3L::INITIAL_HP = 25;
const unsigned int ZkChrStg1Wv3L::COLLIDANT_SIZE = 20;
const double ZkChrStg1Wv3L::DRAW_EXTRATE = 0.07;

const unsigned int ZkChrStg1Wv3L::BARRAGE_EMIT_NOZZLES = 5;
const unsigned int ZkChrStg1Wv3L::BARRAGE_EMIT_INTERVAL = 2000;
const double ZkChrStg1Wv3L::BARRAGE_INIT_ARG = -(1.0 / 2.0) * pi;
const double ZkChrStg1Wv3L::BARRAGE_SHOT_SPEED = 150.0;
const unsigned int ZkChrStg1Wv3L::BARRAGE_SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv3L::BARRAGE_SHOT_DURABILITY = 1;



ZkChrStg1Wv3L::ZkChrStg1Wv3L(
	enum CharacterID given_id,
	double init_pos_x,
	double init_pos_y,
	double barrage_rotate_speed
):
	Character(
		given_id,
		init_pos_x,
		init_pos_y,
		INITIAL_HP,
		make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)
	),
	barrage(make_unique<RotatingStraightShotEmission>(
		init_pos_x,
		init_pos_y,
		BARRAGE_INIT_ARG,
		barrage_rotate_speed,
		true,
		114514,
		BARRAGE_EMIT_NOZZLES,
		BARRAGE_EMIT_INTERVAL,
		BARRAGE_SHOT_SPEED,
		BARRAGE_SHOT_COLLIDANT_SIZE,
		BARRAGE_SHOT_DURABILITY,
		TeamID::ENEMY,
		SkinID::BUBBLE_GENERIC
		)
	),
	arg(INIT_ARG),
	speed(INIT_SPEED),
	status(Stg1WAVE3LMode::ENTER),
	stay_clock_started(DxLib::GetNowCount()),
	stay_count(0),
	last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
}


void ZkChrStg1Wv3L::update() {
	if (status == Stg1WAVE3LMode::ENTER) {
		if (position->y <= STAY_POS_Y) {
			status = Stg1WAVE3LMode::STAY;
		}
		speed = 100;
		arg = 3.0 / 2.0 * pi;
	}
	else if (status == Stg1WAVE3LMode::STAY) {
		if (stay_count == 0) {
			stay_clock_started = DxLib::GetNowCount();
			++stay_count;
		}
		int stay_delta_time = DxLib::GetNowCount() - stay_clock_started;
		if (stay_delta_time > 16000) {
			status = Stg1WAVE3LMode::EXIT;
		}
		speed = 0;
	}
	else if (status == Stg1WAVE3LMode::EXIT) {
		speed = 100;
		arg = 1.0 / 2.0 * pi;
	}
	
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	if (status == Stg1WAVE3LMode::STAY) {
		barrage->update(position->x, position->y);
	}
}


void ZkChrStg1Wv3L::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KURAGE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}