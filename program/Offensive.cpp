#include <memory>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;
using std::move;

template class Offensive<MyCharacter>;
template class Offensive<EnemyCharacter>;

template<class T>
Offensive<T>::Offensive(unsigned int init_durability, unique_ptr<CollideRealm> given_collidant) :
	durability(init_durability),
	collidant(move(given_collidant)),
	clock_keeper_for_update(DxLib::GetNowHiPerformanceCount())
{
}


template<>
bool Offensive<MyCharacter>::check_collision_with() {
	return collidant->is_collided_with(Field::MY_CHARACTER->collidant);
}


template<>	//テンプレートの完全特殊化
bool Offensive<EnemyCharacter>::check_collision_with() {
	bool collided_with_no_less_than_one_enemy_character_flag = false;
	for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
		if (collidant->is_collided_with(enemy_character->collidant)) collided_with_no_less_than_one_enemy_character_flag = true;
	}
	return collided_with_no_less_than_one_enemy_character_flag;
}