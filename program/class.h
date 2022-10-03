#pragma once
#include <string>
#include <vector>
#include <memory>
#include "DxLib.h"
#include "enum.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;

constexpr double pi = 3.141592653589793238462643383279502884;

//�N���X�̑O���錾
class GameConductor;
class Field;
class Scoreboard;
class Stage1;
class MyCharacter;
class EnemyCharacter;
class Offensive;
class CollideRealm;
class InFieldPosition;
class CollideCircle;



//�N���X�̒�`

class AppSession {
private:
	Scene now_scene;
	unique_ptr<GameConductor> game_conductor;
	unsigned int fps_limit;
	LONGLONG clock_keeper_for_screenflip;
	int clock_keeper_for_measure_fps;
	unsigned int flip_count;
	unsigned int actual_fps;	//����FPS
	double instant_fps;			//�u��FPS
public:
	AppSession();
	void update();
};


class GameConductor {
private:
	Stage now_stage;
	unique_ptr<Scoreboard> scoreboard;
	unique_ptr<Stage1> stage1;
public:
	GameConductor();
	void update();
	void check_keyinput();
};


class Field {
private:
	Field() {}
public:
	static unique_ptr<MyCharacter> MY_CHARACTER;
	static unique_ptr<vector<unique_ptr<EnemyCharacter>>> ENEMY_CHARACTERS;
	static unique_ptr<vector<unique_ptr<Offensive>>> MY_OFFENSIVES;
	static unique_ptr<vector<unique_ptr<Offensive>>> ENEMY_OFFENSIVES;
	static void UPDATE();
	static void INITIALIZE();
	static void DRAW();
	static void DEAL_COLLISION();
	static const int FIELD_DRAW_POSITION_X = 350;	//�t�B�[���h�̕`��ʒu���SX���W(�s�N�Z��)
	static const int FIELD_DRAW_POSITION_Y = 384;	//�t�B�[���h�̕`��ʒu���SY���W(�s�N�Z��)
	static const int FIELD_PIXEL_SIZE_X = 620;		//�t�B�[���h�̕�(�s�N�Z��)
	static const int FIELD_PIXEL_SIZE_Y = 742;		//�t�B�[���h�̍���(�s�N�Z��)
	static const double FIELD_DRAW_EXTRATE;
};


class Character {
protected:
	LONGLONG previously_updated_clock;
	unique_ptr<InFieldPosition> position;
	Character(int init_pos_x, int init_pos_y, unique_ptr<CollideRealm> given_collidant);
public:
	unique_ptr<CollideRealm> collidant;
};


class MyCharacter : virtual public Character {
protected:
	string name;
	unsigned int life;
	double shot_frequency;							//�A�ˑ��x
	double move_speed;								//�ړ����x(pixel per second)
	LONGLONG clock_keeper_for_launch_ticking;
	LONGLONG clock_keeper_for_move_upward;
	LONGLONG clock_keeper_for_move_downward;
	LONGLONG clock_keeper_for_move_rightward;
	LONGLONG clock_keeper_for_move_leftward;
	MyCharacter(string character_name);
	static const int INITIAL_POSITION_X = 0;
	static const int INITIAL_POSITION_Y = 0;
	static const unsigned int COLLIDANT_SIZE = 15;
public:
	virtual ~MyCharacter() {}
	virtual void draw() = 0;
	void update();
	void respond_to_keyinput();
	void move_upward(LONGLONG delta_time);
	void move_downward(LONGLONG delta_time);
	void move_rightward(LONGLONG delta_time);
	void move_leftward(LONGLONG delta_time);
	void launch();
	void damaged();
	void draw_life();
	bool is_collided_with_enemy_offensives();
};


class IchigoChan : public MyCharacter {
private:
	static const string CHARACTER_NAME;
public:
	IchigoChan();
	void draw() override;
};


class EnemyCharacter : virtual public Character{
protected:
	unsigned int HP;
	EnemyCharacter(unsigned int init_HP);
public:
	virtual ~EnemyCharacter() {}
	virtual void update() = 0;
	virtual void draw() = 0;
	void damaged();
	void draw_HP();
	bool is_collided_with_my_offensives();
};


class ZakoCharacter : virtual public EnemyCharacter {
protected:
	ZakoCharacter() {}
};


class ZkChrStg1Wv1 : public ZakoCharacter {
private:
	double speed;
	double arg;
	unsigned int tick_count;
	unsigned int shot_count;
	LONGLONG previously_updated_clock;
	int previously_shot_completed_clock;
	int previously_tick_fired_clock;
	static const unsigned int TICKS = 3;
	static const unsigned int SHOTS = 3;
	static const unsigned int TICK_INTERVAL = 125;
	static const unsigned int SHOT_INTERVAL = 2000;
	static const unsigned int INITIAL_HP = 5;
	static const unsigned int COLLIDANT_SIZE = 20;
public:
	ZkChrStg1Wv1(int init_pos_x, int init_pos_y, double init_arg, double init_speed);
	void update() override;
	void draw() override;
};


class ZkChrStg1BsSp3 : public ZakoCharacter {
private:

	static const unsigned int INITIAL_HP = 30;
	static const unsigned int COLLIDANT_SIZE = 30;
public:
	ZkChrStg1BsSp3(int init_pos_x, int init_pos_y, double init_arg);
};


class BossCharacter : virtual public EnemyCharacter {
protected:
	string name;
	BossCharacter(string character_name);
};


class Mofu : public BossCharacter {
private:
	int clock_keeper_for_periodic_emission;
	static const string CHARACTER_NAME;
	static const int INITIAL_POS_X = 310;
	static const int INITIAL_POS_Y = 620;
	static const unsigned int INITIAL_HP = 100;
	static const unsigned int COLLIDANT_SIZE = 60;
public:
	Mofu();
	void update() override;
	void draw() override;
};


class Offensive {
protected:
	unsigned int durability;
	LONGLONG clock_keeper_for_update;
	Offensive(unique_ptr<CollideRealm> given_collidant, unsigned int init_durability);
public:
	unique_ptr<CollideRealm> collidant;
	bool is_collided_with_my_character();
	bool is_collided_with_enemy_characters();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void draw_durability() = 0;
	virtual ~Offensive() {}
};


class Bullet : virtual public Offensive {
protected:
	unique_ptr<InFieldPosition> center_pos;
	double arg;		//�i�s����(���W�A���C�E��0)
	double speed;	//�e�̑��x(pixel per second)
public:
	Bullet(double init_x, double init_y, double init_arg, double init_speed);
	void draw_durability() override;
};


class StraightShot : virtual public Bullet {
private:
	enum SkinID skin_id;
public:
	StraightShot(double init_x, double init_y, double init_arg, double init_speed, unsigned int collidant_size, unsigned int durability, enum SkinID given_skin_id);
	void update() override;
	void draw() override;
};


class HomingShot : public Bullet {

};


class ParabolicShot : public Bullet {
	static double flight_accel_constant;
	static double flight_accel_arg;
};


class KurageAmeShot : public ParabolicShot {
private:
	static double fall_acceleration_constant;

public:
	KurageAmeShot(double init_x, double init_y, double init_arg, double init_speed);
};


class GravityShot : public Bullet {

};

class Laser : public Offensive {

};


class BendingLaser : public Laser {

};


class Barrage {
public:
	virtual void perform() = 0;
};


class SimpleRadiation : public Barrage {
protected:
	const double x;
	const double y;
	const unsigned int amount;
	SimpleRadiation(double emit_pos_x, double emit_pos_y, unsigned int emit_amount);
};


class StraightSimpleRadiation : public SimpleRadiation {
protected:
	enum TeamID team_id;
	double giving_speed;
	unsigned int giving_collidant_size;
	unsigned int giving_durability;
	enum SkinID giving_skin_id;

public:
	StraightSimpleRadiation(
		double emit_pos_x,
		double emit_pos_y,
		unsigned int emit_amount,
		double given_speed,
		unsigned int given_collidant_size,
		unsigned int given_durability,
		enum TeamID given_team_id,
		enum SkinID given_skin_id
	);
	void perform() override;
};


class Scenario {
protected:
	int kept_clock;
	int elapsed_time;
	Scenario();
	virtual void update() = 0;
};


class Stage1 : public Scenario {
private:
	enum Stage1Progress stage1_progress;
public:
	Stage1();
	void update() override;
};


class Scoreboard {

};


class CollideRealm {
protected:
	static const unsigned int DRAW_COLOR;
public:
	CollideRealm() {}
	virtual bool is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) = 0;
	virtual void draw() = 0;
	virtual void update(unique_ptr<InFieldPosition>& now_pos) = 0;
};


class CollideCircle : public CollideRealm {
protected:
	unique_ptr<InFieldPosition> center_pos;
	unsigned int radius;
public:
	CollideCircle(double init_center_pos_x, double init_center_pos_y, unsigned int init_radius);
	bool is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) override;
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
	static const int SCREEN_RESOLUTION_X = 1024;	//��ʉ𑜓xX(�s�N�Z��)
	static const int SCREEN_RESOLUTION_Y = 768;		//��ʉ𑜓xY(�s�N�Z��)
};


class ImageHandles {
private:
	ImageHandles() {}	//�B��̃R���X�g���N�^��private�ɂ��邱�ƂŎ��̂̐������֎~���Ă���
public:
	static void LOAD_ALL_IMAGE();
	static int FIELD_BACKGROUND;
	static int TEST_SHOOTER;
	static int BLUE_MARBLE;
	static int RED_MARBLE;
	static int MAJIKICHI_SMILE;
	static int HAND_POWER;
	static int PIEN;
	static int HEART;
	static int MELTING_FACE;
	static int THINKING_FACE;
	static int SUNGLASS_FACE;
	static int KURAGE;
};


class KeyPushFlags {
private:
	KeyPushFlags() {}
public:
	static void INITIALIZE();
	static char KEY_BUFFER[256];
	static bool Z;
	static bool UP;
	static bool DOWN;
	static bool RIGHT;
	static bool LEFT;
};


class Colors {
private:
	Colors() {}
public:
	static void INITIALIZE();
	static int RED;
	static int GREEN;
	static int BLUE;
	static int YELLOW;
	static int CYAN;
	static int MAZENTA;
};


class DebugParams {

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
