#include <memory>
#include <vector>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;
using std::vector;

unique_ptr<MyCharacter> Field::MY_CHARACTER;
unique_ptr<vector<unique_ptr<EnemyCharacter>>> Field::ENEMY_CHARACTERS;
unique_ptr<vector<unique_ptr<Offensive>>> Field::MY_OFFENSIVES;
unique_ptr<vector<unique_ptr<Offensive>>> Field::ENEMY_OFFENSIVES;
const double Field::FIELD_DRAW_EXTRATE = 1.0;



void Field::INITIALIZE() {
	MY_CHARACTER.reset(new IchigoChan());
	ENEMY_CHARACTERS.reset(new vector<unique_ptr<EnemyCharacter>>);
	MY_OFFENSIVES.reset(new vector<unique_ptr<Offensive>>);
	ENEMY_OFFENSIVES.reset(new vector<unique_ptr<Offensive>>);
	ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(200, 620, 0, 0.0));
	//ENEMY_CHARACTERS->push_back(make_unique<Mofu>());
}


void Field::UPDATE() {

	MY_CHARACTER->update();

	for (const auto& enemy_character : *ENEMY_CHARACTERS) {
		enemy_character->update();
	}

	for (const auto& my_offensive : *MY_OFFENSIVES) {
		my_offensive->update();
	}

	for (const auto& enemy_offensive : *ENEMY_OFFENSIVES) {
		enemy_offensive->update();
	}

	unsigned int objects = MY_OFFENSIVES->size() + ENEMY_OFFENSIVES->size() + ENEMY_CHARACTERS->size() + 1;
	DxLib::DrawFormatString(670, 0, Colors::YELLOW, "objects = %d", objects);

}


void Field::DRAW() {
	DxLib::DrawRotaGraph(FIELD_DRAW_POSITION_X, FIELD_DRAW_POSITION_Y, 1.0, 0, ImageHandles::FIELD_BACKGROUND, TRUE);

	MY_CHARACTER->draw();
	MY_CHARACTER->draw_life();

	for (const auto& enemy_character : *ENEMY_CHARACTERS) {
		enemy_character->draw();
		enemy_character->draw_HP();
	}

	for (const auto& my_offensive : *MY_OFFENSIVES) {
		my_offensive->draw();
		my_offensive->draw_durability();
	}

	for (const auto& enemy_offensive : *ENEMY_OFFENSIVES) {
		enemy_offensive->draw();
		enemy_offensive->draw_durability();
	}

}


void Field::DEAL_COLLISION() {

	if (MY_CHARACTER->is_collided_with_enemy_offensives() == true) MY_CHARACTER->damaged();

	vector<bool> enemy_characters_collided_flags;
	for (const auto& enemy_character : *ENEMY_CHARACTERS) {
		bool enemy_character_collided_flag = enemy_character->is_collided_with_my_offensives();
		enemy_characters_collided_flags.push_back(enemy_character_collided_flag);
	}

	vector<bool> my_offensives_collided_flags;
	for (const auto& my_offensive : *MY_OFFENSIVES) {
		bool is_my_offensive_collided = my_offensive->is_collided_with_enemy_characters();
		my_offensives_collided_flags.push_back(is_my_offensive_collided);
	}

	vector<bool> enemy_offensives_collided_flags;
	for (const auto& enemy_offensive : *ENEMY_OFFENSIVES) {
		bool enemy_offensive_collided_flag = enemy_offensive->is_collided_with_my_character();
		enemy_offensives_collided_flags.push_back(enemy_offensive_collided_flag);
	}


	for (int i = ENEMY_CHARACTERS->size() - 1; i >= 0; --i) {
		if (enemy_characters_collided_flags.at(i) == true) ENEMY_CHARACTERS->at(i)->damaged();
	}

	for (int i = MY_OFFENSIVES->size() - 1; i >= 0; --i) {
		if (my_offensives_collided_flags.at(i) == true) MY_OFFENSIVES->erase(MY_OFFENSIVES->begin() + i);
	}

	for (int i = ENEMY_OFFENSIVES->size() - 1; i >= 0; --i) {
		if (enemy_offensives_collided_flags.at(i) == true) ENEMY_OFFENSIVES->erase(ENEMY_OFFENSIVES->begin() + i);
	}
}