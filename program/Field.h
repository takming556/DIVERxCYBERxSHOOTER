#pragma once
#include <memory>
#include <vector>
#include <map>
#include "enum.h"

#include "Offensive/Offensive.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"

using std::unique_ptr;
using std::vector;
using std::map;

class MyCharacter;
//class EnemyCharacter;
//class Offensive;

class Field {
private:
	Field() {}
public:
	static unique_ptr<MyCharacter> MY_CHARACTER;
	static unique_ptr<vector<unique_ptr<EnemyCharacter>>> ENEMY_CHARACTERS;
	static unique_ptr<map<CharacterID, unique_ptr<EnemyCharacter>>> IDENTIFIABLE_ENEMY_CHARACTERS;
	static unique_ptr<vector<unique_ptr<Offensive>>> MY_OFFENSIVES;
	static unique_ptr<vector<unique_ptr<Offensive>>> ENEMY_OFFENSIVES;
	static unique_ptr<map<CharacterID, bool>> DEAD_FLAGS;

	static void UPDATE();
	static void INITIALIZE();
	static void DRAW();
	static void DEAL_COLLISION();
	static void ERASE_BROKEN_OFFENSIVES();
	static void ERASE_DEAD_CHARACTERS();
	static void ERASE_OUTSIDED_OBJECTS();
	static const int DRAW_POSITION_X;	//フィールドの描画位置中心X座標(ピクセル)
	static const int DRAW_POSITION_Y;	//フィールドの描画位置中心Y座標(ピクセル)
	static const int PIXEL_SIZE_X;		//フィールドの幅(ピクセル)
	static const int PIXEL_SIZE_Y;		//フィールドの高さ(ピクセル)
	static const double DRAW_EXTRATE;	//フィールドの描画倍率
	static const double BACKGROUND_DRAW_EXTRATE;	//フィールド背景画の描画倍率
};
