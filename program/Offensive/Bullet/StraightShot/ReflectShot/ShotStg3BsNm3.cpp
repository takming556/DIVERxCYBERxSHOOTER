#include "Offensive/Bullet/StraightShot/ReflectShot/ShotStg3BsNm3.h"


ShotStg3BsNm3::ShotStg3BsNm3(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	unsigned int collidant_size,
	unsigned int durability,
	SkinID given_skin_id
) :
	Offensive(given_skin_id),
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability, collidant_size)
{
}


void ShotStg3BsNm3::update() {
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


void ShotStg3BsNm3::draw() {

}