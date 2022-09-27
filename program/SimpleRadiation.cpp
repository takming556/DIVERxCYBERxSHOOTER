#include <memory>
#include <type_traits>
#include "class.h"

using std::unique_ptr;
using std::make_unique;
using std::is_same;

//template class SimpleRadiation<StraightShot1>;
//template class SimpleRadiation<StraightShot2>;
//
//template void SimpleRadiation<StraightShot1>::perform<MyCharacter>();
//template void SimpleRadiation<StraightShot1>::perform<EnemyCharacter>();
//template void SimpleRadiation<StraightShot2>::perform<MyCharacter>();
//template void SimpleRadiation<StraightShot2>::perform<EnemyCharacter>();

template<class O>
SimpleRadiation<O>::SimpleRadiation(int emit_pos_x, int emit_pos_y, unsigned int emit_amount) :
	x(emit_pos_x),
	y(emit_pos_y),
	amount(emit_amount)
{
}

//template<class O>
//template<class T>
//void SimpleRadiation<O>::perform<T>() {
//	for (int i = 0; i < amount; i++) {
//		double arg = 2 * pi / amount * i;
//		if constexpr (is_same_v <O, StraightShot1>) {
//			if constexpr (is_same_v<T, MyCharacter>) {
//				Field::MY_OFFENSIVES->push_back(make_unique<StraightShot1>(x, y, arg, 150));
//			}
//			else if constexpr (is_same_v<T, EnemyCharacter>) {
//				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot1>(x, y, arg, 150));
//			}
//		}
//		else if constexpr (is_same_v <O, StraightShot2>) {
//			if constexpr (is_same_v<T, MyCharacter>) {
//				Field::MY_OFFENSIVES->push_back(make_unique<StraightShot2>(x, y, arg, 150));
//			}
//			else if constexpr (is_same_v<T, EnemyCharacter>) {
//				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot2>(x, y, arg, 150));
//			}
//		}
//
//	}
//}