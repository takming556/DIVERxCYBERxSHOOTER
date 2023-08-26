#include <memory>
#include <cmath>
#include "DxLib.h"
#include "enum.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::sin;
using std::cos;


StraightShot::StraightShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID given_skin_id
) :
	Bullet(init_arg, init_speed),
	Offensive(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, collidant_size), durability),
	skin_id(given_skin_id)
{
}


StraightShot::StraightShot(enum SkinID given_skin_id) :
	skin_id(given_skin_id)
{
}


void StraightShot::update() {

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}


void StraightShot::draw() {
	Position draw_pos = position->get_draw_position();

	switch (skin_id) {
	case SkinID::ICHIGO_CHAN:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::STRAWBERRY_RED, TRUE);
		break;

	case SkinID::NORMAL_BLUE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BLUE_MARBLE, TRUE);
		break;

	case SkinID::TERROR:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::ANCHOR_RED, TRUE);
		break;
	case SkinID::BUBBLE_GENERIC:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_AQUA, TRUE);
		break;

	case SkinID::TOROI_SP5_RAIN_SOU:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::POTATO_FUCHSIA, TRUE);
		break;

	case SkinID::TOROI_SP5_RAIN_UTU:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::POTATO_AQUA, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_RED:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_RED, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_ORANGE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_ORANGE, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_YELLOW:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_YELLOW, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_GREEN:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_GREEN, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_TEAL:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_TEAL, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_AQUA:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_AQUA, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_BLUE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_BLUE, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_PURPLE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_PURPLE, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_FUCHSIA:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_FUCHSIA, TRUE);
		break;



	}

	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}