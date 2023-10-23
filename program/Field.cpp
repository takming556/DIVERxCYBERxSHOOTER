#include <memory>
#include <vector>
//#include <unordered_map>
#include <map>
#include <typeinfo>
#include "DxLib.h"
#include "GameConductor.h"
#include "Field.h"
#include "Offensive/Offensive.h"
//#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "Character/MyCharacter/Ichigochan.h"
#include "Position/InFieldPosition.h"
#include "SpNameDisplay.h"
#include "SongNameDisplay.h"
//#include "Scenario/Scenario.h"
#include "StageNameDisplay.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"


using std::unique_ptr;
using std::make_unique;
using std::vector;
//using std::unordered_map;
using std::map;


unique_ptr<MyCharacter> Field::MY_CHARACTER;
//unique_ptr<vector<unique_ptr<EnemyCharacter>>> Field::ENEMY_CHARACTERS;
unique_ptr<vector<unique_ptr<ZakoCharacter>>> Field::ZAKO_CHARACTERS;
unique_ptr<vector<unique_ptr<BossCharacter>>> Field::BOSS_CHARACTERS;
//unique_ptr<map<CharacterID, unique_ptr<EnemyCharacter>>> Field::IDENTIFIABLE_ENEMY_CHARACTERS;
unique_ptr<map<BulletID, unique_ptr<Bullet>>> Field::MY_BULLETS;
unique_ptr<map<BulletID, unique_ptr<Bullet>>> Field::ENEMY_BULLETS;
unique_ptr<map<LaserID, unique_ptr<Laser>>> Field::MY_LASERS;
unique_ptr<map<LaserID, unique_ptr<Laser>>> Field::ENEMY_LASERS;
unique_ptr<map<CharacterID, bool>> Field::DEAD_FLAGS;
unique_ptr<SpNameDisplay> Field::SP_NAME_DISPLAY;
unique_ptr<SongNameDisplay> Field::SONG_NAME_DISPLAY;
unique_ptr<StageNameDisplay> Field::STAGE_NAME_DISPLAY;

const int Field::DRAW_POSITION_X = 350;				//フィールドの描画位置中心X座標(ピクセル)
const int Field::DRAW_POSITION_Y = 384;				//フィールドの描画位置中心Y座標(ピクセル)
const int Field::PIXEL_SIZE_X = 620;				//フィールドの幅(ピクセル)
const int Field::PIXEL_SIZE_Y = 742;				//フィールドの高さ(ピクセル)
const double Field::DRAW_EXTRATE = 1.0;				//フィールドの描画倍率
const double Field::BACKGROUND_DRAW_EXTRATE = 1.0;	//フィールド背景画の描画倍率



void Field::INITIALIZE() {
	MY_CHARACTER.reset(new IchigoChan);
	//ENEMY_CHARACTERS.reset(new vector<unique_ptr<EnemyCharacter>>);
	ZAKO_CHARACTERS.reset(new vector<unique_ptr<ZakoCharacter>>);
	BOSS_CHARACTERS.reset(new vector<unique_ptr<BossCharacter>>);
	//IDENTIFIABLE_ENEMY_CHARACTERS.reset(new map<CharacterID, unique_ptr<EnemyCharacter>>);
	MY_BULLETS.reset(new map<BulletID, unique_ptr<Bullet>>);
	ENEMY_BULLETS.reset(new map<BulletID, unique_ptr<Bullet>>);
	MY_LASERS.reset(new map<LaserID, unique_ptr<Laser>>);
	ENEMY_LASERS.reset(new map<LaserID, unique_ptr<Laser>>);
	DEAD_FLAGS.reset(new map<CharacterID, bool>);
	SP_NAME_DISPLAY.reset(new SpNameDisplay);
	SONG_NAME_DISPLAY.reset(new SongNameDisplay);
	STAGE_NAME_DISPLAY.reset(new StageNameDisplay);
}


void Field::UPDATE() {

	MY_CHARACTER->update();

	//for (const auto& enemy_character : *ENEMY_CHARACTERS) {
	//	enemy_character->update();
	//}

	for (const auto& zako_character : *ZAKO_CHARACTERS) {
		zako_character->update();
	}

	for (const auto& boss_character : *BOSS_CHARACTERS) {
		boss_character->update();
	}

	//for (const auto& identifiable_enemy_character_map : *IDENTIFIABLE_ENEMY_CHARACTERS) {
	//	auto& identifiable_enemy_character = identifiable_enemy_character_map.second;
	//	identifiable_enemy_character->update();
	//}

	for (const auto& my_offensive : *MY_BULLETS) {
		my_offensive.second->update();
	}

	for (const auto& enemy_offensive : *ENEMY_BULLETS) {
		enemy_offensive.second->update();
	}

	for (const auto& my_laser : *MY_LASERS) {
		my_laser.second->update();
	}

	for (const auto& enemy_laser : *ENEMY_LASERS) {
		enemy_laser.second->update();
	}

	DebugParams::OBJECTS
		= MY_BULLETS->size()
		+ ENEMY_BULLETS->size()
		+ ZAKO_CHARACTERS->size()
		+ BOSS_CHARACTERS->size()
		//+ ENEMY_CHARACTERS->size()
		+ 1		// MY_CHARACTER
		+ MY_LASERS->size()
		+ ENEMY_LASERS->size();
}


void Field::DRAW() {

	switch (GameConductor::NOW_STAGE)
	{
	case Stage::STAGE1:
		DxLib::DrawRotaGraph(DRAW_POSITION_X, DRAW_POSITION_Y, BACKGROUND_DRAW_EXTRATE, 0, ImageHandles::FIELD_BACKGROUND_STAGE1, TRUE);
		break;
	case Stage::STAGE2:
		DxLib::DrawRotaGraph(DRAW_POSITION_X, DRAW_POSITION_Y, BACKGROUND_DRAW_EXTRATE, 0, ImageHandles::FIELD_BACKGROUND_STAGE2, TRUE);
		break;
	case Stage::STAGE3:
		DxLib::DrawRotaGraph(DRAW_POSITION_X, DRAW_POSITION_Y, BACKGROUND_DRAW_EXTRATE, 0, ImageHandles::FIELD_BACKGROUND_STAGE3, TRUE);
		break;
	default:
		break;
	}

	for (const auto& my_laser : *MY_LASERS) {
		my_laser.second->draw();
	}

	for (const auto& enemy_laser : *ENEMY_LASERS) {
		enemy_laser.second->draw();
	}

	for (const auto& my_offensive : *MY_BULLETS) {
		my_offensive.second->draw();
		if (DebugParams::DEBUG_FLAG == true) my_offensive.second->draw_durability();
	}

	for (const auto& enemy_offensive : *ENEMY_BULLETS) {
		enemy_offensive.second->draw();
		if (DebugParams::DEBUG_FLAG == true) enemy_offensive.second->draw_durability();
	}

	for (const auto& zako_character : *ZAKO_CHARACTERS) {
		zako_character->draw();
		if (DebugParams::DEBUG_FLAG == true) zako_character->draw_hp();
	}

	for (const auto& boss_character : *BOSS_CHARACTERS) {
		boss_character->draw();
		if (DebugParams::DEBUG_FLAG == true) boss_character->draw_hp();
	}

	//for (const auto& enemy_character : *ENEMY_CHARACTERS) {
	//	enemy_character->draw();
	//	if (DebugParams::DEBUG_FLAG == true) enemy_character->draw_hp();
	//}

	MY_CHARACTER->draw();
	if (DebugParams::DEBUG_FLAG == true) MY_CHARACTER->draw_hp();

	SP_NAME_DISPLAY->draw();
	SONG_NAME_DISPLAY->draw();
	STAGE_NAME_DISPLAY->draw();

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
	
	MY_CHARACTER->deal_collision();

	//for (const auto& enemy_character : *ENEMY_CHARACTERS) {
	//	enemy_character->deal_collision();
	//}

	for (const auto& zako_character : *ZAKO_CHARACTERS) {
		zako_character->deal_collision();
	}

	for (const auto& boss_character : *BOSS_CHARACTERS) {
		boss_character->deal_collision();
	}

	for (const auto& my_bullet : *MY_BULLETS) {
		my_bullet.second->deal_collision(TeamID::MY);
	}

	for (const auto& enemy_bullet : *ENEMY_BULLETS) {
		enemy_bullet.second->deal_collision(TeamID::ENEMY);
	}

	//if (MY_CHARACTER->is_collided_with_enemy_offensives() == true) MY_CHARACTER->damaged();
	//for (const auto& enemy_character : *ENEMY_CHARACTERS) {
	//	if (enemy_character->is_collided_with_my_offensives() == true) enemy_character->damaged();
	//}
	//for (const auto& identifiable_enemy_character_map : *IDENTIFIABLE_ENEMY_CHARACTERS) {
	//	auto& identifiable_enemy_character = identifiable_enemy_character_map.second;
	//	if (identifiable_enemy_character->is_collided_with_my_offensives() == true) identifiable_enemy_character->damaged();
	//}
	//for (const auto& my_bullet : *MY_BULLETS) {
	//	if (my_bullet.second->is_collided_with_enemy_characters() == true) my_bullet.second->damaged();
	//}
	//for (const auto& enemy_bullet : *ENEMY_BULLETS) {
	//	if (enemy_bullet.second->is_collided_with_my_character() == true) enemy_bullet.second->damaged();
	//}
}


void Field::ERASE_BROKEN_OFFENSIVES() {
	//vector<bool> broken_my_bullet_ids;
	for (auto my_bullet = MY_BULLETS->begin(); my_bullet != MY_BULLETS->end();) {
		if (my_bullet->second->is_broken() == true)
			my_bullet = MY_BULLETS->erase(my_bullet);
		else
			++my_bullet;
	}
	for (auto enemy_bullet = ENEMY_BULLETS->begin(); enemy_bullet != ENEMY_BULLETS->end();) {
		if (enemy_bullet->second->is_broken() == true)
			enemy_bullet = ENEMY_BULLETS->erase(enemy_bullet);
		else
			++enemy_bullet;
	}
	//for (int i = MY_BULLETS->size() - 1; i >= 0; --i) {
	//	if (MY_BULLETS->at(i)->is_broken() == true) MY_BULLETS->erase(MY_BULLETS->begin() + i);
	//}
	//for (int i = ENEMY_BULLETS->size() - 1; i >= 0; --i) {
	//	if (ENEMY_BULLETS->at(i)->is_broken() == true) ENEMY_BULLETS->erase(ENEMY_BULLETS->begin() + i);
	//}
}



void Field::DEAL_DEATHS() {
	for ( int i = ZAKO_CHARACTERS->size() - 1; i >= 0; --i ) {
		unique_ptr<ZakoCharacter>& zako_character = ZAKO_CHARACTERS->at(i);
		if ( zako_character->is_dead() == true ) {
			zako_character->funeral();
			( *DEAD_FLAGS )[ zako_character->id ] = true;
			ZAKO_CHARACTERS->erase(ZAKO_CHARACTERS->begin() + i);
		}
	}
	
	for ( const auto& boss_character : *Field::BOSS_CHARACTERS ) {
		if ( boss_character->is_dead() == true ) {
			boss_character->funeral();
			( *DEAD_FLAGS )[ boss_character->id ] = true;
		}
	}
}



//void Field::ERASE_DEAD_ZAKO_CHARACTERS() {
//	for (int i = ZAKO_CHARACTERS->size() - 1; i >= 0; --i) {
//		unique_ptr<ZakoCharacter>& zako_character = ZAKO_CHARACTERS->at(i);
//		if (zako_character->is_dead() == true) {
//			zako_character->funeral();
//			(*DEAD_FLAGS)[zako_character->id] = true;
//			ZAKO_CHARACTERS->erase(ZAKO_CHARACTERS->begin() + i);
//		}
//	}
//}


void Field::ERASE_OUTSIDED_OBJECTS() {
	for (int i = ZAKO_CHARACTERS->size() - 1; i >= 0; --i) {
		InFieldPosition pos = *(ZAKO_CHARACTERS->at(i)->position);
		bool outsided_flag =
			pos.x < InFieldPosition::MIN_EXISTENCE_BOUNDARY_X ||
			pos.y < InFieldPosition::MIN_EXISTENCE_BOUNDARY_Y ||
			pos.x > InFieldPosition::MAX_EXISTENCE_BOUNDARY_X ||
			pos.y > InFieldPosition::MAX_EXISTENCE_BOUNDARY_Y;
		if (outsided_flag == true) ZAKO_CHARACTERS->erase(ZAKO_CHARACTERS->begin() + i);
	}
	for (auto my_bullet = MY_BULLETS->begin(); my_bullet != MY_BULLETS->end(); ++my_bullet) {
		InFieldPosition pos = *(my_bullet->second->position);
		bool outsided_flag =
			pos.x < InFieldPosition::MIN_EXISTENCE_BOUNDARY_X ||
			pos.y < InFieldPosition::MIN_EXISTENCE_BOUNDARY_Y ||
			pos.x > InFieldPosition::MAX_EXISTENCE_BOUNDARY_X ||
			pos.y > InFieldPosition::MAX_EXISTENCE_BOUNDARY_Y;
		if (outsided_flag == true) MY_BULLETS->erase(my_bullet++);
	}
	for (auto enemy_bullet = ENEMY_BULLETS->begin(); enemy_bullet != ENEMY_BULLETS->end(); ++enemy_bullet) {
		InFieldPosition pos = *(enemy_bullet->second->position);
		bool outsided_flag =
			pos.x < InFieldPosition::MIN_EXISTENCE_BOUNDARY_X ||
			pos.y < InFieldPosition::MIN_EXISTENCE_BOUNDARY_Y ||
			pos.x > InFieldPosition::MAX_EXISTENCE_BOUNDARY_X ||
			pos.y > InFieldPosition::MAX_EXISTENCE_BOUNDARY_Y;
		if (outsided_flag == true) ENEMY_BULLETS->erase(enemy_bullet++);
	}
	//for (int i = MY_BULLETS->size() - 1; i >= 0; --i) {
	//	InFieldPosition pos = *(MY_BULLETS->at(i)->position);
	//	bool outsided_flag =
	//		pos.x < InFieldPosition::MIN_EXISTENCE_BOUNDARY_X ||
	//		pos.y < InFieldPosition::MIN_EXISTENCE_BOUNDARY_Y ||
	//		pos.x > InFieldPosition::MAX_EXISTENCE_BOUNDARY_X ||
	//		pos.y > InFieldPosition::MAX_EXISTENCE_BOUNDARY_Y;
	//	if (outsided_flag == true) MY_BULLETS->erase(MY_BULLETS->begin() + i);
	//}
	//for (int i = ENEMY_BULLETS->size() - 1; i >= 0; --i) {
	//	InFieldPosition pos = *(ENEMY_BULLETS->at(i)->position);
	//	bool outsided_flag =
	//		pos.x < InFieldPosition::MIN_EXISTENCE_BOUNDARY_X ||
	//		pos.y < InFieldPosition::MIN_EXISTENCE_BOUNDARY_Y ||
	//		pos.x > InFieldPosition::MAX_EXISTENCE_BOUNDARY_X ||
	//		pos.y > InFieldPosition::MAX_EXISTENCE_BOUNDARY_Y;
	//	if (outsided_flag == true) ENEMY_BULLETS->erase(ENEMY_BULLETS->begin() + i);
	//}
}


unique_ptr<ZakoCharacter>& Field::GET_ZAKO_CHARACTER(CharacterID given_id) {
	for (auto& zako_character : *ZAKO_CHARACTERS) {
		if (zako_character->id == given_id) {
			return zako_character;
		}
	}
	throw "No such CharacterID of ZakoCharacter in Field";
}


bool Field::IS_THERE(CharacterID given_id) {
	bool found = false;
	for ( const auto& zako_character : *ZAKO_CHARACTERS ) {
		if ( zako_character->id == given_id ) {
			found = true;
		}
	}
	for (const auto& boss_character : *BOSS_CHARACTERS) {
		if (boss_character->id == given_id) {
			found = true;
		}
	}
	return found;
}


bool Field::ERASE_ZAKO_CHARACTER(CharacterID given_id) {
	bool erase_succeeded_flag = false;
	for (int i = ZAKO_CHARACTERS->size() - 1; i >= 0; --i) {
		if (ZAKO_CHARACTERS->at(i)->id == given_id) {
			ZAKO_CHARACTERS->erase(ZAKO_CHARACTERS->begin() + i);
			erase_succeeded_flag = true;
		}
	}
	return erase_succeeded_flag;
}