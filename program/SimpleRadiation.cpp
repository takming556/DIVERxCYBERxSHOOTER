#include "class.h"

using std::unique_ptr;


SimpleRadiation::SimpleRadiation(int emit_pos_x, int emit_pos_y, unsigned int emit_amount) :
	x(emit_pos_x),
	y(emit_pos_y),
	amount(emit_amount)
{
}