#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Offensive/Bullet/CurvingShot.h"
#include "ImageHandles.h"
#include "DebugParams.h"

using std::numbers::pi;

CurvingShot::CurvingShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	double curve_speed,
	unsigned int collidant_size,
	unsigned int durability,
	SkinID given_skin_id
) :
	Offensive(given_skin_id),
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability, collidant_size),
	curve_speed(curve_speed)
{
}


void CurvingShot::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	arg += update_delta_time * curve_speed / 1000 / 1000;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;

	collidant->update(position);

	last_updated_clock = DxLib::GetNowHiPerformanceCount();
}


void CurvingShot::draw() {
	int delta_time_frame_update = DxLib::GetNowCount() - last_frame_updated_clock;
	Position draw_pos = position->get_draw_position();

	switch (skin_id) {
	//case SkinID::ICHIGO_CHAN:
	//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, -arg, ImageHandles::HEART, TRUE);
	//	break;

	//case SkinID::NORMAL_BLUE:
	//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BLUE_MARBLE, TRUE);
	//	break;

	case SkinID::BUBBLE_GENERIC:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_AQUA, TRUE);
		break;

	case SkinID::NEON_SP2_GHOST:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.50, 1.0 / 2.0 * pi, ImageHandles::GHOST_AQUA.at(now_frame), TRUE);
		if (delta_time_frame_update > 200) {
			if (now_frame >= ImageHandles::GHOST_AQUA.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}
		break;
	case SkinID::TOROI_NM4_RED_BIG:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, 1.0 / 2.0 * pi, ImageHandles::GHOST_RED.at(now_frame), TRUE);
		if (delta_time_frame_update > 200) {
			if (now_frame >= ImageHandles::GHOST_RED.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}
		break;
	case SkinID::TOROI_NM4_BLUE_BIG:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, 1.0 / 2.0 * pi, ImageHandles::GHOST_BLUE.at(now_frame), TRUE);
		if (delta_time_frame_update > 200) {
			if (now_frame >= ImageHandles::GHOST_BLUE.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}
		break;
	case SkinID::TOROI_SP1_TRICK:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::CRYSTAL_RED, TRUE);
		break;

	case SkinID::TOROI_SP2_SURROUNDED:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::HEART_SILVER, TRUE);
		break;

	//case SkinID::KUNAI_RED:
	//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::ORANGE_TRIANGLE, TRUE);
	//	break;
	}

	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}


void CurvingShot::set_curve_speed(double given_curve_speed) {
	curve_speed = given_curve_speed;
}