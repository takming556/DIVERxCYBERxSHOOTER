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
class MyCharacter;
class EnemyCharacter;
class Offensive;
class InFieldPosition;


//クラスの定義

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
	char key_buffer[256] = { NULL };
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


class Field {
public:
	unique_ptr<MyCharacter> my_character;
	vector<unique_ptr<EnemyCharacter>> enemy_characters;
	vector<unique_ptr<Offensive>> my_offensives;
	vector<unique_ptr<Offensive>> enemy_offensives;
	Field();
	void update(char key_buffer[]);
	void draw();
	static const int FIELD_DRAW_POSITION_X = 350;	//フィールドの描画位置中心X座標(ピクセル)
	static const int FIELD_DRAW_POSITION_Y = 384;	//フィールドの描画位置中心Y座標(ピクセル)
	static const int FIELD_PIXEL_SIZE_X = 620;		//フィールドの幅(ピクセル)
	static const int FIELD_PIXEL_SIZE_Y = 742;		//フィールドの高さ(ピクセル)
	static const double FIELD_DRAW_EXTRATE;
};



class Character {
protected:
	unique_ptr<InFieldPosition> position;
	Character(int init_pos_x, int init_pos_y);
public:
	virtual void draw() = 0;
};


class MyCharacter : public Character{
protected:
	string name;
	unsigned int life;
	double SPS;	//Shot Per Second
	int clock_keeper_for_launch_ticking;
	bool is_z_key_pushed;
	bool is_x_key_pushed;
	MyCharacter(string character_name);
	static const int INITIAL_POSITION_X = 0;
	static const int INITIAL_POSITION_Y = 0;
	//static const int INITIAL_POSITION_X = 350;
	//static const int INITIAL_POSITION_Y = 590;
public:
	void update(char key_buffer[], vector<unique_ptr<Offensive>>& my_offensives);
	void respond_to_keyinput(char key_buffer[], vector<unique_ptr<Offensive>>& my_offensives);
	void move_upward();
	void move_downward();
	void move_rightward();
	void move_leftward();
	void launch(vector<unique_ptr<Offensive>>& my_offensives);
};


class MyCharacter1 : public MyCharacter {
private:
public:
	MyCharacter1();
	void draw() override;
	static const string character_name;
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


class Offensive {
public:
	virtual void update() = 0;
	virtual void draw() = 0;
};


class Bullet : public Offensive {
protected:
	unique_ptr<InFieldPosition> center_pos;
public:
	Bullet(double init_x, double init_y);
};


class StraightShot : public Bullet {
public:
	StraightShot(double init_x, double init_y);
	void update() override;
	void draw() override;
};


class HomingShot : public Bullet {

};


class Laser : public Offensive {

};


class Scenario {

};


class Stage1 : public Scenario {

};


class Scoreboard {

};


class CollideRealm {
protected:
	virtual bool is_collided_with(unique_ptr<CollideCircle>& given_collide_circle) = 0;
	virtual void draw() = 0;
};


class CollideCircle : public CollideRealm {
protected:
	unique_ptr<InFieldPosition> center_pos;
	int radius;
public:
	CollideCircle(double init_center_pos_x, double init_center_pos_y, int init_radius);
	bool is_collided_with(unique_ptr<CollideCircle>& given_collide_circle) override;
	void draw() override;
};


class CollideRectangle : public CollideRealm {

};


class CollideTriangle : public CollideRealm {

};


class Position {
public:
	double x;
	double y;
	Position(double init_x, double init_y);
};


class InFieldPosition : public Position {
private:
	static const int DRAW_POS_OFFSET_X = - (Field::FIELD_PIXEL_SIZE_X / 2);
	static const int DRAW_POS_OFFSET_Y = - (Field::FIELD_PIXEL_SIZE_Y / 2);

public:
	InFieldPosition(double init_x, double init_y);
	Position get_draw_position();
};


class Screen {
public:
	static const int SCREEN_RESOLUTION_X = 1024;	//画面解像度X(ピクセル)
	static const int SCREEN_RESOLUTION_Y = 768;		//画面解像度Y(ピクセル)
};


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
