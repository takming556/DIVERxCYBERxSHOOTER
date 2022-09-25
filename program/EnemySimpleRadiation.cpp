#include <memory>
#include "class.h"

using std::make_unique;

//template class EnemySimpleRadiation<StraightShot>;	//テンプレートクラスの明示的実体化(詳しくは検索せよ)
//
//
//
//template <class T>
//EnemySimpleRadiation<T>::EnemySimpleRadiation(int emit_pos_x, int emit_pos_y, unsigned int emit_amount) :
//	SimpleRadiation(emit_pos_x, emit_pos_y, emit_amount)
//{
//}
//
//
//template <class T>
//void EnemySimpleRadiation<T>::perform() {
//	for (int i = 0; i < amount; i++) {
//		double arg = 2 * pi / amount * i;
//		Field::ENEMY_OFFENSIVES->push_back(make_unique<T>(x, y, arg, 150));
//	}
//}