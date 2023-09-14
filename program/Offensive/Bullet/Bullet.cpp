#include <memory>
#include "DxLib.h"
#include "Offensive/Bullet/Bullet.h"
#include "Position/Position.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"

using std::make_unique;


Bullet::Bullet(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	int init_durability
):
	position(make_unique<InFieldPosition>(init_pos_x, init_pos_y)),
	arg(init_arg),
	speed(init_speed),
	durability(init_durability),
	last_frame_updated_clock(0),
	now_frame(0)
{
}


Bullet::Bullet() = default;


void Bullet::draw_durability() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::BLUE, L"%d", durability);
}


bool Bullet::is_broken() {
	return durability <= 0;
}

void Bullet::damaged() {
	durability += -1;
}