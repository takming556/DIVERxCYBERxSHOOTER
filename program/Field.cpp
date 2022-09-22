#include <memory>
#include <vector>
#include "DxLib.h"
#include "class.h"
#include "extern.h"

using std::make_unique;
using std::vector;

const double Field::FIELD_DRAW_EXTRATE = 1.0;

Field::Field() :
	my_character(make_unique<MyCharacter1>()),
	enemy_characters(make_unique<vector<unique_ptr<EnemyCharacter>>>()),
	my_offensives(make_unique<vector<unique_ptr<Offensive>>>()),
	enemy_offensives(make_unique<vector<unique_ptr<Offensive>>>())
{
	enemy_characters->push_back(make_unique<BossCharacter1>());
}


void Field::update(char key_buffer[]) {

	my_character->update(key_buffer, my_offensives);

	for (const auto& enemy_character : *enemy_characters) {
		enemy_character->update(enemy_offensives);
	}

	for (const auto& my_offensive : *my_offensives) {
		my_offensive->update();
	}

	for (const auto& enemy_offensive : *enemy_offensives) {
		enemy_offensive->update();
	}

	unsigned int objects = my_offensives->size() + enemy_offensives->size() + enemy_characters->size() + 1;
	DxLib::DrawFormatString(670, 0, Colors::YELLOW, "objects = %d", objects);

}


void Field::draw() {
	DxLib::DrawRotaGraph(FIELD_DRAW_POSITION_X, FIELD_DRAW_POSITION_Y, 1.0, 0, ImageHandles::FIELD_BACKGROUND, TRUE);

	my_character->draw();
	my_character->draw_life();

	for (const auto& enemy_character : *enemy_characters) {
		enemy_character->draw();
		enemy_character->draw_HP();
	}

	for (const auto& my_offensive : *my_offensives) {
		my_offensive->draw();
		my_offensive->draw_durability();
	}

	for (const auto& enemy_offensive : *enemy_offensives) {
		enemy_offensive->draw();
		enemy_offensive->draw_durability();
	}

}


void Field::deal_collision() {

	if (my_character->check_collision_with(enemy_offensives) == true) my_character->damaged();

	vector<bool> are_enemy_characters_collided;
	for (const auto& enemy_character : *enemy_characters) {
		bool is_enemy_character_collided = enemy_character->check_collision_with(my_offensives);
		are_enemy_characters_collided.push_back(is_enemy_character_collided);
	}

	vector<bool> are_my_offensives_collided;
	for (const auto& my_offensive : *my_offensives) {
		bool is_my_offensive_collided = my_offensive->check_collision_with(enemy_characters);
		are_my_offensives_collided.push_back(is_my_offensive_collided);
	}

	vector<bool> are_enemy_offensives_collided;
	for (const auto& enemy_offensive : *enemy_offensives) {
		bool is_enemy_offensive_collided = enemy_offensive->check_collision_with(my_character);
		are_enemy_offensives_collided.push_back(is_enemy_offensive_collided);
	}


	for (int i = enemy_characters->size() - 1; i >= 0; --i) {
		if (are_enemy_characters_collided.at(i) == true) enemy_characters->at(i)->damaged();
	}

	for (int i = my_offensives->size() - 1; i >= 0; --i) {
		if (are_my_offensives_collided.at(i) == true) my_offensives->erase(my_offensives->begin() + i);
	}

	for (int i = enemy_offensives->size() - 1; i >= 0; --i) {
		if (are_enemy_offensives_collided.at(i) == true) enemy_offensives->erase(enemy_offensives->begin() + i);
	}
}