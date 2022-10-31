#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <array>
#include "DxLib.h"
#include "enum.h"

using std::string;
using std::vector;
using std::map;
using std::array;
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
class NicknameInput;



//クラスの定義

class AppSession {
private:
	Scene now_scene;
	unique_ptr<GameConductor> game_conductor;
	unique_ptr<NicknameInput> nickname_input;
	LONGLONG last_screenflipped_clock;
	int clock_keeper_for_measure_fps;
	unsigned int flip_count;
public:
	AppSession();
	void update();
	void get_keyinput_state();
	void respond_to_keyinput();
	int send_sql(string nickname);
};


class GameConductor {
private:
	Stage now_stage;
	unique_ptr<Scoreboard> scoreboard;
	unique_ptr<Stage1> stage1;
	int last_updated_clock;
	double game_time;
	static const unsigned int SURVIVAL_BONUS;
public:
	static unsigned int SCORE;
	static bool SURVIVAL_BONUS_ENABLE_FLAG;
	static bool GAMEOVER_FLAG;
	static bool GAMECLEAR_FLAG;
	static void INITIALIZE();
	GameConductor();
	void update();
	void draw_score();
	void draw_my_hp();
};


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
	double shot_frequency;							//連射速度
	double move_speed;								//移動速度(pixel per second)
	int last_launch_ticked_clock;
	//LONGLONG last_updated_clock;
	MyCharacter(string character_name);
	static const int INITIAL_POSITION_X;
	static const int INITIAL_POSITION_Y;
	static const unsigned int COLLIDANT_SIZE;
	static const double SLOW_MOVE_SPEED_EXTRATE;
public:
	static bool SLOWMOVE_FLAG;
	unsigned int life;
	virtual ~MyCharacter() {}
	virtual void draw() = 0;
	void update();
	void respond_to_keyinput();
	void move_upward();
	void move_downward();
	void move_rightward();
	void move_leftward();
	void move_uprightward();
	void move_downrightward();
	void move_upleftward();
	void move_downleftward();
	void regulate_position();
	void launch();
	void damaged();
	void draw_life();
	bool is_collided_with_enemy_offensives();
	bool is_dead();
};


class IchigoChan : public MyCharacter {
private:
	static const string CHARACTER_NAME;
	static const double DRAW_EXTRATE;
public:
	IchigoChan();
	void draw() override;
};


class EnemyCharacter : virtual public Character{
protected:
	unsigned int hp;
	EnemyCharacter(unsigned int init_hp);
public:
	virtual ~EnemyCharacter() {}
	virtual void update() = 0;
	virtual void draw() = 0;
	void damaged();
	void draw_HP();
	bool is_collided_with_my_offensives();
	bool is_dead();
};


class BossCharacter : virtual public EnemyCharacter {
protected:
	string name;
	BossCharacter(string character_name);
};


class Mofu : public BossCharacter {
private:
	MofuStatus status;
	int last_status_changed_clock;
	int last_normal1_performed_clock;
	int last_sp1_performed_clock;
	int last_normal2_lines_performed_clock;
	int last_sp2_swaying_performed_clock;
	int last_sp2_swaying_tick_fired_clock;
	int last_sp2_straight_performed_clock;
	int last_normal3_tickked_clock;
	int last_normal3_barraged_clock;
	unsigned int sp2_swaying_tick_count;
	unique_ptr<SimpleStraightShotEmission> normal2_barrage;
	bool sp2_swaying_tick_firing_flag;
	double arg_sp2_swaying_toward_mychr;
	MofuNormal3Mode normal3_mode;
	unsigned int normal3_tick_count;

	static const string CHARACTER_NAME;
	static const int INITIAL_POS_X;
	static const int INITIAL_POS_Y;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int INITIAL_HP;
	static const double SP1_ACTIVATE_HP_RATIO;
	static const double SP1_TERMINATE_HP_RATIO;
	static const double SP2_ACTIVATE_HP_RATIO;
	static const double SP2_TERMINATE_HP_RATIO;
	static const double SP3_ACTIVATE_HP_RATIO;
	static const double SP3_TERMINATE_HP_RATIO;

	static const unsigned int NORMAL1_AMOUNT;
	static const unsigned int NORMAL1_INTERVAL;
	static const unsigned int NORMAL1_SCATTERING_Y;
	static const double NORMAL1_SHOT_SPEED;
	static const unsigned int NORMAL1_SHOT_COLLIDANT_SIZE;
	static const unsigned int NORMAL1_SHOT_DURABILITY;

	static const unsigned int SP1_AMOUNT;
	static const unsigned int SP1_INTERVAL;
	static const unsigned int SP1_SCATTERING_Y;

	static const unsigned int NORMAL2_BARRAGE_NOZZLES;
	static const unsigned int NORMAL2_BARRAGE_INTERVAL;
	static const double NORMAL2_BARRAGE_SPEED;
	static const unsigned int NORMAL2_BARRAGE_COLLIDANT_SIZE;
	static const unsigned int NORMAL2_BARRAGE_DURABILITY;
	static const double NORMAL2_BARRAGE_DRAW_EXTRATE;
	static const unsigned int NORMAL2_LINES_INTERVAL;
	static const double NORMAL2_LINES_SPEED;
	static const unsigned int NORMAL2_LINES_COLLIDANT_SIZE;
	static const unsigned int NORMAL2_LINES_DURABILITY;
	static const double NORMAL2_LINES_DRAW_EXTRATE;

	static const unsigned int SP2_SWAYING_INTERVAL;
	static const unsigned int SP2_SWAYING_TICK_INTERVAL;
	static const unsigned int SP2_SWAYING_TICKS;
	static const double SP2_SWAYING_MOVESPEED;
	static const unsigned int SP2_SWAYING_COLLIDANT_SIZE;
	static const unsigned int SP2_SWAYING_DURABILITY;
	static const double SP2_SWAYING_INTENSITY;
	static const double SP2_SWAYING_FREQUENCY;
	static const unsigned int SP2_STRAIGHT_INTERVAL;
	static const double SP2_STRAIGHT_MOVESPEED;
	static const unsigned int SP2_STRAIGHT_COLLIDANT_SIZE;
	static const unsigned int SP2_STRAIGHT_DURABILITY;

	static const unsigned int NORMAL3_RIGHTROLL_NOZZLES;
	static const unsigned int NORMAL3_LEFTROLL_NOZZLES;
	static const double NORMAL3_RIGHTROLL_MOVESPEED;
	static const double NORMAL3_LEFTROLL_MOVESPEED;
	static const double NORMAL3_RIGHTROLL_CURVESPEED;
	static const double NORMAL3_LEFTROLL_CURVESPEED;
	static const unsigned int NORMAL3_RIGHTROLL_COLLIDANT_SIZE;
	static const unsigned int NORMAL3_LEFTROLL_COLLIDANT_SIZE;
	static const unsigned int NORMAL3_RIGHTROLL_DURABILITY;
	static const unsigned int NORMAL3_LEFTROLL_DURABILITY;
	static const unsigned int NORMAL3_BARRAGE_INTERVAL;
	static const unsigned int NORMAL3_TICK_INTERVAL;
	static const unsigned int NORMAL3_TICKS;

public:
	Mofu();
	void update() override;
	void draw() override;
	static const unsigned int SP1_ACCOMPLISH_BONUS;
	static const unsigned int SP2_ACCOMPLISH_BONUS;
	static const unsigned int SP3_ACCOMPLISH_BONUS;
	static const unsigned int CRUSH_BONUS;
};


class ZakoCharacter : virtual public EnemyCharacter {
protected:
	ZakoCharacter() {}
public:
	static const unsigned int CRUSH_BONUS;
};


class ZkChrStg1Wv1 : public ZakoCharacter {
private:
	double speed;
	double arg;
	//LONGLONG last_updated_clock;
	int last_shot_completed_clock;
	int last_tick_fired_clock;
	unsigned int tick_count;
	unsigned int shot_count;

	static const unsigned int TICKS;
	static const unsigned int SHOTS;
	static const unsigned int TICK_INTERVAL;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int SHOT_DURABILITY;
	//static const double SHOT_DRAW_EXTRATE;
public:
	ZkChrStg1Wv1(int init_pos_x, int init_pos_y, double init_arg, double init_speed);
	void update() override;
	void draw() override;
};


class ZkChrStg1Wv2 : public ZakoCharacter {
private:
	double speed;
	double arg;
	//LONGLONG last_updated_clock;
	unique_ptr<RotatingStraightShotEmission> barrage;

	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int BARRAGE_EMIT_NOZZLES;
	static const unsigned int BARRAGE_EMITS;
	static const unsigned int BARRAGE_EMIT_INTERVAL;
	static const double BARRAGE_INIT_ARG;
	static const double BARRAGE_SHOT_SPEED;
	static const unsigned int BARRAGE_SHOT_COLLIDANT_SIZE;
	static const unsigned int BARRAGE_SHOT_DURABILITY;
	//static const double BARRAGE_SHOT_DRAW_EXTRATE;
public:
	ZkChrStg1Wv2(double init_pos_x, double init_pos_y, double init_arg, double init_speed, double barrage_rotate_speed);
	void update() override;
	void draw() override;
};


class ZkChrStg1Wv3S : public ZakoCharacter { //クジラ
private:
	//double speed;
	//double arg;
	//LONGLONG last_updated_clock;
	unsigned int tick_count;
	//unsigned int shot_count;
	int last_shot_completed_clock;
	int last_tick_fired_clock;

	static const unsigned int TICKS;
	//static const unsigned int SHOTS;
	static const unsigned int TICK_INTERVAL;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int SHOT_DURABILITY;
	//static const double SHOT_DRAW_EXTRATE;
public:
	ZkChrStg1Wv3S(int init_pos_x, int init_pos_y);
	void update() override;
	void draw() override;

};


class ZkChrStg1Wv3L : public ZakoCharacter { //クラゲ
private:
	//double speed;
	//double arg;
	//LONGLONG last_updated_clock;
	unique_ptr<RotatingStraightShotEmission> barrage;
	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int BARRAGE_EMIT_NOZZLES;
	//static const unsigned int BARRAGE_EMITS;
	static const unsigned int BARRAGE_EMIT_INTERVAL;
	static const double BARRAGE_INIT_ARG;
	static const double BARRAGE_SHOT_SPEED;
	static const unsigned int BARRAGE_SHOT_COLLIDANT_SIZE;
	static const unsigned int BARRAGE_SHOT_DURABILITY;
	//static const double BARRAGE_SHOT_DRAW_EXTRATE;
public:
	ZkChrStg1Wv3L(double init_pos_x, double init_pos_y, double barrage_rotate_speed);
	void update() override;
	void draw() override;

};


class ZkChrStg1Wv4 : public ZakoCharacter { //クジラ
private:
	//double speed;
	//double arg;
	//LONGLONG last_updated_clock;
	unique_ptr<SimpleStraightShotEmission> barrage;
	int last_lines_tick_fired_clock;
	int last_lines_shot_completed_clock;
	unsigned int tick_count;
	unsigned int shot_count;

	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int LINES_TICKS;
	static const unsigned int LINES_SHOTS;
	static const unsigned int LINES_TICK_INTERVAL;
	static const unsigned int LINES_SHOT_INTERVAL;
	static const double LINES_SHOT_SPEED;
	static const unsigned int LINES_SHOT_COLLIDANT_SIZE;
	static const unsigned int LINES_SHOT_DURABILITY;
	static const double LINES_SHOT_DRAW_EXTRATE;

	static const unsigned int BARRAGE_EMIT_NOZZLES;
	static const unsigned int BARRAGE_EMITS;
	static const unsigned int BARRAGE_EMIT_INTERVAL;
	static const double BARRAGE_INIT_ARG;
	static const double BARRAGE_SHOT_SPEED;
	static const unsigned int BARRAGE_SHOT_COLLIDANT_SIZE;
	static const unsigned int BARRAGE_SHOT_DURABILITY;
	static const double BARRAGE_SHOT_DRAW_EXTRATE;
public:
	ZkChrStg1Wv4(double init_pos_x, double init_pos_y);
	void update() override;
	void draw() override;


};


class ZkChrStg1Wv5S : public ZakoCharacter {
private:
	//double speed;
	//double arg;
	//LONGLONG last_updated_clock;
	unique_ptr<RotatingStraightShotEmission> barrage;

	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int BARRAGE_EMIT_NOZZLES;
	//static const unsigned int BARRAGE_EMITS;
	static const unsigned int BARRAGE_EMIT_INTERVAL;
	static const double BARRAGE_INIT_ARG;
	static const double BARRAGE_SHOT_SPEED;
	static const unsigned int BARRAGE_SHOT_COLLIDANT_SIZE;
	static const unsigned int BARRAGE_SHOT_DURABILITY;
	//static const double BARRAGE_SHOT_DRAW_EXTRATE;
public:
	ZkChrStg1Wv5S(double init_pos_x, double init_pos_y, double barrage_rotate_speed);
	void update() override;
	void draw() override;
};


class ZkChrStg1Wv5L : public ZakoCharacter {
private:
	//double speed;
	//double arg;
	//LONGLONG last_updated_clock;
	int last_tick_fired_clock;
	int last_shot_completed_clock;
	unsigned int tick_count;
	//unsigned int shot_count;

	static const unsigned int TICKS;
	//static const unsigned int SHOTS;
	static const unsigned int TICK_INTERVAL;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int SHOT_DURABILITY;
	//static const double SHOT_DRAW_EXTRATE;
public:
	ZkChrStg1Wv5L(double init_pos_x, double init_pos_y);
	void update() override;
	void draw() override;
};


class ZkChrStg1BsSp3 : public ZakoCharacter {
private:
	int last_barraged_clock;

	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;
	static const unsigned int NOZZLES;
	static const unsigned int INTERVAL;

public:
	ZkChrStg1BsSp3(double init_pos_x, double init_pos_y);
	void update() override;
	void draw() override;
};


class Offensive {
protected:
	unsigned int durability;
	LONGLONG last_updated_clock;
	Offensive(double init_pos_x, double init_pos_y, unique_ptr<CollideRealm> given_collidant, unsigned int init_durability);
	Offensive() {}
public:
	unique_ptr<CollideRealm> collidant;
	unique_ptr<InFieldPosition> position;
	bool is_collided_with_my_character();
	bool is_collided_with_enemy_characters();
	bool is_broken();
	void damaged();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void draw_durability() = 0;
	virtual ~Offensive() {}
};


class Bullet : virtual public Offensive {
protected:
	double arg;		//進行方向(ラジアン，右が0)
	double speed;	//弾の速度(pixel per second)
public:
	Bullet(double init_arg, double init_speed);
	Bullet() {}
	void draw_durability() override;
};


class StraightShot : virtual public Bullet {
protected:
	enum SkinID skin_id;
public:
	StraightShot(
		double init_pos_x, 
		double init_pos_y, 
		double init_arg, 
		double init_speed, 
		unsigned int collidant_size, 
		unsigned int durability, 
		enum SkinID given_skin_id
	);
	StraightShot(enum SkinID given_skin_id);
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
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		unsigned int collidant_size,
		unsigned int durability,
		enum SkinID skin_id
	);
	void update() override;
	void draw() override;
};


class SwayingShot : public Bullet {
private:
	SkinID skin_id;
	double sway_intensity;
	double sway_frequency;
	double initial_arg;
	double theta;
public:
	SwayingShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		double sway_intensity,
		double sway_frequency,
		unsigned int collidant_size,
		unsigned int durability,
		enum SkinID skin_id
	);
	void update() override;
	void draw() override;
};


class CurvingShot : public Bullet {
protected:
	enum SkinID skin_id;
	double curve_speed;
public:
	CurvingShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		double curve_speed,
		unsigned int collidant_size,
		unsigned int durability,
		enum SkinID skin_id
	);
	void update() override;
	void draw() override;
};


class ParabolicShot : public Bullet {
	static double flight_accel_constant;
	static double flight_accel_arg;
};


class FloatingTerrorShot : public StraightShot {
private:
	enum FloatingTerrorShotMode status;
	static const unsigned int MODE_SWITCH_Y;
	static const double FLOATING_SPEED;
	static const double TERROR_SPEED;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int DURABILITY;

public:
	FloatingTerrorShot(double init_pos_x, double init_pos_y);
	void update() override;
};


class KurageAmeShot : public Bullet {
private:
	KurageAmeShotMode mode;
	int generated_clock;
	static const double GRAVITY_CONSTANT;
	static const unsigned int WAITTIME_UNTIL_MODECHANGE;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int DURABILITY;
	static const double DRAW_EXTRATE;
public:
	KurageAmeShot(double init_pos_x, double init_pos_y);
	void update() override;
	void draw() override;
};


class GravityShot : public Bullet {

};

class Laser : public Offensive {

};


class BendingLaser : public Laser {

};


class Barrage {
};


class Emission : public Barrage {

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
	void emit();
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
	static const int DRAW_POS_OFFSET_X;
	static const int DRAW_POS_OFFSET_Y;
public:
	InFieldPosition(double init_x, double init_y);
	Position get_draw_position();
	static Position GET_DRAW_POSITION(double given_infieldpos_x, double given_infieldpos_y);
	static const double MIN_MOVABLE_BOUNDARY_X;
	static const double MIN_MOVABLE_BOUNDARY_Y;
	static const double MAX_MOVABLE_BOUNDARY_X;
	static const double MAX_MOVABLE_BOUNDARY_Y;
	static const double MIN_EXISTENCE_BOUNDARY_X;
	static const double MIN_EXISTENCE_BOUNDARY_Y;
	static const double MAX_EXISTENCE_BOUNDARY_X;
	static const double MAX_EXISTENCE_BOUNDARY_Y;
	static void DRAW_MOVABLE_BOUNDARY();
	static void DRAW_EXISTENCE_BOUNDARY();
};


class Screen {
public:
	static const int SCREEN_RESOLUTION_X = 1024;	//画面解像度X(ピクセル)
	static const int SCREEN_RESOLUTION_Y = 768;		//画面解像度Y(ピクセル)
};


class Dial {
private:
	unsigned int position;
	static const string ENABLED_CHARACTERS;
	static const unsigned int INITIAL_POSITION;
public:
	Dial();
	void respond_to_keyinput();
	void uproll();
	void downroll();
	void draw_character(int draw_x, int draw_y);
	void draw_cursor(int draw_x, int draw_y);
	string get();
};


class NicknameInput {
private:
	unsigned int operating_digit;
	array<Dial, 16> dials;
public:
	static bool CONFIRMING_FLAG;
	bool determined_flag;
	NicknameInput();
	static void INITIALIZE();
	void update();
	void respond_to_keyinput();
	void digitslide_left();
	void digitslide_right();
	void draw();
	string get();
};


class ImageHandles {
private:
	ImageHandles() {}	//唯一のコンストラクタをprivateにすることで実体の生成を禁止している
public:
	static void LOAD_ALL_IMAGE();
	
	static int FULLBODY_ICHIGOCHAN_NORMAL;
	static int FULLBODY_ICHIGOCHAN_AVATAR;
	static int FULLBODY_MOFU;
	static int FULLBODY_NEON;
	static int FULLBODY_TOROI;

	static int SPRITE_ICHIGOCHAN;
	static int SPRITE_MOFU;
	static int SPRITE_NEON;
	static int SPRITE_TOROI;
	static int SPRITE_ZKCHR_KURAGE;
	static int SPRITE_ZKCHR_KUJIRA;
	static int SPRITE_ZKCHR_GUARDIAN_DWARF;
	static int SPRITE_ZKCHR_ATTACKER_NIGHT;
	static int SPRITE_ZKCHR_GOD_OF_ABSOLUTE_LOVE;
	static int SPRITE_ZKCHR_GOD_OF_MISSING_LOVE;

	static int ANCHOR_BLACK;
	static int ANCHOR_GRAY;
	static int ANCHOR_SILVER;
	static int ANCHOR_WHITE;
	static int ANCHOR_BLUE;
	static int ANCHOR_NAVY;
	static int ANCHOR_TEAL;
	static int ANCHOR_GREEN;
	static int ANCHOR_LIME;
	static int ANCHOR_AQUA;
	static int ANCHOR_YELLOW;
	static int ANCHOR_RED;
	static int ANCHOR_FUCHSIA;
	static int ANCHOR_OLIVE;
	static int ANCHOR_PURPLE;
	static int ANCHOR_MAROON;

	static int BUBBLE_BLACK;
	static int BUBBLE_GRAY;
	static int BUBBLE_SILVER;
	static int BUBBLE_WHITE;
	static int BUBBLE_BLUE;
	static int BUBBLE_NAVY;
	static int BUBBLE_TEAL;
	static int BUBBLE_GREEN;
	static int BUBBLE_LIME;
	static int BUBBLE_AQUA;
	static int BUBBLE_YELLOW;
	static int BUBBLE_RED;
	static int BUBBLE_FUCHSIA;
	static int BUBBLE_OLIVE;
	static int BUBBLE_PURPLE;
	static int BUBBLE_MAROON;

	static int CRYSTAL_BLACK;
	static int CRYSTAL_GRAY;
	static int CRYSTAL_SILVER;
	static int CRYSTAL_WHITE;
	static int CRYSTAL_BLUE;
	static int CRYSTAL_NAVY;
	static int CRYSTAL_TEAL;
	static int CRYSTAL_GREEN;
	static int CRYSTAL_LIME;
	static int CRYSTAL_AQUA;
	static int CRYSTAL_YELLOW;
	static int CRYSTAL_RED;
	static int CRYSTAL_FUCHSIA;
	static int CRYSTAL_OLIVE;
	static int CRYSTAL_PURPLE;
	static int CRYSTAL_MAROON;

	static int LOGO;
	static int LOGO_NONSILHOUETTE;
	static int ICHIGOCHAN_CONCEPTUAL;
	static int SCREEN_BACKGROUND;
	static int SCREEN_BACKGROUND_CROPPED;
	static int FIELD_BACKGROUND_STAGE1;
	static int DIGIT_CURSOR;


	static int FIELD_BACKGROUND;
	static int TEST_SHOOTER;
	static int BLUE_MARBLE;
	static int RED_MARBLE;
	static int ORANGE_TRIANGLE;
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


class SoundHandles {
private:
	SoundHandles() {}
public:
	static void LOAD_ALL_SOUNDS();
	static int CURSORMOVE;
	static int FORWARD;
	static int BACKWARD;
	static int MYSHOT;
	static int ENEMYSHOT;
	static int MYHIT;
	static int ENEMYHIT;
	static int ZAKOCRASH;
	static int BOSSCRASH;
};


class FontHandles {
private:
	FontHandles() {}
public:
	static void LOAD_ALL_FONT();
	static int DSEG14;
	static int HGP_SOUEIKAKU_GOTHIC_UB_64;
	static int HGP_SOUEIKAKU_GOTHIC_UB_48;
	static int HGP_SOUEIKAKU_GOTHIC_UB_32;
	static int HGP_SOUEIKAKU_GOTHIC_UB_24;
	static int HGP_SOUEIKAKU_GOTHIC_UB_16;
	static int CONSOLAS_64;
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
	static bool F3;
	static bool ENTER;
};


class Colors {
private:
	Colors() {}
public:
	static void INITIALIZE();
	static int BLACK;
	static int RED;
	static int GREEN;
	static int BLUE;
	static int YELLOW;
	static int CYAN;
	static int MAZENTA;
	static int WHITE;
};


class DebugParams {
private:
	DebugParams() {}
public:
	static void INITIALIZE();
	static void DRAW();
	static bool DEBUG_FLAG;
	static unsigned int ACTUAL_FPS;
	static double INSTANT_FPS;
	static int SLEEP_TIME;
	static unsigned int OBJECTS;
	static double GAME_TIME;
	static double MY_CHARACTER_INFIELD_X;
	static double MY_CHARACTER_INFIELD_Y;
	static double MY_CHARACTER_DRAW_X;
	static double MY_CHARACTER_DRAW_Y;
};


class SettingParams {
private:
	SettingParams() {};
public:
	static void INITIALIZE();
	static unsigned int LIMIT_FPS;
};


class SQLConfig {
private:
	SQLConfig() {}
public:
	static void INITIALIZE();

	static const string FILENAME_HOST;
	static const string FILENAME_USER;
	static const string FILENAME_PASSWORD;
	static const string FILENAME_DATABASE;
	static const string FILENAME_LOG;
	static const string FILENAME_DEVICE;

	static string HOST;
	static string USER;
	static string PASSWORD;
	static string DATABASE;
	static string DEVICE;
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



//class SimpleRadiation : public Barrage {
//protected:
//	const double x;
//	const double y;
//	const unsigned int amount;
//	SimpleRadiation(double emit_pos_x, double emit_pos_y, unsigned int emit_amount);
//};
//
//
//class StraightSimpleRadiation : public SimpleRadiation {
//protected:
//	double giving_speed;
//	unsigned int giving_collidant_size;
//	unsigned int giving_durability;
//	enum SkinID giving_skin_id;
//	enum TeamID team_id;
//public:
//	StraightSimpleRadiation(
//		double emit_pos_x,
//		double emit_pos_y,
//		unsigned int emit_amount,
//		double given_speed,
//		unsigned int given_collidant_size,
//		unsigned int given_durability,
//		enum TeamID given_team_id,
//		enum SkinID given_skin_id
//	);
//	void perform();
//};
//
//
//class RotatingRadiation : public Barrage {
//protected:
//	double x;
//	double y;
//	double rotate_speed;
//	unsigned int emit_nozzles;
//	RotatingRadiation(double init_pos_x, double init_pos_y, double given_rotate_speed, unsigned int given_emit_nozzles);
//};
//
//
//class StraightRotatingRadiation : public RotatingRadiation {
//private:
//	double giving_speed;
//	unsigned int giving_collidant_size;
//	unsigned int giving_durability;
//	enum SkinID giving_skin_id;
//	bool perform_completed_flag;
//	double rotate_speed;
//	double emit_arg;
//	unsigned int emits;
//	unsigned int emit_count;
//	unsigned int emit_interval;
//	int last_emitted_clock;
//	enum TeamID team_id;
//public:
//	StraightRotatingRadiation(
//		double init_pos_x,
//		double init_pos_y,
//		double init_emit_arg,
//		double given_rotate_speed,
//		unsigned int given_emit_nozzles,
//		unsigned int given_emits,
//		unsigned int given_emit_interval,
//		double given_shot_speed,
//		unsigned int given_collidant_size,
//		unsigned int given_durability,
//		enum TeamID given_team_id,
//		enum SkinID given_skin_id
//	);
//	void update();
//};
