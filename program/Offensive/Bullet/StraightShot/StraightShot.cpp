#include <memory>
#include <cmath>
#include "DxLib.h"
#include "class.h"
#include "enum.h"

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
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, -arg, ImageHandles::HEART, TRUE);
		break;

	case SkinID::NORMAL_BLUE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BLUE_MARBLE, TRUE);
		break;

	case SkinID::KUNAI_RED:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::ORANGE_TRIANGLE, TRUE);
		break;
	}

	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}