#include <memory>
#include <numbers>
#include "Field.h"
#include "Offensive/Bullet/Bullet.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Offensive/Bullet/StraightShot/ReflectShot/DVDShot.h"
#include "ImageHandles.h"
#include "DebugParams.h"


using std::numbers::pi;
using std::make_unique;


const double DVDShot::DECOY_SHOT_SPEED = 100.0;
const double DVDShot::COY_SHOT_SPEED = 100.0;
const double DVDShot::SELF_SHOT_SPEED = 300.0;
const unsigned int DVDShot::DECOY_COLLIDANT_SIZE = 0;
const unsigned int DVDShot::COY_COLLIDANT_SIZE = 10;
const unsigned int DVDShot::SELF_COLLIDANT_SIZE = 10;
const double DVDShot::DRAW_ARG = 1.0 / 2.0 * pi;
const double DVDShot::DRAW_EXTRATE = 1.25;


DVDShot::DVDShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg
) :
	Offensive(SkinID::TOROI_NM3_REFLECT),
	Bullet(init_pos_x, init_pos_y, init_arg, SELF_SHOT_SPEED, 1000000, SELF_COLLIDANT_SIZE),
	collide_count(0)
{
}


void DVDShot::update() {
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


void DVDShot::draw() {
	Position draw_pos = position->get_draw_position();
	unsigned int color_selector = collide_count % 11;
	switch (color_selector) {
	case 0:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_RED, TRUE);
		break;
	case 1:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_ORANGE, TRUE);
		break;
	case 2:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_YELLOW, TRUE);
		break;
	case 3:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_GREEN, TRUE);
		break;
	case 4:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_TEAL, TRUE);
		break;
	case 5:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_AQUA, TRUE);
		break;
	case 6:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_BLUE, TRUE);
		break;
	case 7:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_PURPLE, TRUE);
		break;
	case 8:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_FUCHSIA, TRUE);
		break;
	case 9:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_SILVER, TRUE);
		break;
	case 10:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_GRAY, TRUE);
		break;
	default:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, DRAW_ARG, ImageHandles::HEART_RED, TRUE);
		break;
	}
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();

}


void DVDShot::clone() {
	++collide_count;
	if (collide_count % 2 == 0) {
		even_clone();
	}
	else {
		odd_clone();
	}
}


void DVDShot::odd_clone() {
	double coy1_arg = arg + 1.0 / 36.0 * pi;
	double coy2_arg = arg - 1.0 / 36.0 * pi;
	double decoy_arg = arg;
	(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
		position->x,
		position->y,
		coy1_arg,
		COY_SHOT_SPEED,
		10,
		1,
		SkinID::TOROI_NM3_COY
	);
	(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
		position->x,
		position->y,
		coy2_arg,
		COY_SHOT_SPEED,
		10,
		1,
		SkinID::TOROI_NM3_COY
	);
	(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
		position->x,
		position->y,
		decoy_arg,
		DECOY_SHOT_SPEED,
		0,
		1,
		SkinID::TOROI_NM3_DECOY
	);
}


void DVDShot::even_clone() {
	double decoy1_arg = arg + 1.0 / 36.0 * pi;
	double decoy2_arg = arg - 1.0 / 36.0 * pi;
	double coy_arg = arg;
	(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
		position->x,
		position->y,
		decoy1_arg,
		DECOY_SHOT_SPEED,
		0,
		1,
		SkinID::TOROI_NM3_DECOY
	);
	(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
		position->x,
		position->y,
		decoy2_arg,
		DECOY_SHOT_SPEED,
		0,
		1,
		SkinID::TOROI_NM3_DECOY
	);
	(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
		position->x,
		position->y,
		coy_arg,
		COY_SHOT_SPEED,
		10,
		1,
		SkinID::TOROI_NM3_COY
	);
}