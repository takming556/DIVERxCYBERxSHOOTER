#include <memory>
#include "DxLib.h"
#include "Offensive/Bullet/Bullet.h"
#include "Position/Position.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"

using std::make_unique;


Bullet::Bullet(double init_arg, double init_speed) :
	arg(init_arg),
	speed(init_speed)
{
}


void Bullet::draw_durability() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::BLUE, "%d", durability);
}
