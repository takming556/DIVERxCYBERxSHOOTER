#include <memory>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;
using std::move;

Offensive::Offensive(unsigned int init_durability, unique_ptr<CollideRealm> given_collidant) :
	durability(init_durability),
	collidant(move(given_collidant)),
	clock_keeper_for_update(DxLib::GetNowHiPerformanceCount())
{
}


bool Offensive::check_collision_with(unique_ptr<vector<unique_ptr<EnemyCharacter>>>& given_enemy_characters) {
	bool is_collided_with_no_less_than_one_enemy_character = false;
	for (const auto& given_enemy_character : *given_enemy_characters) {
		if (collidant->is_collided_with(given_enemy_character->collidant)) is_collided_with_no_less_than_one_enemy_character = true;
	}
	return is_collided_with_no_less_than_one_enemy_character;
}


bool Offensive::check_collision_with(unique_ptr<MyCharacter>& given_my_character) {
	return collidant->is_collided_with(given_my_character->collidant);
}