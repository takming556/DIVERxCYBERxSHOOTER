#include "class.h"


EnemyCharacter::EnemyCharacter(unsigned int init_HP) :
	HP(init_HP)
{
}


void EnemyCharacter::damaged() {
	HP += -1;
}