#include <memory>
#include <typeinfo>
#include "class.h"

using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::move;


SimpleRadiation::SimpleRadiation(double emit_pos_x, double emit_pos_y, unsigned int emit_amount) :
	x(emit_pos_x),
	y(emit_pos_y),
	amount(emit_amount)
{
}


//void SimpleRadiation::perform() {
//	for (int i = 0; i < amount; i++) {
//		double arg = 2 * pi / amount * i;
//
//		if (teamside_id == TeamsideID::MY) {
//			Field::MY_OFFENSIVES->push_back(make_unique<StraightShot>(x,y,arg,))
//		}
//		
//				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot1>(x, y, arg, 150));
//				Field::MY_OFFENSIVES->push_back(make_unique<StraightShot2>(x, y, arg, 150));
//				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot2>(x, y, arg, 150));
//	}
//}