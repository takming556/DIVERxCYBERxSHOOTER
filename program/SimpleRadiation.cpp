#include "class.h"

using std::unique_ptr;


template<class C, class O>
SimpleRadiation<C, O>::SimpleRadiation(int emit_pos_x, int emit_pos_y, unsigned int emit_amount) :
	x(emit_pos_x),
	y(emit_pos_y),
	amount(emit_amount)
{
}


template<class MyCharacter, class O>
void SimpleRadiation<MyCharacter, O>::perform() {
	for (int i = 0; i < amount; i++) {
		double arg = 2 * pi / amount * i;
		Field::MY_OFFENSIVES->push_back(make_unique<O>(x, y, arg, 150));
	}
}