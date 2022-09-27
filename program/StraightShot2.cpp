#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


StraightShot2::StraightShot2(double init_x, double init_y, double init_arg, double init_speed) :
	Offensive(make_unique<CollideCircle>(init_x, init_y, COLLIDANT_SIZE), DURABILITY),
	Bullet(init_x, init_y, init_arg, init_speed)
{
}


void StraightShot2::draw() {
	Position draw_pos = center_pos->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, 0, ImageHandles::BLUE_MARBLE, TRUE);
	collidant->draw();
}