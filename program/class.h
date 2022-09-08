#pragma once
#include <string>
#include <vector>
#include "enum.h"

using std::string;
using std::vector;

//クラスの前方宣言
class AppSession;
class GameSession;


class Screen;
class TitleScreen;
class GameScreen;
class ResultScreen;
class RankingScreen;

class Character;
class MyCharacter;
class Deziko;
class EnemyCharacter;
class ZakoCharacter;
class BossCharacter;

class Bullet;
class MyBullet;
class EnemyBullet;

class EnemyBarrage;

class Stage;
class Stage1;

class Field;
class Scoreboard;


//クラスの宣言

class AppSession {
private:
	Scene now_scene;
	GameScreen* game_screen;
	GameSession* game_session;
};


class GameSession {

};


class Screen {
public:
	static const int SCREEN_RESOLUTION_X = 1024;	//画面解像度X(ピクセル)
	static const int SCREEN_RESOLUTION_Y = 768;		//画面解像度Y(ピクセル)
};


class TitleScreen : public Screen {

};

class GameScreen : public Screen {
private:
	Field field;
	Scoreboard scoreboard;
};

class ResultScreen : public Screen {

};

class RankingScreen : public Screen {

};





class Character {
private:
	int position_x;
	int position_y;
protected:
	Character();
public:
};


class MyCharacter : public Character{
protected:
	unsigned int life;
	MyCharacter();
	static const int INITIAL_POSITION_X = 350;
	static const int INITIAL_POSITION_Y = 590;
};


class Deziko : public MyCharacter {
public:
	string name;
	Deziko();
};


class EnemyCharacter : public Character{
private:
	unsigned int HP;
};


class ZakoCharacter : public EnemyCharacter {

};


class BossCharacter : public EnemyCharacter {

};




class Bullet {

};


class MyBullet : public Bullet {

};


class StraightShot : public MyBullet {

};


class EnemyBullet : public Bullet {

};




class EnemyBarrage {

};



class Stage {

};


class Stage1 : public Stage {

};


class Field {
private:
	MyCharacter& my_character;
	vector<EnemyCharacter> enemy_characters;
	vector<MyBullet> my_bullets;
	vector<EnemyBullet> enemy_bullets;

public:
	Field();
	void draw();
	static const int FIELD_DRAW_POSITION_X = 350;	//フィールドの描画位置中心X座標(ピクセル)
	static const int FIELD_DRAW_POSITION_Y = 384;	//フィールドの描画位置中心Y座標(ピクセル)
	static const int FIELD_PIXEL_SIZE_X = 620;		//フィールドの幅(ピクセル)
	static const int FIELD_PIXEL_SIZE_Y = 742;		//フィールドの高さ(ピクセル)
	static const double FIELD_DRAW_EXTRATE;			
};


class Scoreboard {

};