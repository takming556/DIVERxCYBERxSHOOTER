#include <memory>
#include <cmath>
#include "DxLib.h"
#include "enum.h"
#include "ImageHandles.h"
#include "DebugParams.h"
#include "Position/InFieldPosition.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/ReflectShot.h"

using std::make_unique;
using std::sin;
using std::cos;
using std::tan;
using std::atan;

ReflectShot::ReflectShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID given_skin_id
):
	Offensive(make_unique<CollideCircle>(init_pos_x, init_pos_y, collidant_size)),
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability),
	StraightShot(given_skin_id),
	left_wall_last_collided_flag(false),
	right_wall_last_collided_flag(false),
	up_wall_last_collided_flag(false),
	bottom_wall_last_collided_flag(false)
{}


void ReflectShot::reflect() {
	if (cos(arg) > 0)
		arg = -atan(-tan(arg));
	else
		arg = atan(-tan(arg));
}


void ReflectShot::update() {

	if (position->x < InFieldPosition::MIN_MOVABLE_BOUNDARY_X && left_wall_last_collided_flag == false) {
		reflect();
		left_wall_last_collided_flag = true;
	}
	else if (position->x <= InFieldPosition::MIN_MOVABLE_BOUNDARY_X && left_wall_last_collided_flag == true) {
		left_wall_last_collided_flag = false;
	}

	if (position->x > InFieldPosition::MAX_MOVABLE_BOUNDARY_X && right_wall_last_collided_flag == false) {
		reflect();
		right_wall_last_collided_flag = true;
	}
	else if (position->x <= InFieldPosition::MAX_MOVABLE_BOUNDARY_X && right_wall_last_collided_flag == true) {
		right_wall_last_collided_flag = false;
	}

	if (position->y < InFieldPosition::MIN_MOVABLE_BOUNDARY_Y && bottom_wall_last_collided_flag == false) {
		reflect();
		bottom_wall_last_collided_flag = true;
	}
	else if (position->y <= InFieldPosition::MIN_MOVABLE_BOUNDARY_Y && bottom_wall_last_collided_flag == true) {
		bottom_wall_last_collided_flag = false;
	}

	if (position->y > InFieldPosition::MAX_MOVABLE_BOUNDARY_Y && up_wall_last_collided_flag == false) {
		reflect();
		up_wall_last_collided_flag = true;
	}
	else if (position->y <= InFieldPosition::MAX_MOVABLE_BOUNDARY_Y && up_wall_last_collided_flag == true) {
		up_wall_last_collided_flag = false;
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
	case SkinID::TOROI_NM1:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BUBBLE_GREEN, TRUE);
		break;
	}
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}