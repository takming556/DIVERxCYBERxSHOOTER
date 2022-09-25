#include "class.h"

using std::unique_ptr;


template<class T>
SimpleRadiation<T>::SimpleRadiation(int emit_pos_x, int emit_pos_y, unsigned int emit_amount) :
	x(emit_pos_x),
	y(emit_pos_y),
	amount(emit_amount)
{
}


template<class T>
void SimpleRadiation<T>::perform() {
	for (int i = 0; i < amount; i++) {
		double arg = 2 * pi / amount * i;
		Field::ENEMY_OFFENSIVES->push_back(make_unique<T>(x, y, arg, 150));
	}
}