#include <memory>
#include <vector>
#include <map>
#include "DxLib.h"
#include "GameConductor.h"
#include "Field.h"
#include "Offensive/Offensive.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "Character/MyCharacter/Ichigochan.h"
#include "Position/InFieldPosition.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"


using std::unique_ptr;
using std::make_unique;
using std::vector;
using std::map;


unique_ptr<MyCharacter> Field::MY_CHARACTER;
unique_ptr<vector<unique_ptr<EnemyCharacter>>> Field::ENEMY_CHARACTERS;
//unique_ptr<map<CharacterID, unique_ptr<EnemyCharacter>>> Field::IDENTIFIABLE_ENEMY_CHARACTERS;
unique_ptr<vector<unique_ptr<Offensive>>> Field::MY_OFFENSIVES;
unique_ptr<vector<unique_ptr<Offensive>>> Field::ENEMY_OFFENSIVES;
unique_ptr<map<CharacterID, bool>> Field::DEAD_FLAGS;
const int Field::DRAW_POSITION_X = 350;				//フィールドの描画位置中心X座標(ピクセル)
const int Field::DRAW_POSITION_Y = 384;				//フィールドの描画位置中心Y座標(ピクセル)
const int Field::PIXEL_SIZE_X = 620;				//フィールドの幅(ピクセル)
const int Field::PIXEL_SIZE_Y = 742;				//フィールドの高さ(ピクセル)
const double Field::DRAW_EXTRATE = 1.0;				//フィールドの描画倍率
const double Field::BACKGROUND_DRAW_EXTRATE = 1.0;	//フィールド背景画の描画倍率



void Field::INITIALIZE() {
	MY_CHARACTER.reset(new IchigoChan);
	ENEMY_CHARACTERS.reset(new vector<unique_ptr<EnemyCharacter>>);
	//IDENTIFIABLE_ENEMY_CHARACTERS.reset(new map<CharacterID, unique_ptr<EnemyCharacter>>);
	MY_OFFENSIVES.reset(new vector<unique_ptr<Offensive>>);
	ENEMY_OFFENSIVES.reset(new vector<unique_ptr<Offensive>>);
	DEAD_FLAGS.reset(new map<CharacterID, bool>);
}


void Field::UPDATE() {

	MY_CHARACTER->update();

	for (const auto& enemy_character : *ENEMY_CHARACTERS) {
		enemy_character->update();
	}

	//for (const auto& identifiable_enemy_character_map : *IDENTIFIABLE_ENEMY_CHARACTERS) {
	//	auto& identifiable_enemy_character = identifiable_enemy_character_map.second;
	//	identifiable_enemy_character->update();
	//}

	for (const auto& my_offensive : *MY_OFFENSIVES) {
		my_offensive->update();
	}

	for (const auto& enemy_offensive : *ENEMY_OFFENSIVES) {
		enemy_offensive->update();
	}

	DebugParams::OBJECTS = MY_OFFENSIVES->size() + ENEMY_OFFENSIVES->size() + ENEMY_CHARACTERS->size() + 1;
}


void Field::DRAW() {
	DxLib::DrawRotaGraph(DRAW_POSITION_X, DRAW_POSITION_Y, BACKGROUND_DRAW_EXTRATE, 0, ImageHandles::FIELD_BACKGROUND_STAGE1, TRUE);

	for (const auto& my_offensive : *MY_OFFENSIVES) {
		my_offensive->draw();
		if (DebugParams::DEBUG_FLAG == true) my_offensive->draw_durability();
	}

	for (const auto& enemy_offensive : *ENEMY_OFFENSIVES) {
		enemy_offensive->draw();
		if (DebugParams::DEBUG_FLAG == true) enemy_offensive->draw_durability();
	}

	MY_CHARACTER->draw();
	if (DebugParams::DEBUG_FLAG == true) MY_CHARACTER->draw_life();

	for (const auto& enemy_character : *ENEMY_CHARACTERS) {
		enemy_character->draw();
		if (DebugParams::DEBUG_FLAG == true) enemy_character->draw_HP();
	}

	//for (const auto& identifiable_enemy_character_map : *IDENTIFIABLE_ENEMY_CHARACTERS) {
	//	auto& identifiable_enemy_character = identifiable_enemy_character_map.second;
	//	identifiable_enemy_character->draw();
	//	if (DebugParams::DEBUG_FLAG == true) identifiable_enemy_character->draw_HP();
	//}

	if (DebugParams::DEBUG_FLAG == true) {
		InFieldPosition::DRAW_MOVABLE_BOUNDARY();
		InFieldPosition::DRAW_EXISTENCE_BOUNDARY();
	}
}


void Field::DEAL_COLLISION() {

	if (MY_CHARACTER->is_collided_with_enemy_offensives() == true) MY_CHARACTER->damaged();

	for (const auto& enemy_character : *ENEMY_CHARACTERS) {
		if (enemy_character->is_collided_with_my_offensives() == true) enemy_character->damaged();
	}
	//for (const auto& identifiable_enemy_character_map : *IDENTIFIABLE_ENEMY_CHARACTERS) {
	//	auto& identifiable_enemy_character = identifiable_enemy_character_map.second;
	//	if (identifiable_enemy_character->is_collided_with_my_offensives() == true) identifiable_enemy_character->damaged();
	//}
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
		if (ENEMY_CHARACTERS->at(i)->is_dead() == true) {
			ENEMY_CHARACTERS->erase(ENEMY_CHARACTERS->begin() + i);
			DxLib::PlaySoundMem(SoundHandles::ZAKOCRASH, DX_PLAYTYPE_BACK);
			GameConductor::SCORE += ZakoCharacter::CRUSH_BONUS;
		}
	}
}


void Field::ERASE_OUTSIDED_OBJECTS() {
	for (int i = ENEMY_CHARACTERS->size() - 1; i >= 0; --i) {
		InFieldPosition pos = *(ENEMY_CHARACTERS->at(i)->position);
		bool outsided_flag =
			pos.x < InFieldPosition::MIN_EXISTENCE_BOUNDARY_X ||
			pos.y < InFieldPosition::MIN_EXISTENCE_BOUNDARY_Y ||
			pos.x > InFieldPosition::MAX_EXISTENCE_BOUNDARY_X ||
			pos.y > InFieldPosition::MAX_EXISTENCE_BOUNDARY_Y;
		if (outsided_flag == true) ENEMY_CHARACTERS->erase(ENEMY_CHARACTERS->begin() + i);
	}
	for (int i = MY_OFFENSIVES->size() - 1; i >= 0; --i) {
		InFieldPosition pos = *(MY_OFFENSIVES->at(i)->position);
		bool outsided_flag =
			pos.x < InFieldPosition::MIN_EXISTENCE_BOUNDARY_X ||
			pos.y < InFieldPosition::MIN_EXISTENCE_BOUNDARY_Y ||
			pos.x > InFieldPosition::MAX_EXISTENCE_BOUNDARY_X ||
			pos.y > InFieldPosition::MAX_EXISTENCE_BOUNDARY_Y;
		if (outsided_flag == true) MY_OFFENSIVES->erase(MY_OFFENSIVES->begin() + i);
	}
	for (int i = ENEMY_OFFENSIVES->size() - 1; i >= 0; --i) {
		InFieldPosition pos = *(ENEMY_OFFENSIVES->at(i)->position);
		bool outsided_flag =
			pos.x < InFieldPosition::MIN_EXISTENCE_BOUNDARY_X ||
			pos.y < InFieldPosition::MIN_EXISTENCE_BOUNDARY_Y ||
			pos.x > InFieldPosition::MAX_EXISTENCE_BOUNDARY_X ||
			pos.y > InFieldPosition::MAX_EXISTENCE_BOUNDARY_Y;
		if (outsided_flag == true) ENEMY_OFFENSIVES->erase(ENEMY_OFFENSIVES->begin() + i);
	}
}


unique_ptr<EnemyCharacter>& Field::GET_ENEMY_CHARACTER(enum CharacterID given_id) {
	for (auto& enemy_character : *ENEMY_CHARACTERS) {
		if (enemy_character->id == given_id) {
			return enemy_character;
		}
	}
}


void Field::ERASE_ENEMY_CHARACTER(enum CharacterID given_id) {
	for (int i = ENEMY_CHARACTERS->size() - 1; i >= 0; --i) {
		if (ENEMY_CHARACTERS->at(i)->id == given_id) {
			ENEMY_CHARACTERS->erase(ENEMY_CHARACTERS->begin() + i);
		}
	}
}