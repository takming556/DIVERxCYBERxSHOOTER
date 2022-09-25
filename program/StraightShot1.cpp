#include "DxLib.h"
#include "class.h"

template<class T>
StraightShot1<T>::StraightShot1(double init_x, double init_y, double init_arg, double init_speed) :
	StraightShot(init_x, init_y, init_arg, init_speed)
{
}


template<class T>
void StraightShot1<T>::draw() {
	Position draw_pos = center_pos->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, 0, ImageHandles::HEART, TRUE);
	collidant->draw();

}