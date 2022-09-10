#pragma once
#include <string>
#include <vector>
#include <memory>
#include "enum.h"

using std::string;
using std::vector;
using std::unique_ptr;

//クラスの前方宣言
class GameConductor;
class Field;
class Scoreboard;
class Stage1;


//クラスの宣言

class AppSession {
private:
	Scene now_scene;
	unique_ptr<GameConductor> game_conductor;
public:
	AppSession();
	void update();
};


class GameConductor {
private:
	Stage now_stage;
	unique_ptr<Field> field;
	unique_ptr<Scoreboard> scoreboard;
	unique_ptr<Stage1> stage1;
	char key_buffer[256];
	bool is_up_key_pushed;
	bool is_down_key_pushed;
	bool is_right_key_pushed;
	bool is_left_key_pushed;
	bool is_z_key_pushed;
public:
	GameConductor();
	void update();
	void check_keyinput();
};


class Screen {
public:
	static const int SCREEN_RESOLUTION_X = 1024;	//画面解像度X(ピクセル)
	static const int SCREEN_RESOLUTION_Y = 768;		//画面解像度Y(ピクセル)
};
//
//
//class TitleScreen : public Screen {
//
//};
//
//class GameScreen : public Screen {
//private:
//	Field field;
//	Scoreboard scoreboard;
//};
//
//class ResultScreen : public Screen {
//
//};
//
//class RankingScreen : public Screen {
//
//};



class Character {
protected:
	int position_x;
	int position_y;
	Character(int init_pos_x, int init_pos_y);
};


class MyCharacter : public Character{
protected:
	string name;
	unsigned int life;
	double SPS;					//Shot Per Second
	bool is_up_key_pushed;
	bool is_down_key_pushed;
	bool is_right_key_pushed;
	bool is_left_key_pushed;
	bool is_z_key_pushed;
	MyCharacter(string character_name);
	static const int INITIAL_POSITION_X = 350;
	static const int INITIAL_POSITION_Y = 590;
public:
	void update();
	virtual void draw() {};
	void respond_to_keyinput(char key_buffer[]);
	void move_upward();
	void move_downward();
	void move_rightward();
	void move_leftward();
};


class MyCharacter1 : public MyCharacter {
private:
	const string character_name = "デジ子";
public:
	MyCharacter1();
	void draw() override;
};


class EnemyCharacter : public Character{
private:
	unsigned int HP;
protected:
	EnemyCharacter(int init_pos_x, int init_pos_y, int init_HP);
};


class ZakoCharacter : public EnemyCharacter {
protected:
	ZakoCharacter(int init_pos_x, int init_pos_y, int init_HP);
};


class ZakoCharacter1 : public ZakoCharacter {
private:
public:
	ZakoCharacter1(int init_pos_x, int init_pos_y);
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



class Scenario {

};


class Stage1 : public Scenario {

};


class Field {
private:
	unique_ptr<MyCharacter> my_character;
	vector<unique_ptr<EnemyCharacter>> enemy_characters;
	vector<unique_ptr<MyBullet>> my_bullets;
	vector<unique_ptr<EnemyBullet>> enemy_bullets;

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
