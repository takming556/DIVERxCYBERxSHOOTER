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
const int Field::DRAW_POSITION_X = 350;				//フィールドの描画位置中心X座標(ピクセル)
const int Field::DRAW_POSITION_Y = 384;				//フィールドの描画位置中心Y座標(ピクセル)
const int Field::PIXEL_SIZE_X = 620;				//フィールドの幅(ピクセル)
const int Field::PIXEL_SIZE_Y = 742;				//フィールドの高さ(ピクセル)
const double Field::DRAW_EXTRATE = 1.0;				//フィールドの描画倍率
const double Field::BACKGROUND_DRAW_EXTRATE = 1.0;	//フィールド背景画の描画倍率



void Field::INITIALIZE() {
	MY_CHARACTER.reset(new IchigoChan());
	ENEMY_CHARACTERS.reset(new vector<unique_ptr<EnemyCharacter>>);
	MY_OFFENSIVES.reset(new vector<unique_ptr<Offensive>>);
	ENEMY_OFFENSIVES.reset(new vector<unique_ptr<Offensive>>);
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

	DebugParams::OBJECTS = MY_OFFENSIVES->size() + ENEMY_OFFENSIVES->size() + ENEMY_CHARACTERS->size() + 1;
}


void Field::DRAW() {
	DxLib::DrawRotaGraph(DRAW_POSITION_X, DRAW_POSITION_Y, BACKGROUND_DRAW_EXTRATE, 0, ImageHandles::FIELD_BACKGROUND, TRUE);

	MY_CHARACTER->draw();
	if (DebugParams::DEBUG_FLAG == true) MY_CHARACTER->draw_life();

	for (const auto& enemy_character : *ENEMY_CHARACTERS) {
		enemy_character->draw();
		if (DebugParams::DEBUG_FLAG == true) enemy_character->draw_HP();
	}

	for (const auto& my_offensive : *MY_OFFENSIVES) {
		my_offensive->draw();
		if (DebugParams::DEBUG_FLAG == true) my_offensive->draw_durability();
	}

	for (const auto& enemy_offensive : *ENEMY_OFFENSIVES) {
		enemy_offensive->draw();
		if (DebugParams::DEBUG_FLAG == true) enemy_offensive->draw_durability();
	}

	if (DebugParams::DEBUG_FLAG == true) {
		InFieldPosition::DRAW_VISIBLE_BOUNDARY();
		InFieldPosition::DRAW_EXISTENCE_BOUNDARY();
	}
}


void Field::DEAL_COLLISION() {

	if (MY_CHARACTER->is_collided_with_enemy_offensives() == true) MY_CHARACTER->damaged();

	//vector<bool> enemy_characters_collided_flags;
	//for (const auto& enemy_character : *ENEMY_CHARACTERS) {
	//	bool enemy_character_collided_flag = enemy_character->is_collided_with_my_offensives();
	//	enemy_characters_collided_flags.push_back(enemy_character_collided_flag);
	//}

	//vector<bool> my_offensives_collided_flags;
	//for (const auto& my_offensive : *MY_OFFENSIVES) {
	//	bool my_offensive_collided_flag = my_offensive->is_collided_with_enemy_characters();
	//	my_offensives_collided_flags.push_back(my_offensive_collided_flag);
	//}

	//vector<bool> enemy_offensives_collided_flags;
	//for (const auto& enemy_offensive : *ENEMY_OFFENSIVES) {
	//	bool enemy_offensive_collided_flag = enemy_offensive->is_collided_with_my_character();
	//	enemy_offensives_collided_flags.push_back(enemy_offensive_collided_flag);
	//}


	//for (int i = ENEMY_CHARACTERS->size() - 1; i >= 0; --i) {
	//	if (enemy_characters_collided_flags.at(i) == true) ENEMY_CHARACTERS->at(i)->damaged();
	//}

	//for (int i = MY_OFFENSIVES->size() - 1; i >= 0; --i) {
	//	if (my_offensives_collided_flags.at(i) == true) MY_OFFENSIVES->erase(MY_OFFENSIVES->begin() + i);
	//}

	//for (int i = ENEMY_OFFENSIVES->size() - 1; i >= 0; --i) {
	//	if (enemy_offensives_collided_flags.at(i) == true) ENEMY_OFFENSIVES->erase(ENEMY_OFFENSIVES->begin() + i);
	//}


	for (const auto& enemy_character : *ENEMY_CHARACTERS) {
		if (enemy_character->is_collided_with_my_offensives() == true) enemy_character->damaged();
	}
	for (const auto& my_offensive : *MY_OFFENSIVES) {
		if (my_offensive->is_collided_with_enemy_characters() == true) my_offensive->damaged();
	}
	for (const auto& enemy_offensive : *ENEMY_OFFENSIVES) {
		if (enemy_offensive->is_collided_with_my_character() == true) enemy_offensive->damaged();
	}
}


void Field::ERASE_BROKEN_OFFENSIVES() {
	for (int i = MY_OFFENSIVES->size() - 1; i >= 0; --i) {
		if (MY_OFFENSIVES->at(i)->is_broken() == true) MY_OFFENSIVES->erase(MY_OFFENSIVES->begin() + i);
	}
	for (int i = ENEMY_OFFENSIVES->size() - 1; i >= 0; --i) {
		if (ENEMY_OFFENSIVES->at(i)->is_broken() == true) ENEMY_OFFENSIVES->erase(ENEMY_OFFENSIVES->begin() + i);
	}
}


void Field::ERASE_DEAD_CHARACTERS() {
	for (int i = ENEMY_CHARACTERS->size() - 1; i >= 0; --i) {
		if (ENEMY_CHARACTERS->at(i)->is_dead() == true) ENEMY_CHARACTERS->erase(ENEMY_CHARACTERS->begin() + i);
	}
}