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

//クラスの前方宣言
class GameConductor;
class Field;
class Scoreboard;
class Stage1;
class MyCharacter;
class EnemyCharacter;
class Offensive;
class Barrage;
class CollideRealm;
class InFieldPosition;
class SimpleStraightShotEmission;
class RotatingStraightShotEmission;
class CollideCircle;



//クラスの定義

class AppSession {
private:
	Scene now_scene;
	unique_ptr<GameConductor> game_conductor;
	LONGLONG last_screenflipped_clock;
	int clock_keeper_for_measure_fps;
	unsigned int flip_count;
public:
	AppSession();
	void update();
};


class GameConductor {
private:
	Stage now_stage;
	unique_ptr<Scoreboard> scoreboard;
	unique_ptr<Stage1> stage1;
	int last_updated_clock;
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
	static const int FIELD_DRAW_POSITION_X = 350;	//フィールドの描画位置中心X座標(ピクセル)
	static const int FIELD_DRAW_POSITION_Y = 384;	//フィールドの描画位置中心Y座標(ピクセル)
	static const int FIELD_PIXEL_SIZE_X = 620;		//フィールドの幅(ピクセル)
	static const int FIELD_PIXEL_SIZE_Y = 742;		//フィールドの高さ(ピクセル)
	static const double FIELD_DRAW_EXTRATE;
};


class Character {
protected:
	LONGLONG last_updated_clock;
	Character(int init_pos_x, int init_pos_y, unique_ptr<CollideRealm> given_collidant);
public:
	unique_ptr<InFieldPosition> position;
	unique_ptr<CollideRealm> collidant;
};


class MyCharacter : virtual public Character {
protected:
	string name;
	unsigned int life;
	double shot_frequency;							//連射速度
	double move_speed;								//移動速度(pixel per second)
	int last_launch_ticked_clock;
	LONGLONG last_updated_clock;
	MyCharacter(string character_name);
	static const int INITIAL_POSITION_X = 0;
	static const int INITIAL_POSITION_Y = 0;
	static const unsigned int COLLIDANT_SIZE = 15;
	static const double SLOW_MOVE_SPEED_EXTRATE;
public:
	virtual ~MyCharacter() {}
	virtual void draw() = 0;
	void update();
	void respond_to_keyinput();
	void move_upward(bool slow_flag = false);
	void move_downward(bool slow_flag = false);
	void move_rightward(bool slow_flag = false);
	void move_leftward(bool slow_flag = false);
	void move_uprightward(bool slow_flag = false);
	void move_downrightward(bool slow_flag = false);
	void move_upleftward(bool slow_flag = false);
	void move_downleftward(bool slow_flag = false);
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
	LONGLONG last_updated_clock;
	int last_shot_completed_clock;
	int last_tick_fired_clock;
	static const unsigned int TICKS;
	static const unsigned int SHOTS;
	static const unsigned int TICK_INTERVAL;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
public:
	ZkChrStg1Wv1(int init_pos_x, int init_pos_y, double init_arg, double init_speed);
	void update() override;
	void draw() override;
};


class ZkChrStg1Wv2 : public ZakoCharacter {
private:
	unique_ptr<RotatingStraightShotEmission> barrage;
	double speed;
	double arg;
	LONGLONG last_updated_clock;
	static const unsigned int HP;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int BARRAGE_EMIT_NOZZLES;
	static const unsigned int BARRAGE_EMITS;
	static const unsigned int BARRAGE_EMIT_INTERVAL;
	static const double BARRAGE_INIT_ARG;
	static const double BARRAGE_SHOT_SPEED;
	static const unsigned int BARRAGE_SHOT_COLLIDANT_SIZE;
	static const unsigned int BARRAGE_SHOT_DURABILITY;
public:
	ZkChrStg1Wv2(double init_pos_x, double init_pos_y, double init_arg, double init_speed, double barrage_rotate_speed);
	void update() override;
	void draw() override;
};


class ZkChrStg1Wv3S : public ZakoCharacter { //クジラ
private:
	//double speed;
	//double arg;
	unsigned int tick_count;
	//unsigned int shot_count;
	//LONGLONG last_updated_clock;
	int last_shot_completed_clock;
	int last_tick_fired_clock;
	static const unsigned int TICKS;
	//static const unsigned int SHOTS;
	static const unsigned int TICK_INTERVAL;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
public:
	ZkChrStg1Wv3S(int init_pos_x, int init_pos_y);
	void update() override;
	void draw() override;

};


class ZkChrStg1Wv3L : public ZakoCharacter { //クラゲ
private:
	unique_ptr<RotatingStraightShotEmission> barrage;
	//double speed;
	//double arg;
	//LONGLONG last_updated_clock;
	static const unsigned int HP;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int BARRAGE_EMIT_NOZZLES;
	static const unsigned int BARRAGE_EMITS;
	static const unsigned int BARRAGE_EMIT_INTERVAL;
	static const double BARRAGE_INIT_ARG;
	static const double BARRAGE_SHOT_SPEED;
	static const unsigned int BARRAGE_SHOT_COLLIDANT_SIZE;
	static const unsigned int BARRAGE_SHOT_DURABILITY;
public:
	ZkChrStg1Wv3L(double init_pos_x, double init_pos_y, double barrage_rotate_speed);
	void update() override;
	void draw() override;

};


class ZkChrStg1Wv4 : public ZakoCharacter { //クジラ
private:
	unique_ptr<SimpleStraightShotEmission> barrage;
	//double speed;
	//double arg;
	//LONGLONG last_updated_clock;
	static const unsigned int HP;
	static const unsigned int TICKS;
	static const unsigned int TICK_INTERVAL;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int BARRAGE_EMIT_NOZZLES;
	static const unsigned int BARRAGE_EMITS;
	static const unsigned int BARRAGE_EMIT_INTERVAL;
	static const double BARRAGE_INIT_ARG;
	static const double BARRAGE_SHOT_SPEED;
	static const unsigned int BARRAGE_SHOT_COLLIDANT_SIZE;
	static const unsigned int BARRAGE_SHOT_DURABILITY;
public:
	ZkChrStg1Wv4(double init_pos_x, double init_pos_y);
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
	LONGLONG last_updated_clock;
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
	double arg;		//進行方向(ラジアン，右が0)
	double speed;	//弾の速度(pixel per second)
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
private:
	enum SkinID skin_id;
	static const double SUSPENSION_TIME;
	int last_arg_updated_clock;
public:
	HomingShot(
		double init_x,
		double init_y,
		double init_arg,
		double init_speed,
		unsigned int collidant_size,
		unsigned int durability,
		enum SkinID given_skin_id
	);
	void update() override;
	void draw() override;
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
};


class Emission {

};


class StraightShotEmission : public Emission {

};


class SimpleStraightShotEmission : public StraightShotEmission {
private:
	double x;
	double y;
	double arg;
	bool emit_unlimited_flag;
	unsigned int emits;
	unsigned int emit_nozzles;
	unsigned int emit_interval;
	unsigned int emit_count;
	int last_emitted_clock;
	LONGLONG last_updated_clock;
	double shot_speed;
	unsigned int shot_collidant_size;
	unsigned int shot_durability;
	enum TeamID shot_team_id;
	enum SkinID shot_skin_id;
public:
	SimpleStraightShotEmission(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		bool given_emit_unlimited_flag,
		unsigned int given_emits,
		unsigned int given_emit_nozzles,
		unsigned int given_emit_interval,
		double given_shot_speed,
		unsigned int given_shot_collidant_size,
		unsigned int given_shot_durability,
		enum TeamID given_shot_team_id,
		enum SkinID given_shot_skin_id
	);
	void update(double upd_pos_x, double upd_pos_y);
	void emit();
};


class RotatingStraightShotEmission : public StraightShotEmission {
private:
	double x;
	double y;
	double arg;
	double rotate_speed;
	bool emit_unlimited_flag;
	unsigned int emits;
	unsigned int emit_nozzles;
	unsigned int emit_interval;
	unsigned int emit_count;
	int last_emitted_clock;
	LONGLONG last_updated_clock;
	double shot_speed;
	unsigned int shot_collidant_size;
	unsigned int shot_durability;
	enum TeamID shot_team_id;
	enum SkinID shot_skin_id;
public:
	RotatingStraightShotEmission(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double given_rotate_speed,
		bool given_emit_unlimited_flag,
		unsigned int given_emits,
		unsigned int given_emit_nozzles,
		unsigned int given_emit_interval,
		double given_shot_speed,
		unsigned int given_shot_collidant_size,
		unsigned int given_shot_durability,
		enum TeamID given_shot_team_id,
		enum SkinID given_shot_skin_id
	);
	void update(double upd_pos_x, double upd_pos_y);
	void emit();
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
	double giving_speed;
	unsigned int giving_collidant_size;
	unsigned int giving_durability;
	enum SkinID giving_skin_id;
	enum TeamID team_id;
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
	void perform();
};


class RotatingRadiation : public Barrage {
protected:
	double x;
	double y;
	double rotate_speed;
	unsigned int emit_nozzles;
	RotatingRadiation(double init_pos_x, double init_pos_y, double given_rotate_speed, unsigned int given_emit_nozzles);
};


class StraightRotatingRadiation : public RotatingRadiation {
private:
	double giving_speed;
	unsigned int giving_collidant_size;
	unsigned int giving_durability;
	enum SkinID giving_skin_id;
	bool perform_completed_flag;
	double rotate_speed;
	double emit_arg;
	unsigned int emits;
	unsigned int emit_count;
	unsigned int emit_interval;
	int last_emitted_clock;
	enum TeamID team_id;
public:
	StraightRotatingRadiation(
		double init_pos_x,
		double init_pos_y,
		double init_emit_arg,
		double given_rotate_speed,
		unsigned int given_emit_nozzles,
		unsigned int given_emits,
		unsigned int given_emit_interval,
		double given_shot_speed,
		unsigned int given_collidant_size,
		unsigned int given_durability,
		enum TeamID given_team_id,
		enum SkinID given_skin_id
	);
	void update();
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
	static const int SCREEN_RESOLUTION_X = 1024;	//画面解像度X(ピクセル)
	static const int SCREEN_RESOLUTION_Y = 768;		//画面解像度Y(ピクセル)
};


class ImageHandles {
private:
	ImageHandles() {}	//唯一のコンストラクタをprivateにすることで実体の生成を禁止している
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
	static int KUJIRA;
};


class KeyPushFlags {
private:
	KeyPushFlags() {}
public:
	static void INITIALIZE();
	static char KEY_BUFFER[256];
	static bool Z;
	static bool X;
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
private:
	DebugParams() {}
public:
	static void INITIALIZE();
	static void DRAW();
	static unsigned int ACTUAL_FPS;
	static double INSTANT_FPS;
	static int SLEEP_TIME;
	static unsigned int OBJECTS;
	static double GAME_TIME;
};


class SettingParams {
private:
	SettingParams() {};
public:
	static void INITIALIZE();
	static unsigned int LIMIT_FPS;
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
