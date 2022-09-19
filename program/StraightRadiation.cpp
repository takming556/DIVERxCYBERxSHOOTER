#include <memory>
#include <list>
#include "class.h"

using std::unique_ptr;
using std::make_unique;
using std::list;


StraightRadiation::StraightRadiation(int emit_pos_x, int emit_pos_y, unsigned int emit_amount) :
	x(emit_pos_x),
	y(emit_pos_y),
	amount(emit_amount)
{
}


void StraightRadiation::perform(list<unique_ptr<Offensive>>& given_offensives) {
	for (int i = 0; i < amount; i++) {
		double arg = 2 * pi / amount * i;
		given_offensives.push_back(make_unique<StraightShot>(x, y, arg, 150));
	}
}