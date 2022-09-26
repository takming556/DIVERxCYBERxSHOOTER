#include <memory>
#include <type_traits>
#include "class.h"

using std::unique_ptr;
using std::make_unique;
using std::is_same;


SimpleRadiation::SimpleRadiation(int emit_pos_x, int emit_pos_y, unsigned int emit_amount) :
	x(emit_pos_x),
	y(emit_pos_y),
	amount(emit_amount)
{
}


template<class O, class T>
void SimpleRadiation::perform<MyCharacter>() {
	for (int i = 0; i < amount; i++) {
		double arg = 2 * pi / amount * i;
		if constexpr (is_same_v<T, MyCharacter>) {
			Field::MY_OFFENSIVES->push_back(make_unique<Offensive>(x, y, arg, 150));
		}
		else if constexpr (is_same_v<T, EnemyCharacter>) {
			Field::ENEMY_OFFENSIVES->push_back(make_unique<Offensive>)
		}
	}
}