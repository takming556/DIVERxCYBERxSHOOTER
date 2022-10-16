#include <memory>
#include "DxLib.h"
#include "class.h"
#include "enum.h"

using std::unique_ptr;
using std::make_unique;
using std::move;


Offensive::Offensive(double init_pos_x, double init_pos_y, unique_ptr<CollideRealm> given_collidant, unsigned int init_durability) :
	position(make_unique<InFieldPosition>(init_pos_x, init_pos_y)),
	durability(init_durability),
	collidant(move(given_collidant)),
	last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
}


bool Offensive::is_collided_with_my_character() {
	return collidant->is_collided_with(Field::MY_CHARACTER->collidant);
}


bool Offensive::is_collided_with_enemy_characters() {
	bool collided_with_no_less_than_one_enemy_character_flag = false;
	for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
		if (collidant->is_collided_with(enemy_character->collidant)) collided_with_no_less_than_one_enemy_character_flag = true;
	}
	return collided_with_no_less_than_one_enemy_character_flag;
}


bool Offensive::is_broken() {
	return durability < 1;
}


void Offensive::damaged() {
	durability += -1;
}