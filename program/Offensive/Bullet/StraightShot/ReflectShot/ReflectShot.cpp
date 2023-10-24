#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "ImageHandles.h"
#include "DebugParams.h"
#include "Position/InFieldPosition.h"
#include "Offensive/Bullet/StraightShot/ReflectShot/ReflectShot.h"
#include "Utils.h"

using std::sin;
using std::cos;
using std::tan;
using std::atan;
using std::numbers::pi;

ReflectShot::ReflectShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	unsigned int collidant_size,
	unsigned int durability,
	SkinID given_skin_id
):
	Offensive(given_skin_id),
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability, collidant_size),
	left_wall_last_collided_flag(true),
	right_wall_last_collided_flag(true),
	top_wall_last_collided_flag(true),
	bottom_wall_last_collided_flag(true)
{
}



ReflectShot::ReflectShot() :
	left_wall_last_collided_flag(true) ,
	right_wall_last_collided_flag(true) ,
	top_wall_last_collided_flag(true) ,
	bottom_wall_last_collided_flag(true)
{
}



void ReflectShot::reflect_on_rightline() {
	arg = atan(-tan(arg)) + pi;
}


void ReflectShot::reflect_on_leftline() {
	arg = atan(-tan(arg));
}


void ReflectShot::reflect_on_topline() {
	if (cos(arg) > 0) {
		arg = atan(-tan(arg));
	}
	else {
		arg = atan(-tan(arg)) + pi;
	}
}


void ReflectShot::reflect_on_bottomline() {
	if (cos(arg) > 0) {
		arg = atan(-tan(arg));
	}
	else {
		arg = atan(-tan(arg)) + pi;
	}
}


void ReflectShot::update() {

	if (position->x < InFieldPosition::MIN_MOVABLE_BOUNDARY_X && left_wall_last_collided_flag == false) {
		reflect_on_leftline();
		left_wall_last_collided_flag = true;
	}
	else if (position->x > InFieldPosition::MIN_MOVABLE_BOUNDARY_X && left_wall_last_collided_flag == true) {
		left_wall_last_collided_flag = false;
	}

	if (position->x > InFieldPosition::MAX_MOVABLE_BOUNDARY_X && right_wall_last_collided_flag == false) {
		reflect_on_rightline();
		right_wall_last_collided_flag = true;
	}
	else if (position->x < InFieldPosition::MAX_MOVABLE_BOUNDARY_X && right_wall_last_collided_flag == true) {
		right_wall_last_collided_flag = false;
	}

	if (position->y < InFieldPosition::MIN_MOVABLE_BOUNDARY_Y && bottom_wall_last_collided_flag == false) {
		reflect_on_bottomline();
		bottom_wall_last_collided_flag = true;
	}
	else if (position->y > InFieldPosition::MIN_MOVABLE_BOUNDARY_Y && bottom_wall_last_collided_flag == true) {
		bottom_wall_last_collided_flag = false;
	}

	if (position->y > InFieldPosition::MAX_MOVABLE_BOUNDARY_Y && top_wall_last_collided_flag == false) {
		reflect_on_topline();
		top_wall_last_collided_flag = true;
	}
	else if (position->y < InFieldPosition::MAX_MOVABLE_BOUNDARY_Y && top_wall_last_collided_flag == true) {
		top_wall_last_collided_flag = false;
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


void ReflectShot::draw() {
	int delta_time_frame_update = DxLib::GetNowCount() - last_frame_updated_clock;
	Position draw_pos = position->get_draw_position();

	switch (skin_id) {
	//case SkinID::TOROI_NM1:
	//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BUBBLE_GREEN, TRUE);
	//	break;

	case SkinID::BUBBLE_GENERIC:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_AQUA, TRUE);
		break;

	}

	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}