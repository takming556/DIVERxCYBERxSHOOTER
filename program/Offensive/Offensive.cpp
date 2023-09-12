#include <memory>
#include <vector>
#include "DxLib.h"
#include "enum.h"
#include "Offensive/Offensive.h"
#include "CollideRealm/CollideRealm.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"


using std::unique_ptr;
using std::vector;



Offensive::Offensive(vector<unique_ptr<CollideRealm>> given_collidants) :
	collidants(given_collidants),
	last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
}


Offensive::~Offensive() = default;


bool Offensive::is_collided_with_my_character() {
	bool totally_collided_flag = false;
	for (const auto& collidant : collidants) {
		if (collidant->is_collided_with(Field::MY_CHARACTER->collidant)) {
			totally_collided_flag = true;
		}
	}
	return totally_collided_flag;
}


bool Offensive::is_collided_with_enemy_characters() {
	bool collided_with_no_less_than_one_enemy_character_flag = false;
	for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
		if (collidant->is_collided_with(enemy_character->collidant)) collided_with_no_less_than_one_enemy_character_flag = true;
	}
	for (const auto& identifiable_enemy_character_map : *Field::IDENTIFIABLE_ENEMY_CHARACTERS) {
		auto& identifiable_enemy_character = identifiable_enemy_character_map.second;
		if (collidant->is_collided_with(identifiable_enemy_character->collidant)) collided_with_no_less_than_one_enemy_character_flag = true;
	}

	return collided_with_no_less_than_one_enemy_character_flag;
}


bool Offensive::is_broken() {
	return durability < 1;
}


void Offensive::damaged() {
	durability += -1;
}