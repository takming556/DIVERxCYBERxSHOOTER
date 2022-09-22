#include "DxLib.h"
#include "class.h"


EnemyCharacter::EnemyCharacter(unsigned int init_HP) :
	HP(init_HP)
{
}


void EnemyCharacter::damaged() {
	HP += -1;
}


void EnemyCharacter::draw_HP() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::BLUE, "%d", HP);
}