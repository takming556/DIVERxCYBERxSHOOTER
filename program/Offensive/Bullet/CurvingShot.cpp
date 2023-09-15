#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/CurvingShot.h"
#include "ImageHandles.h"
#include "DebugParams.h"

using std::make_unique;

CurvingShot::CurvingShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	double curve_speed,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID skin_id
) :
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability),
	Offensive(make_unique<CollideCircle>(init_pos_x, init_pos_y, collidant_size)),
	curve_speed(curve_speed),
	skin_id(skin_id)
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
	case SkinID::ICHIGO_CHAN:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, -arg, ImageHandles::HEART, TRUE);
		break;

	case SkinID::NORMAL_BLUE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BLUE_MARBLE, TRUE);
		break;

	case SkinID::BUBBLE_GENERIC:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_AQUA, TRUE);
		break;

	case SkinID::NEON_SP2_HAIL:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::CRYSTAL_AQUA, TRUE);
		break;

	case SkinID::TOROI_SP1_TRICK:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::CRYSTAL_RED, TRUE);
		break;

	//case SkinID::KUNAI_RED:
	//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::ORANGE_TRIANGLE, TRUE);
	//	break;
	}

	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}