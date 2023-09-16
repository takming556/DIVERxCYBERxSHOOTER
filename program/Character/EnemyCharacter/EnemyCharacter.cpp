#include "DxLib.h"
#include "Position/Position.h"
#include "Position/InFieldPosition.h"
#include "CollideRealm/CollideRealm.h"
#include "Field.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "Offensive/Offensive.h"
#include "SoundHandles.h"
#include "Colors.h"


unsigned int EnemyCharacter::DPS = 15;	// Damage Per Second

EnemyCharacter::EnemyCharacter()
{
}


void EnemyCharacter::damaged() {
	hp += -1;
	DxLib::PlaySoundMem(SoundHandles::ENEMYHIT, DX_PLAYTYPE_BACK);
}


bool EnemyCharacter::is_collided_with_my_offensives() {
	bool collided_with_no_less_than_one_my_offensive_flag = false;
	for (const auto& my_offensive : *Field::MY_BULLETS) {
		if (collidant->is_collided_with(my_offensive.second->collidant)) collided_with_no_less_than_one_my_offensive_flag = true;
	}
	return collided_with_no_less_than_one_my_offensive_flag;
}


void EnemyCharacter::deal_collision() {
	for (const auto& my_bullet : *Field::MY_BULLETS) {
		if (is_last_collided_with(my_bullet.first) == false							// 前回はそいつと衝突していなかったが、
			&& collidant->is_collided_with(my_bullet.second->collidant) == true)	// 現在は衝突している
		{
			damaged();
		}
	}

	last_collided_my_bullet_ids.clear();

	for (const auto& my_bullet : *Field::MY_BULLETS) {
		if (collidant->is_collided_with(my_bullet.second->collidant)) {
			last_collided_my_bullet_ids.push_back(my_bullet.first);
		}
	}
}


bool EnemyCharacter::is_last_collided_with(unsigned int given_my_bullet_id) {
	bool found = false;
	for (const auto& last_collided_my_bullet_id : last_collided_my_bullet_ids) {
		if (last_collided_my_bullet_id == given_my_bullet_id) found = true;
	}
	return found;
}