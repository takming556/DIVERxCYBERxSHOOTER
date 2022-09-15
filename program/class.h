#pragma once
#include <string>
#include <vector>
#include <memory>
#include "DxLib.h"
#include "enum.h"

using std::string;
using std::vector;
using std::unique_ptr;

constexpr double pi = 3.141592653589793238462643383279502884;

//クラスの前方宣言
class GameConductor;
class Field;
class Scoreboard;
class Stage1;
class MyCharacter;
class EnemyCharacter;
class Offensive;
class InFieldPosition;
class CollideCircle;


//クラスの定義

class AppSession {
private:
	Scene now_scene;
	unique_ptr<GameConductor> game_conductor;
	unsigned int fps_limit;
	LONGLONG clock_keeper_for_screenflip;
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
};


class MyCharacter : public Character {
protected:
	unique_ptr<CollideCircle> collidant;
	string name;
	unsigned int life;
	double shot_frequency;							//連射速度
	double move_speed;								//移動速度(pixel per second)
	LONGLONG clock_keeper_for_launch_ticking;
	LONGLONG clock_keeper_for_move_upward;
	LONGLONG clock_keeper_for_move_downward;
	LONGLONG clock_keeper_for_move_rightward;
	LONGLONG clock_keeper_for_move_leftward;
	bool is_z_key_pushed;
	bool is_x_key_pushed;
	bool is_up_key_pushed;
	bool is_down_key_pushed;
	bool is_right_key_pushed;
	bool is_left_key_pushed;
	MyCharacter(string character_name);
	static const int INITIAL_POSITION_X = 0;
	static const int INITIAL_POSITION_Y = 0;
	static const unsigned int COLLIDANT_SIZE = 15;
public:
	virtual void draw() = 0;
	void update(char key_buffer[], vector<unique_ptr<Offensive>>& my_offensives);
	void respond_to_keyinput(char key_buffer[], vector<unique_ptr<Offensive>>& my_offensives);
	void move_upward(LONGLONG delta_time);
	void move_downward(LONGLONG delta_time);
	void move_rightward(LONGLONG delta_time);
	void move_leftward(LONGLONG delta_time);
	void launch(vector<unique_ptr<Offensive>>& my_offensives);
};


class MyCharacter1 : public MyCharacter {
private:
	static const string character_name;
public:
	MyCharacter1();
	void draw() override;
};


class EnemyCharacter : public Character{
protected:
	unsigned int HP;
	EnemyCharacter(int init_pos_x, int init_pos_y, int init_HP);
public:
	virtual void update(vector<unique_ptr<Offensive>>& enemy_offensives) = 0;
	virtual void draw() = 0;
};


class ZakoCharacter : public EnemyCharacter {
protected:
	ZakoCharacter(int init_pos_x, int init_pos_y, int init_HP);
};


class ZakoCharacter1 : public ZakoCharacter {
public:
	ZakoCharacter1(int init_pos_x, int init_pos_y);
};


class BossCharacter : public EnemyCharacter {
protected:
	string name;
	BossCharacter(double init_pos_x, double init_pos_y, int init_HP, string character_name);
};


class BossCharacter1 : public BossCharacter {
private:
	int clock_keeper_for_periodic_emission;
	static const string CHARACTER_NAME;
	static const int INITIAL_POS_X = 310;
	static const int INITIAL_POS_Y = 620;
	static const unsigned int INITIAL_HP = 100;
public:
	BossCharacter1();
	void update(vector<unique_ptr<Offensive>>& enemy_offensives) override;
	void draw() override;
};


class Offensive {
protected:
	LONGLONG clock_keeper_for_update;
	Offensive();
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
private:
	double speed;	//弾の速度(pixel per second)
	double arg;		//進行方向(ラジアン，右が0)
public:
	StraightShot(double init_x, double init_y, double init_arg = 0, double init_speed = 150);
	void update() override;
	void draw() override;
};


class HomingShot : public Bullet {

};


class Laser : public Offensive {

};


class Barrage {

};


class StraightRadiation : public Barrage {
private:
	const int x;
	const int y;
	const unsigned int amount;
public:
	StraightRadiation(int emit_pos_x, int emit_pos_y, unsigned int emit_amount);
	void perform(vector<unique_ptr<Offensive>>& given_offensives);
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
	virtual void update(unique_ptr<InFieldPosition>& now_pos) = 0;
	static const unsigned int DRAW_COLOR;
};


class CollideCircle : public CollideRealm {
protected:
	unique_ptr<InFieldPosition> center_pos;
	unsigned int radius;
public:
	CollideCircle(double init_center_pos_x, double init_center_pos_y, unsigned int init_radius);
	bool is_collided_with(unique_ptr<CollideCircle>& given_collide_circle) override;
	void draw() override;
	void update(unique_ptr<InFieldPosition>& now_pos) override;
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
