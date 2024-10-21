#pragma once
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include "Barrage/Emission/StraightShotEmission/RotatingStraightShotEmission.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "Offensive/Bullet/Bullet.h"
#include "Offensive/Laser/Laser.h"
#include "enum.h"

using std::vector;
using std::unique_ptr;
using std::wstring;
using std::pair;

class Toroi : public BossCharacter {
private:
	int kept_clock;

	int nm1_last_generated_clock;

	ToroiNM2Mode nm2_mode;
	ToroiNM4ColorFlag nm4_color_flag;
	double nm2_laser_arg;
	int nm2_laser_width;
	int nm2_laser_kept_clock;
	int nm2_laser_notify_count;
	int nm2_laser_laps;
	double nm2_notifyarg1;
	double nm2_notifyarg2;
	int nm2_lasercount;
	int nm2_laser_shot_count;
	int nm2_random_num;
	double nm2_shot_arg_yellow;
	LaserID nm2_laser_id[45];

	ToroiNm3Status nm3_status;
	vector<BulletID> nm3_dvd_shot_ids;
	int nm3_parasol_rain_last_emitted_clock;

	int nm4_last_generated_clock;

	ToroiSP1Mode sp1_mode;
	int sp1_last_questioned_clock;
	int sp1_trick_last_started_clock;
	int sp1_trick_last_emitted_clock;
	double sp1_trick_nozzle_rotate_arg;
	int sp1_treat_last_started_clock;
	int sp1_treat_last_threw_clock;
	int sp1_trap_last_started_clock;
	unsigned char sp1_trap_phase;
	int sp1_trap_last_across_started_clock;
	int sp1_trap_last_shot_clock;

	int sp2_last_surrounded_clock;
	int sp2_last_sting_clock;
	int sp2_last_rain_clock;

	ToroiSP3Status sp3_status;
	int sp3_last_step_advanced_clock;
	LaserID sp3_step1_slash_laser_id;
	vector<LaserID> sp3_step1_besiege_laser_ids;
	vector<BulletID> sp3_step2_ghost_ids;
	int sp3_step2_last_ghost_emitted_clock;
	LaserID sp3_step3_slash_laser_id;
	vector<LaserID> sp3_step3_besiege_laser_ids;
	LaserID sp3_step4_slash_laser_id;
	vector<BulletID> sp3_step5_ghost_ids;
	int sp3_step5_last_ghost_emitted_clock;

	bool sp4_started_flag;
	int sp4_started_clock;
	bool sp4_knife_emitted_flag;
	BulletID sp4_knife_shot_id;
	bool sp4_blood_splashed_flag;
	int sp4_blood_splashed_clock;

	int sp5_rain_last_generated_clock;
	double sp5_heart_x;
	double sp5_heart_y;
	double sp5_heart_arg_toward_mychr;
	ToroiSP5HeartStatus sp5_heart_status;
	int sp5_heart_last_generated_clock;
	

	ToroiSP6Mode sp6_mode;
	vector<unique_ptr<RotatingStraightShotEmission>> sp6_ran_nozzles;
	double sp6_ran_nozzle_radius;
	int sp6_ran_count;
	int sp6_ru_inital_started_clock;
	int sp6_ru_started_clock;
	int sp6_ru_potato_last_generated_clock;
	int sp6_ru_tomato_tick_last_generated_clock;
	int sp6_ru_tomato_fire_last_generated_clock;
	int sp6_ru_tomato_tick_count;

	bool sp7_started_flag;
	int sp7_started_clock;
	int sp7_last_dagger_emitted_clock;
	vector<pair<double, bool>> sp7_dial_aperture_args;
	bool sp7_dial_generated_flag;
	//vector<bool> sp7_dial_unlocked_flags;
	bool sp7_all_dials_unlocked_flag;
	unsigned int sp7_now_rolling_dial_num;
	vector<vector<double>> sp7_dials_shot_args;
	vector<vector<BulletID>> sp7_dials_shot_ids;
	LONGLONG sp7_dial_arg_last_updated_clock;
	int sp7_laser_prenotify_last_started_clock;
	//bool sp7_laser_prenotify_started_flag;
	int sp7_laser_prenotify_last_finished_clock;
	bool sp7_laser_prenotify_finished_flag;
	int sp7_laser_emit_last_started_clock;
	bool sp7_laser_emit_started_flag;
	int sp7_laser_emit_last_finished_clock;
	bool sp7_laser_emit_finished_flag;
	vector<LaserID> sp7_laser_ids;
	bool sp7_dials_shots_scattered_flag;

	void nm1();
	void nm2();
	void nm3();
	void nm4();
	void sp1();
	void sp2();
	void sp3();
	void sp4();
	void sp5();
	void sp6();
	void sp7();
	enum SkinID get_sp5_heart_random_image_handles();

	static const wstring NAME;
	static const wstring SP1_NAME;
	static const wstring SP2_NAME;
	static const wstring SP3_NAME;
	static const wstring SP4_NAME;
	static const wstring SP5_NAME;
	static const wstring SP6_NAME;
	static const wstring SP7_NAME;
	static const int INITIAL_POS_X;
	static const int INITIAL_POS_Y;
	static const unsigned int INITIAL_COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int NM1_INTERVAL;

	static const unsigned int NM2_LASER_LENGTH;
	static const unsigned int NM2_SHOT_LASER_WIDTH;
	static const unsigned int NM2_NOTIFY_LASER_WIDTH;
	static const unsigned int LASERNOZZLES;

	static const unsigned int NM3_PARASOL_RAIN_INTERVAL;
	static const unsigned int NM3_PARASOL_RAIN_LANE_COUNT;
	static const unsigned int NM3_PARASOL_RAIN_THROW_SPEED;
	static const double NM3_PARASOL_RAIN_GRAVITY_ACCEL;
	static const unsigned int NM3_PARASOL_RAIN_COLLIDANT_SIZE;

	static const unsigned int NM4_BIG_NOZZLES;
	static const unsigned int NM4_INTERVAL;
	static const double NM4_SPEED;
	static const unsigned int NM4_COLLIDANT_SIZE_BIG;
	static const unsigned int NM4_COLLIDANT_SIZE_SMALL;

	static const int SP1_THINKING_TIME_LENGTH;
	static const unsigned int SP1_TRICK_DURATION;
	static const unsigned int SP1_TRICK_NOZZLES;
	static const unsigned int SP1_TRICK_NOZZLE_RADIUS;
	static const double SP1_TRICK_NOZZLE_ROTATE_SPEED;
	static const unsigned int SP1_TRICK_SHOT_INTERVAL;
	static const unsigned int SP1_TRICK_SHOT_SPEED;
	static const unsigned int SP1_TRICK_SHOT_COLLIDANT_SIZE;
	static const unsigned int SP1_TREAT_DURATION;
	static const unsigned int SP1_TREAT_THROW_AMOUNT;
	static const unsigned int SP1_TREAT_THROW_INTERVAL;
	static const unsigned int SP1_TRAP_SHOT_INTERVAL;					// [ミリ秒]
	static const unsigned int SP1_TRAP_SHOT_COLLIDANT_SIZE;
	static const unsigned int SP1_TRAP_HORIZONTAL_ACROSS_DURATION;		// [ミリ秒]
	static const unsigned int SP1_TRAP_VERTICAL_ACROSS_DURATION;		// [ミリ秒]
	static const unsigned int SP1_TRAP_ACROSS_SPEED;					// [ピクセル／秒]
	static const unsigned char SP1_TRAP_ACROSS_LANES;

	static const double SP2_SURROUNDED_LEFT_ARG;
	static const double SP2_SURROUNDED_RIGHT_ARG;
	static const double SP2_SURROUNDED_SPEED;
	static const double SP2_SURROUNDED_LEFT_CURVE_SPEED;
	static const double SP2_SURROUNDED_RIGHT_CURVE_SPEED;
	static const unsigned int SP2_SURROUNDED_COLLIDANT_SIZE;
	static const unsigned int SP2_SURROUNDED_INTERVAL;
	static const double SP2_STING_GENERATED_TOP_Y;
	static const double SP2_STING_GENERATED_BOTTOM_Y;
	static const double SP2_STING_GENERATED_LEFT_X;
	static const double SP2_STING_GENERATED_RIGHT_X;
	static const double SP2_STING_SPEED;
	static const unsigned int SP2_STING_COLLIDANT_SIZE;
	static const unsigned int SP2_STING_INTERVAL;
	static const double SP2_RAIN_LEFT_POS_X;
	static const double SP2_RAIN_RIGHT_POS_X;
	static const double SP2_RAIN_POS_Y;
	static const double SP2_RAIN_ACCEL;
	static const double SP2_RAIN_ACCEL_ARG;
	static const unsigned int SP2_RAIN_COLLIDANT_SIZE;
	static const unsigned int SP2_RAIN_NOZZLES;
	static const unsigned int SP2_RAIN_INTERVAL;

	static const unsigned int SP3_GHOSTS_EMIT_INTERVAL;

	static const unsigned int SP4_INITIAL_WAIT;
	static const double SP4_KNIFE_INITIAL_POS_X;
	static const double SP4_KNIFE_INITIAL_POS_Y;
	static const double SP4_KNIFE_SPEED;
	static const unsigned int SP4_KNIFE_COLLIDANT_SIZE;
	static const unsigned int SP4_BLOOD_SPLASH_AMOUNT;
	static const double SP4_BLOOD_SPLASH_GRAVITY_ACCEL;
	static const unsigned int SP4_BLOOD_SPLASH_COLLIDANT_SIZE;
	static const unsigned int SP4_BLOOD_SPLASH_AFTER_WAIT;


	static const unsigned int SP5_RAIN_INTERVAL;						// 躁鬱雨の生成間隔(躁鬱共通)
	static const double SP5_RAIN_SOU_GENERATED_Y;						// 躁
	static const double SP5_RAIN_UTU_GENERATED_Y;						// 鬱
	static const unsigned int SP5_RAIN_SPEED;							// 躁鬱雨の速度(躁鬱共通)
	static const unsigned int SP5_RAIN_COLLIDANT_SIZE;					// 躁鬱雨の当たり判定サイズ(躁鬱共通)
	static const unsigned int SP5_HEART_INTERVAL;
	static const double SP5_HEART_GENERATED_TOP_Y;
	static const double SP5_HEART_GENERATED_BOTTOM_Y;
	static const double SP5_HEART_GENERATED_LEFT_X;
	static const double SP5_HEART_GENERATED_RIGHT_X;
	static const double SP5_HEART_SPEED;
	static const unsigned int SP5_HEART_COLLIDANT_SIZE;

	static const unsigned int SP6_RAN_NOZZLE_INIT_RADIUS;				// 初期半径
	static const unsigned int SP6_RAN_MAIN_NOZZLES_AMOUNT;				// ノズル(大)の数
	static const unsigned int SP6_RAN_SUB_NOZZLES_AMOUNT;				// ノズル(小)の数
	static const double SP6_RAN_SUB_NOZZLES_ROTATE_SPEED;				// ノズル(小)の回転速度
	static const unsigned int SP6_RAN_SHOT_INTERVAL;					// ノズル(小)からのショットの発射間隔
	static const double SP6_RAN_SHOT_SPEED;								// ノズル(小)からのショットの速度
	static const unsigned int SP6_RAN_SHOT_COLLIDANT_SIZE;				// ノズル(小)からのショットの当たり判定サイズ
	static const unsigned int SP6_RAN_CONTRACTION_SPEED;				// 円の収縮速度

	static const unsigned int SP6_RU_INITAL_LIMITED_TIME;
	static const unsigned int SP6_RU_LIMITED_TIME;
	static const unsigned int SP6_RU_POTATO_INTERVAL;
	static const double SP6_RU_POTATO_GENERATED_Y;
	static const unsigned int SP6_RU_POTATO_SPEED;
	static const unsigned int SP6_RU_POTATO_COLLIDANT_SIZE;
	static const unsigned int SP6_RU_TOMATO_TICK_INTERVAL;
	static const unsigned int SP6_RU_TOMATO_FIRE_INTERVAL;
	static const unsigned int SP6_RU_TOMATO_SPEED;
	static const unsigned int SP6_RU_TOMATO_COLLIDANT_SIZE;
	static const unsigned int SP6_RU_TOMATO_NOZZLES;
	static const unsigned int SP6_RU_TOMATO_TICK_COUNT_MAX;

	static const unsigned int SP6_POSE_RAN_A_X_LEFT;
	static const unsigned int SP6_POSE_RAN_A_X_RIGHT;
	static const unsigned int SP6_POSE_RAN_A_Y;
	static const unsigned int SP6_POSE_RAN_A_EXTRATE;
	static const double SP6_POSE_RAN_A_RADIAN_LEFT;
	static const double SP6_POSE_RAN_A_RADIAN_RIGHT;
	static const unsigned int SP6_POSE_RAN_B_X_LEFT;
	static const unsigned int SP6_POSE_RAN_B_X_RIGHT;
	static const unsigned int SP6_POSE_RAN_B_Y;
	static const unsigned int SP6_POSE_RAN_B_EXTRATE;
	static const double SP6_POSE_RAN_B_RADIAN_LEFT;
	static const double SP6_POSE_RAN_B_RADIAN_RIGHT;
	static const unsigned int SP6_POSE_RU_X_LEFT;
	static const unsigned int SP6_POSE_RU_X_RIGHT;
	static const unsigned int SP6_POSE_RU_Y;
	static const unsigned int SP6_POSE_RU_EXTRATE;
	static const double SP6_POSE_RU_RADIAN_LEFT;
	static const double SP6_POSE_RU_RADIAN_RIGHT;

	static const unsigned int SP7_INITIAL_WAIT;
	static const unsigned int SP7_DIAL_COUNT;
	static const unsigned int SP7_DIAL_SHOT_COUNT;
	static const double SP7_DIAL_APERTURE_ARG_RANGE;
	static const double SP7_DIAL_ROLLING_SPEED;
	static const unsigned int SP7_DIAL_RADIUS_STEP;
	static const unsigned int SP7_DIAL_INNERMOST_RADIUS;
	static const unsigned int SP7_DIAL_SHOT_COLLIDANT_SIZE;
	static const double SP7_DIAL_SHOT_SCATTER_SPEED;
	static const unsigned int SP7_LASER_EMIT_DURATION;
	static const unsigned int SP7_LASER_COUNT;
	static const unsigned int SP7_LASER_WIDTH;
	static const unsigned int SP7_LASER_LENGTH;
	static const unsigned int SP7_LASER_DPS;
	static const unsigned int SP7_LASER_COUNT;
	static const unsigned int SP7_LASER_PRENOTIFY_DURATION;
	static const unsigned int SP7_LASER_PRENOTIFY_LINE_LENGTH;
	static const double SP7_DAGGER_EMIT_POS_Y;
	static const unsigned int SP7_DAGGER_EMIT_INTERVAL;
	static const unsigned int SP7_DAGGER_COLLIDANT_SIZE;
	static const double SP7_DAGGER_SPEED;


	static const unsigned int INITIAL_HP;
	static const double NM1_ACTIVATE_HP_RATIO;
	static const double SP1_ACTIVATE_HP_RATIO;
	static const double NM2_ACTIVATE_HP_RATIO;
	static const double SP2_ACTIVATE_HP_RATIO;
	static const double SP3_ACTIVATE_HP_RATIO;
	static const double NM3_ACTIVATE_HP_RATIO;
	static const double SP4_ACTIVATE_HP_RATIO;
	static const double SP5_ACTIVATE_HP_RATIO;
	static const double NM4_ACTIVATE_HP_RATIO;
	static const double SP6_ACTIVATE_HP_RATIO;
	static const double SP7_ACTIVATE_HP_RATIO;

public:
	static ToroiStatus STATUS;
	Toroi();
	void update() override;
	void draw() override;

	static const unsigned int NM3_PARASOL_RAIN_FRAMING_INTERVAL;
	static const unsigned int SP3_GHOST_FRAMING_INTERVAL;


	static const unsigned int CRUSH_BONUS;
	static const unsigned int SP1_ACCOMPLISH_BONUS;
	static const unsigned int SP2_ACCOMPLISH_BONUS;
	static const unsigned int SP3_ACCOMPLISH_BONUS;
	static const unsigned int SP4_ACCOMPLISH_BONUS;
	static const unsigned int SP5_ACCOMPLISH_BONUS;
	static const unsigned int SP6_ACCOMPLISH_BONUS;
	static const unsigned int SP7_ACCOMPLISH_BONUS;

};