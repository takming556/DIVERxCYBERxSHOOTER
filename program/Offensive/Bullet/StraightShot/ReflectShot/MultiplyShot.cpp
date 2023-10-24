#include <memory>
#include <numbers>
#include "Field.h"
#include "Offensive/Bullet/Bullet.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Offensive/Bullet/StraightShot/ReflectShot/MultiplyShot.h"
#include "ImageHandles.h"
#include "DebugParams.h"


using std::numbers::pi;
using std::make_unique;

const double MultiplyShot::SPEED = 200;
const unsigned int MultiplyShot::COLLIDANT_SIZE = 10;
const unsigned int MultiplyShot::MULTIPLY_INTERVAL = 3000;
const double MultiplyShot::DRAW_EXTRATE = 0.75;

MultiplyShot::MultiplyShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg
) :
	Offensive(SkinID::TOROI_NM1_MULTIPLY),
	Bullet(init_pos_x, init_pos_y, init_arg, SPEED, 1, COLLIDANT_SIZE),
	kept_clock(DxLib::GetNowCount())
{
}

void MultiplyShot::update() {
	int elapsed_time = DxLib::GetNowCount() - kept_clock;

	if (elapsed_time > MULTIPLY_INTERVAL) {
		clone();
		kept_clock = DxLib::GetNowCount();
	}

	if (position->x < InFieldPosition::MIN_MOVABLE_BOUNDARY_X && left_wall_last_collided_flag == false) {
		reflect_on_leftline();
		clone();
		left_wall_last_collided_flag = true;
	}
	else if (position->x > InFieldPosition::MIN_MOVABLE_BOUNDARY_X && left_wall_last_collided_flag == true) {
		left_wall_last_collided_flag = false;
	}

	if (position->x > InFieldPosition::MAX_MOVABLE_BOUNDARY_X && right_wall_last_collided_flag == false) {
		reflect_on_rightline();
		clone();
		right_wall_last_collided_flag = true;
	}
	else if (position->x < InFieldPosition::MAX_MOVABLE_BOUNDARY_X && right_wall_last_collided_flag == true) {
		right_wall_last_collided_flag = false;
	}

	if (position->y < InFieldPosition::MIN_MOVABLE_BOUNDARY_Y && bottom_wall_last_collided_flag == false) {
		reflect_on_bottomline();
		clone();
		bottom_wall_last_collided_flag = true;
	}
	else if (position->y > InFieldPosition::MIN_MOVABLE_BOUNDARY_Y && bottom_wall_last_collided_flag == true) {
		bottom_wall_last_collided_flag = false;
	}

	if (position->y > InFieldPosition::MAX_MOVABLE_BOUNDARY_Y && top_wall_last_collided_flag == false) {
		reflect_on_topline();
		clone();
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

void MultiplyShot::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, arg, ImageHandles::BUBBLE_PURPLE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}

void MultiplyShot::clone() {
	double clone_arg = arg - 1.0 / 36.0 * pi + 2.0 / 36.0 * DxLib::GetRand(1) * pi;	// Å}1.0 / 36.0 Ç…ÉNÉçÅ[ÉìÇê∂ê¨ 
	(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<MultiplyShot>(
		position->x,
		position->y,
		clone_arg
	);
}