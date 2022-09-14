#include "DxLib.h"
#include "class.h"
#include "extern.h"

StraightShot::StraightShot(double init_x, double init_y, double init_speed) :
	Bullet(init_x, init_y),
	speed(init_speed)
{
}


void StraightShot::update() {
	LONGLONG delta_time = DxLib::GetNowHiPerformanceCount() - clock_keeper_for_update;
	double distance = speed * delta_time / 1000 / 1000;
	center_pos->y += distance;
	clock_keeper_for_update = DxLib::GetNowHiPerformanceCount();
}


void StraightShot::draw() {
	Position draw_pos = center_pos->get_draw_position();
	DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, 0, hHeart, TRUE);

}