#include "DxLib.h"
#include "Position/Position.h"
#include "Position/InFieldPosition.h"
#include "CollideRealm/CollideRealm.h"
#include "Field.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "Offensive/Offensive.h"
#include "SoundHandles.h"
#include "Colors.h"


EnemyCharacter::EnemyCharacter(unsigned int init_hp) :
	hp(init_hp)
{
}


void EnemyCharacter::damaged() {
	hp -= 1;
	DxLib::PlaySoundMem(SoundHandles::ENEMYHIT, DX_PLAYTYPE_BACK);
}


void EnemyCharacter::draw_HP() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::BLUE, "%d", hp);
}


bool EnemyCharacter::is_collided_with_my_offensives() {
	bool collided_with_no_less_than_one_my_offensive_flag = false;
	for (const auto& my_offensive : *Field::MY_OFFENSIVES) {
		if (collidant->is_collided_with(my_offensive->collidant)) collided_with_no_less_than_one_my_offensive_flag = true;
	}
	return collided_with_no_less_than_one_my_offensive_flag;
}


bool EnemyCharacter::is_dead() {
	return hp < 1;
}