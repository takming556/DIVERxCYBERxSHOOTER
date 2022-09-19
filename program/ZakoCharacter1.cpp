#include <memory>
#include "class.h"

using std::make_unique;

ZakoCharacter1::ZakoCharacter1(int init_pos_x, int init_pos_y) :
	Character(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)),
	EnemyCharacter(INITIAL_HP)
{
}