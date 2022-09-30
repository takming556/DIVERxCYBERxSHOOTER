#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


Bullet::Bullet(double init_x, double init_y, double init_arg, double init_speed) :
	center_pos(make_unique<InFieldPosition>(init_x, init_y)),
	arg(init_arg),
	speed(init_speed)
{
}


void Bullet::draw_durability() {
	Position draw_pos = center_pos->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::BLUE, "%d", durability);
}