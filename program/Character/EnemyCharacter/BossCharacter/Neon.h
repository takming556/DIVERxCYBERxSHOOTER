#pragma once
#include <vector>
#include <memory>
#include <string>
#include "enum.h"
#include "Offensive/Bullet/Bullet.h"
#include "Offensive/Laser/Laser.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"

using std::vector;
using std::wstring;

class Neon : public BossCharacter {
private:
	int nm2_straight_last_generated_clock;
	double nm2_laser_arg;
	LaserID nm2_laser_id;
	int nm2_laser_notify_count;
	int nm2_laser_emit_count;
	int nm2_laser_kept_clock;
	NeonNormal2LaserStatus nm2_laser_status;

	double nm3_shot_arg;
	int nm3_last_generated_clock;

	int nm4_zk_generate_count;
	SkinID nm4_crystal_skin_id;
	int nm4_tick_count;
	int nm4_last_tick_clock;
	int nm4_last_fire_clock;

	double sp2_hail_curve_speed;
	int sp2_hail_last_generated_clock;
	double sp2_laser_arg;
	LaserID sp2_laser_id;
	int sp2_laser_notify_count;
	int sp2_laser_emit_count;
	int sp2_laser_kept_clock;
	NeonSp2LaserStatus sp2_laser_status;

	bool sp3_leidenjar_emitted_flag;
	bool sp3_leidenlaser_generated_flag;
	LaserID sp3_leidenlaser_a_id;
	LaserID sp3_leidenlaser_b_id;
	LaserID sp3_leidenlaser_c_id;

	double sp4_shuffle_arg;
	double sp4_shuffle_speed;
	vector<unsigned int> sp4_shuffle_ids;
	vector<vector<unsigned int>> sp4_shuffles_ids;
	int sp4_shuffle_tick_count;
	int sp4_shuffle_fire_count;
	int sp4_shuffle_tick_last_generated_clock;
	int sp4_shuffle_fire_last_generated_clock;
	int sp4_shuffle_down_last_changed_clock;
	int sp4_train_tick_count;
	int sp4_train_tick_last_generated_clock;
	int sp4_train_fire_last_generated_clock;
	vector<unsigned int> sp4_train_ids;
	vector<vector<unsigned int>> sp4_trains_ids;

	void nm1();
	void nm2();
	void nm3();
	void nm4();
	void sp1();
	void sp2();
	void sp3();
	void sp4();

	enum SkinID get_nm3_oval_image_handles(int count);

	static const wstring NAME;
	static const wstring SP1_NAME;
	static const wstring SP2_NAME;
	static const wstring SP3_NAME;
	static const wstring SP4_NAME;
	static const int INITIAL_POS_X;
	static const int INITIAL_POS_Y;
	static const unsigned int INITIAL_COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int NM2_STRAIGHT_NOZZLES;
	static const unsigned int NM2_STRAIGHT_INTERVAL;
	static const double NM2_STRAIGHT_SHOT_SPEED;
	static const unsigned int NM2_STRAIGHT_COLLIDANT_SIZE;
	static const double NM2_LASER_INIT_ARG;
	static const unsigned int NM2_LASER_LENGTH;
	static const unsigned int NM2_LASER_WIDTH;
	static const double NM2_LASER_DPS;
	static const unsigned int NM2_LASER_AWAIT_INTERVAL;
	static const unsigned int NM2_LASER_NOTIFY_INTERVAL;
	static const unsigned int NM2_LASER_EMIT_INTERVAL;

	static const unsigned int NM3_NOZZLES;
	static const double NM3_NOZZLES_ROTATE_SPEED;
	static const double NM3_SHOT_SPEED;
	static const unsigned int NM3_COLLIDANT_SIZE;
	static const unsigned int NM3_INTERVAL;

	static const double NM4_CRYSTAL_SPEED;
	static const unsigned int NM4_CRYSTAL_COLLIDANT_SIZE;
	static const unsigned int NM4_CRYSTAL_NOZZLES;
	static const unsigned int NM4_TICK_INTERVAL;
	static const unsigned int NM4_FIRE_INTERVAL;

	static const unsigned int SP2_HAIL_NOZZLES;
	static const unsigned int SP2_HAIL_INTERVAL;
	static const double SP2_HAIL_INIT_ARG;
	static const double SP2_HAIL_INIT_SPEED;
	static const double SP2_HAIL_INIT_CURVE_SPEED;
	static const unsigned int SP2_HAIL_COLLIDANT_SIZE;
	static const double SP2_LASER_INIT_ARG;
	static const unsigned int SP2_LASER_LENGTH;
	static const unsigned int SP2_LASER_WIDTH;
	static const double SP2_LASER_DPS;
	static const unsigned int SP2_LASER_AWAIT_INTERVAL;
	static const unsigned int SP2_LASER_NOTIFY_INTERVAL;
	static const unsigned int SP2_LASER_EMIT_INTERVAL;

	static const unsigned int SP4_SHUFFLE_CARD_NUM;
	static const unsigned int SP4_SHUFFLE_CARD_DISTANCE;
	static const unsigned int SP4_SHUFFLE_TICK_INTERVAL;
	static const unsigned int SP4_SHUFFLE_FIRE_INTERVAL;
	static const unsigned int SP4_SHUFFLE_TICK_COUNT_MAX;
	static const double SP4_SHUFFLE_INIT_ARG;
	static const double SP4_SHUFFLE_INIT_SPEED;
	static const double SP4_SHUFFLE_DOWN_ARG;
	static const double SP4_SHUFFLE_DOWN_SPEED;
	static const double SP4_SHUFFLE_EXIT_ARG;
	static const double SP4_SHUFFLE_EXIT_SPEED;
	static const unsigned int SP4_SHUFFLE_COLLIDANT_SIZE;
	static const unsigned int SP4_SHUFFLE_DOWN_CRITERION_X;
	static const unsigned int SP4_SHUFFLE_EXIT_CRITERION_Y;

	static const double SP4_TRAIN_INIT_ARG;
	static const double SP4_TRAIN_INIT_SPEED;
	static const unsigned int SP4_TRAIN_COLLIDANT_SIZE;
	static const unsigned int SP4_TRAIN_TICK_INTERVAL;
	static const unsigned int SP4_TRAIN_FIRE_INTERVAL;
	static const unsigned int SP4_TRAIN_TICK_COUNT_MAX;

	static const unsigned int INITIAL_HP;
	static const double NM1_ACTIVATE_HP_RATIO;
	static const double SP1_ACTIVATE_HP_RATIO;
	static const double NM2_ACTIVATE_HP_RATIO;
	static const double SP2_ACTIVATE_HP_RATIO;
	static const double NM3_ACTIVATE_HP_RATIO;
	static const double SP3_ACTIVATE_HP_RATIO;
	static const double NM4_ACTIVATE_HP_RATIO;
	static const double SP4_ACTIVATE_HP_RATIO;

public:
	static NeonStatus STATUS;
	Neon();
	void update() override;
	void draw() override;
	static const unsigned int CRUSH_BONUS;
	static const unsigned int SP1_ACCOMPLISH_BONUS;
	static const unsigned int SP2_ACCOMPLISH_BONUS;
	static const unsigned int SP3_ACCOMPLISH_BONUS;
	static const unsigned int SP4_ACCOMPLISH_BONUS;
};