#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv8L.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg2Wv8L::INIT_POS_X = InFieldPosition::MIN_MOVABLE_BOUNDARY_X - 50;
const double ZkChrStg2Wv8L::INIT_POS_Y = InFieldPosition::MIN_MOVABLE_BOUNDARY_Y + 100;
const double ZkChrStg2Wv8L::INIT_SPEED = 100;
const double ZkChrStg2Wv8L::INIT_ARG = 0.0 * pi;
const unsigned int ZkChrStg2Wv8L::COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg2Wv8L::INIT_HP = 10;
const unsigned int ZkChrStg2Wv8L::LINE_UP_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y - 130;

const double ZkChrStg2Wv8L::DRAW_EXTRATE = 0.05;

Stg2WAVE8WaitFlag ZkChrStg2Wv8L::WAIT_FLAG_L = Stg2WAVE8WaitFlag::WAIT;

ZkChrStg2Wv8L::ZkChrStg2Wv8L(enum CharacterID given_id, int line_up_position_x, double lower_speed) :
	Character(
		given_id,
		INIT_POS_X,
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)
	),
	line_up_x(line_up_position_x),
	speed(INIT_SPEED),
	lower_down_speed(lower_speed),
	arg(INIT_ARG),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_generated_clock(DxLib::GetNowCount()),
	move_status(Stg2WAVE8MoveFlag::RAISE)
{
}

void ZkChrStg2Wv8L::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (move_status == Stg2WAVE8MoveFlag::RAISE) {
		arg += 1.0 / 20.0 * pi * update_delta_time / 1000 / 1000;
		if (position->y > LINE_UP_Y) {
			move_status = Stg2WAVE8MoveFlag::LINE_UP;
		}
	}
	else if (move_status == Stg2WAVE8MoveFlag::LINE_UP) {
		arg = 1.0 * pi;
		if (position->x < line_up_x) {
			move_status = Stg2WAVE8MoveFlag::WAIT;
		}
	}
	else if (move_status == Stg2WAVE8MoveFlag::WAIT) {
		speed = 0;
		if (WAIT_FLAG_L == Stg2WAVE8WaitFlag::GO) {
			move_status = Stg2WAVE8MoveFlag::LOWER;
		}
	}
	else if (move_status == Stg2WAVE8MoveFlag::LOWER) {
		arg = 3.0 / 2.0 * pi;
		speed = lower_down_speed;
	}

	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}

void ZkChrStg2Wv8L::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_LIGHT_ELE, TRUE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}