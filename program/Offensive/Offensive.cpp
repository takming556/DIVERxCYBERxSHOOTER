#include <memory>
#include "DxLib.h"
#include "class.h"
#include "enum.h"

using std::unique_ptr;
using std::make_unique;
using std::move;


Offensive::Offensive(unique_ptr<CollideRealm> given_collidant/*, enum TeamsideID given_teamside_id*/, unsigned int init_durability) :
	//teamside_id(given_teamside_id),
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