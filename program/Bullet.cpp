#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


template<class T>
Bullet<T>::Bullet(double init_x, double init_y) :
	center_pos(make_unique<InFieldPosition>(init_x, init_y))
{
}


template<class T>
void Bullet<T>::draw_durability() {
	Position draw_pos = center_pos->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::BLUE, "%d", durability);
}
