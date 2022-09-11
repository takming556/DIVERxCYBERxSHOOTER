#include <memory>
#include "class.h"

using std::make_unique;

Character::Character(int init_pos_x, int init_pos_y) :
	position(make_unique<InFieldPosition>((double)init_pos_x, (double)init_pos_y))
{
}