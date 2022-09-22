#include <memory>
#include <vector>
#include "DxLib.h"
#include "class.h"
//#include "extern.h"

using std::unique_ptr;
using std::make_unique;
using std::vector;

unique_ptr<MyCharacter> Field::MY_CHARACTER;
unique_ptr<vector<unique_ptr<EnemyCharacter>>> Field::ENEMY_CHARACTERS;
unique_ptr<vector<unique_ptr<Offensive>>> Field::MY_OFFENSIVES;
unique_ptr<vector<unique_ptr<Offensive>>> Field::ENEMY_OFFENSIVES;
const double Field::FIELD_DRAW_EXTRATE = 1.0;

void Field::INITIALIZE() {
	MY_CHARACTER.reset(new MyCharacter1());
	ENEMY_CHARACTERS.reset(new vector<unique_ptr<EnemyCharacter>>);
	MY_OFFENSIVES.reset(new vector<unique_ptr<Offensive>>);
	ENEMY_OFFENSIVES.reset(new vector<unique_ptr<Offensive>>);
	ENEMY_CHARACTERS->push_back(make_unique<BossCharacter1>());
}

//Field::Field() :
//	MY_CHARACTER(make_unique<MyCharacter1>()),
//	enemy_characters(make_unique<vector<unique_ptr<EnemyCharacter>>>()),
//	my_offensives(make_unique<vector<unique_ptr<Offensive>>>()),
//	enemy_offensives(make_unique<vector<unique_ptr<Offensive>>>())
//{
//	enemy_characters->push_back(make_unique<BossCharacter1>());
//}


void Field::UPDATE(char key_buffer[]) {

	MY_CHARACTER->update(key_buffer, MY_OFFENSIVES);

	for (const auto& enemy_character : *ENEMY_CHARACTERS) {
		enemy_character->update(ENEMY_OFFENSIVES);
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

	if (MY_CHARACTER->check_collision_with(ENEMY_OFFENSIVES) == true) MY_CHARACTER->damaged();

	vector<bool> are_enemy_characters_collided;
	for (const auto& enemy_character : *ENEMY_CHARACTERS) {
		bool is_enemy_character_collided = enemy_character->check_collision_with(MY_OFFENSIVES);
		are_enemy_characters_collided.push_back(is_enemy_character_collided);
	}

	vector<bool> are_my_offensives_collided;
	for (const auto& my_offensive : *MY_OFFENSIVES) {
		bool is_my_offensive_collided = my_offensive->check_collision_with(ENEMY_CHARACTERS);
		are_my_offensives_collided.push_back(is_my_offensive_collided);
	}

	vector<bool> are_enemy_offensives_collided;
	for (const auto& enemy_offensive : *ENEMY_OFFENSIVES) {
		bool is_enemy_offensive_collided = enemy_offensive->check_collision_with(MY_CHARACTER);
		are_enemy_offensives_collided.push_back(is_enemy_offensive_collided);
	}


	for (int i = ENEMY_CHARACTERS->size() - 1; i >= 0; --i) {
		if (are_enemy_characters_collided.at(i) == true) ENEMY_CHARACTERS->at(i)->damaged();
	}

	for (int i = MY_OFFENSIVES->size() - 1; i >= 0; --i) {
		if (are_my_offensives_collided.at(i) == true) MY_OFFENSIVES->erase(MY_OFFENSIVES->begin() + i);
	}

	for (int i = ENEMY_OFFENSIVES->size() - 1; i >= 0; --i) {
		if (are_enemy_offensives_collided.at(i) == true) ENEMY_OFFENSIVES->erase(ENEMY_OFFENSIVES->begin() + i);
	}
}