#include <memory>
#include "DxLib.h"
#include "class.h"
#include "extern.h"

using std::make_unique;

const double Field::FIELD_DRAW_EXTRATE = 1.0;

Field::Field() :
	my_character(make_unique<MyCharacter1>())
{
	enemy_characters.push_back(make_unique<BossCharacter1>());
}


void Field::update(char key_buffer[]) {

	my_character->update(key_buffer, my_offensives);

	for (const auto& enemy_character : enemy_characters) {
		enemy_character->update(enemy_offensives);
	}

	for (const auto& my_offensive : my_offensives) {
		my_offensive->update();
	}

	for (const auto& enemy_offensive : enemy_offensives) {
		enemy_offensive->update();
	}

}


void Field::draw() {
	DrawRotaGraph(FIELD_DRAW_POSITION_X, FIELD_DRAW_POSITION_Y, 1.0, 0, hFieldBackground, TRUE);

	my_character->draw();

	for (const auto& enemy_character : enemy_characters) {
		enemy_character->draw();
	}

	for (const auto& my_offensive : my_offensives) {
		my_offensive->draw();
	}

	for (const auto& enemy_offensive : enemy_offensives) {
		enemy_offensive->draw();
	}

}