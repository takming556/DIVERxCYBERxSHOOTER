#include <memory>
#include <vector>
#include <utility>
#include "DxLib.h"
#include "enum.h"
#include "Offensive/Offensive.h"
#include "CollideRealm/CollideRealm.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"


using std::unique_ptr;
using std::vector;
using std::move;


unsigned int Offensive::NEXT_ID;


void Offensive::INITIALIZE() {
	NEXT_ID = 0;
}


Offensive::Offensive(unique_ptr<CollideRealm> given_collidant) :
	collidant(move(given_collidant)),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_frame_updated_clock(0)
{
}


Offensive::Offensive() = default;


Offensive::~Offensive() = default;


unsigned int Offensive::GENERATE_ID() {
	unsigned int generated_id = NEXT_ID;
	++NEXT_ID;
	return generated_id;
}


//bool Offensive::is_collided_with_my_character() {
//	bool totally_collided_flag = false;
//	for (const auto& collidant : collidants) {
//		if (collidant->is_collided_with(Field::MY_CHARACTER->collidant)) {
//			totally_collided_flag = true;
//		}
//	}
//	return totally_collided_flag;
//}


bool Offensive::is_collided_with_my_character() {
	return collidant->is_collided_with(Field::MY_CHARACTER->collidant);
}


bool Offensive::is_collided_with_enemy_characters() {
	bool collided_with_no_less_than_one_enemy_character_flag = false;
	for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
		if (collidant->is_collided_with(enemy_character->collidant)) collided_with_no_less_than_one_enemy_character_flag = true;
	}
	//for (const auto& identifiable_enemy_character_map : *Field::IDENTIFIABLE_ENEMY_CHARACTERS) {
	//	auto& identifiable_enemy_character = identifiable_enemy_character_map.second;
	//	if (collidant->is_collided_with(identifiable_enemy_character->collidant)) collided_with_no_less_than_one_enemy_character_flag = true;
	//}

	return collided_with_no_less_than_one_enemy_character_flag;
}