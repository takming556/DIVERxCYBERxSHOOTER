#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Offensive/Bullet/SwayingShot.h"
#include "Offensive/Bullet/StraightShot/TurnShot.h"
#include "CollideRealm/CollideCircle.h"

using std::make_unique;
using std::numbers::pi;


TurnShot::TurnShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	unsigned int turn_postpone_time,
	double add_arg,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID given_skin_id
) :
	Offensive(make_unique<CollideCircle>(init_pos_x, init_pos_y, collidant_size)),
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability),
	StraightShot(
		init_pos_x,
		init_pos_y,
		init_arg,
		init_speed,
		collidant_size,
		durability,
		given_skin_id
	),
	already_turned_flag(false),
	generated_clock(DxLib::GetNowCount()),
	TURN_POSTPONE_TIME(turn_postpone_time),
	ADD_ARG(add_arg)
{
}


void TurnShot::update() {

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	int elapsed_time_since_generated = DxLib::GetNowCount() - generated_clock;
	if (elapsed_time_since_generated > TURN_POSTPONE_TIME && already_turned_flag == false) {
		arg += ADD_ARG;
		already_turned_flag = true;
	}

}