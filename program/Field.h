#pragma once
#include <memory>
#include <vector>
//#include <unordered_map>
#include <map>
#include "enum.h"
#include "Offensive/Bullet/Bullet.h"
#include "Offensive/Laser/Laser.h"
#include "Character/MyCharacter/MyCharacter.h"
//#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "SpNameDisplay.h"
#include "SongNameDisplay.h"
#include "StageNameDisplay.h"

using BulletID = unsigned int;
using LaserID = unsigned int;

using std::unique_ptr;
using std::vector;
using std::map;
//using std::unordered_map;

//class MyCharacter;
//class EnemyCharacter;
//class Offensive;


class Field {
private:
	Field() {}
public:
	static unique_ptr<MyCharacter> MY_CHARACTER;
	//static unique_ptr<vector<unique_ptr<EnemyCharacter>>> ENEMY_CHARACTERS;
	static unique_ptr<vector<unique_ptr<ZakoCharacter>>> ZAKO_CHARACTERS;
	static unique_ptr<vector<unique_ptr<BossCharacter>>> BOSS_CHARACTERS;
	//static unique_ptr<map<CharacterID, unique_ptr<EnemyCharacter>>> IDENTIFIABLE_ENEMY_CHARACTERS;
	static unique_ptr<map<BulletID, unique_ptr<Bullet>>> MY_BULLETS;
	static unique_ptr<map<BulletID, unique_ptr<Bullet>>> ENEMY_BULLETS;
	static unique_ptr<map<LaserID, unique_ptr<Laser>>> MY_LASERS;
	static unique_ptr<map<LaserID, unique_ptr<Laser>>> ENEMY_LASERS;
	static unique_ptr<map<CharacterID, bool>> DEAD_FLAGS;
	static unique_ptr<SpNameDisplay> SP_NAME_DISPLAY;
	static unique_ptr<SongNameDisplay> SONG_NAME_DISPLAY;
	static unique_ptr<StageNameDisplay> STAGE_NAME_DISPLAY;

	static void UPDATE();
	static void INITIALIZE();
	static void DRAW();
	static void DEAL_COLLISION();
	static void ERASE_BROKEN_OFFENSIVES();
	static void DEAL_DEATHS();
	//static void ERASE_DEAD_ZAKO_CHARACTERS();
	static void ERASE_OUTSIDED_OBJECTS();
	static unique_ptr<ZakoCharacter>& GET_ZAKO_CHARACTER(CharacterID given_id);
	static unique_ptr<BossCharacter>& GET_BOSS_CHARACTER(CharacterID given_id);
	static bool ERASE_ZAKO_CHARACTER(CharacterID given_id);
	static bool IS_THERE(CharacterID given_id);
	static bool IS_THERE(BulletID given_id);
	static const int DRAW_POSITION_X;				// フィールドの描画位置中心X座標(ピクセル)
	static const int DRAW_POSITION_Y;				// フィールドの描画位置中心Y座標(ピクセル)
	static const int PIXEL_SIZE_X;					// フィールドの幅(ピクセル)
	static const int PIXEL_SIZE_Y;					// フィールドの高さ(ピクセル)
	static const double DRAW_EXTRATE;				// フィールドの描画倍率
	static const double BACKGROUND_DRAW_EXTRATE;	// フィールド背景画の描画倍率
};