#include "class.h"

BossCharacter::BossCharacter(double init_pos_x, double init_pos_y, int init_HP, string character_name) :
	EnemyCharacter(init_pos_x, init_pos_y, init_HP),
	name(character_name)
{
}