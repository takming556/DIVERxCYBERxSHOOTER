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
	static const int DRAW_POSITION_X;	//�t�B�[���h�̕`��ʒu���SX���W(�s�N�Z��)
	static const int DRAW_POSITION_Y;	//�t�B�[���h�̕`��ʒu���SY���W(�s�N�Z��)
	static const int PIXEL_SIZE_X;		//�t�B�[���h�̕�(�s�N�Z��)
	static const int PIXEL_SIZE_Y;		//�t�B�[���h�̍���(�s�N�Z��)
	static const double DRAW_EXTRATE;	//�t�B�[���h�̕`��{��
	static const double BACKGROUND_DRAW_EXTRATE;	//�t�B�[���h�w�i��̕`��{��
};
