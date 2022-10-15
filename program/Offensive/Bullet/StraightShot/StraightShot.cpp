#include <memory>
#include <cmath>
#include "DxLib.h"
#include "class.h"
#include "enum.h"

using std::make_unique;
using std::sin;
using std::cos;


StraightShot::StraightShot(
	double init_x,
	double init_y,
	double init_arg,
	double init_speed,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID given_skin_id
) :
	Bullet(init_x, init_y, init_arg, init_speed),
	Offensive(make_unique<CollideCircle>(init_x, init_y, collidant_size), durability),
	skin_id(given_skin_id)
{
}


void StraightShot::update() {

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	center_pos->x += distance_x;
	center_pos->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(center_pos);
}


void StraightShot::draw() {
	Position draw_pos = center_pos->get_draw_position();

	if (skin_id == SkinID::ICHIGO_CHAN) {
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, 0, ImageHandles::HEART, TRUE);
	}
	else if (skin_id == SkinID::NORMAL_BLUE) {
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, 0, ImageHandles::BLUE_MARBLE, TRUE);
	}

	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}