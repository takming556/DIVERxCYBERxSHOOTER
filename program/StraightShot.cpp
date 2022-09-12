#include "DxLib.h"
#include "class.h"
#include "extern.h"

StraightShot::StraightShot(double init_x, double init_y) :
	Bullet(init_x, init_y)
{
}


void StraightShot::update() {
	center_pos->y += -20;
}


void StraightShot::draw() {
	Position draw_pos = center_pos->get_draw_position();
	DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, 0, hHeart, TRUE);

}