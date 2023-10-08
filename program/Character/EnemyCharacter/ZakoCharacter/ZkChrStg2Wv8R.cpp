#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv8R.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg2Wv8R::INIT_POS_X = InFieldPosition::MAX_MOVABLE_BOUNDARY_X + 50;
const double ZkChrStg2Wv8R::INIT_POS_Y = InFieldPosition::MIN_MOVABLE_BOUNDARY_Y + 100;
const double ZkChrStg2Wv8R::INIT_SPEED = 100;
const double ZkChrStg2Wv8R::INIT_ARG = 1.0 * pi;
const unsigned int ZkChrStg2Wv8R::COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg2Wv8R::INIT_HP = 10;
const unsigned int ZkChrStg2Wv8R::LINE_UP_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y - 50;

const double ZkChrStg2Wv8R::DRAW_EXTRATE = 0.05;

Stg2WAVE8WaitFlag ZkChrStg2Wv8R::WAIT_FLAG_R18 = Stg2WAVE8WaitFlag::WAIT;
Stg2WAVE8WaitFlag ZkChrStg2Wv8R::WAIT_FLAG_R27 = Stg2WAVE8WaitFlag::WAIT;
Stg2WAVE8WaitFlag ZkChrStg2Wv8R::WAIT_FLAG_R36 = Stg2WAVE8WaitFlag::WAIT;
Stg2WAVE8WaitFlag ZkChrStg2Wv8R::WAIT_FLAG_R45 = Stg2WAVE8WaitFlag::WAIT;

ZkChrStg2Wv8R::ZkChrStg2Wv8R(enum CharacterID given_id, int generated_id, double lower_speed) :
	Character(
		given_id,
		INIT_POS_X,
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)
	),
	line_up_x(0),
	speed(INIT_SPEED),
	lower_down_speed(lower_speed),
	arg(INIT_ARG),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_generated_clock(DxLib::GetNowCount()),
	move_status(Stg2WAVE8MoveFlag::RAISE),
	order_num(generated_id)
{
	line_up_x = InFieldPosition::MAX_MOVABLE_BOUNDARY_X - InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * generated_id;
}

void ZkChrStg2Wv8R::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (move_status == Stg2WAVE8MoveFlag::RAISE) {
		arg += -1.0 / 20.0 * pi * update_delta_time / 1000 / 1000;
		if (position->y > LINE_UP_Y) {
			move_status = Stg2WAVE8MoveFlag::LINE_UP;
		}
	}
	else if (move_status == Stg2WAVE8MoveFlag::LINE_UP) {
		arg = 0.0 * pi;
		if (position->x > line_up_x) {
			move_status = Stg2WAVE8MoveFlag::WAIT;
		}
	}
	else if (move_status == Stg2WAVE8MoveFlag::WAIT) {
		speed = 0;

		bool lower_term_18 = WAIT_FLAG_R18 == Stg2WAVE8WaitFlag::GO && (order_num == 1 || order_num == 8);
		bool lower_term_27 = WAIT_FLAG_R27 == Stg2WAVE8WaitFlag::GO && (order_num == 2 || order_num == 7);
		bool lower_term_36 = WAIT_FLAG_R36 == Stg2WAVE8WaitFlag::GO && (order_num == 3 || order_num == 6);
		bool lower_term_45 = WAIT_FLAG_R45 == Stg2WAVE8WaitFlag::GO && (order_num == 4 || order_num == 5);
		if (position->x > line_up_x - 5 && position->x < line_up_x + 5) {
			if (lower_term_18 || lower_term_27 || lower_term_36 || lower_term_45){
				move_status = Stg2WAVE8MoveFlag::LOWER;
			}
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

void ZkChrStg2Wv8R::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KNIGHT_RAY, TRUE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}