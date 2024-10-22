#pragma once
#include <string>
#include <memory>
#include "enum.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"

using std::wstring;
using std::unique_ptr;

class SimpleStraightShotEmission;


class Mofu : public BossCharacter {
private:
	int generated_clock;
	int last_status_changed_clock;
	int last_normal1_performed_clock;
	int last_sp1_performed_clock;
	int last_normal2_lines_performed_clock;
	int last_sp2_swaying_performed_clock;
	int last_sp2_swaying_tick_fired_clock;
	int last_sp2_straight_performed_clock;
	int last_normal3_tickked_clock;
	int last_normal3_barraged_clock;
	int last_sp3_mofu_tickked_clock;
	int last_sp3_mofu_shot_completed_clock;
	unsigned int sp2_swaying_tick_count;
	unique_ptr<SimpleStraightShotEmission> normal2_barrage;
	bool sp2_swaying_tick_firing_flag;
	double arg_sp2_swaying_toward_mychr;
	MofuNormal3Mode normal3_mode;
	unsigned int normal3_tick_count;
	unsigned int sp3_mofu_start_nozzles;
	unsigned int sp3_mofu_end_nozzles;
	unsigned int sp3_mofu_tick_count;
	bool sp3_zk_crash_1_first_flag;
	bool sp3_zk_crash_2_first_flag;
	bool sp3_zk_crash_3_first_flag;
	bool sp3_zk_crash_4_first_flag;

	static const wstring CHARACTER_NAME;
	static const wstring SP1_NAME;
	static const wstring SP2_NAME;
	static const wstring SP3_NAME;
	static const int INITIAL_POS_X;
	static const int INITIAL_POS_Y;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int INITIAL_HP;
	static const double NM1_ACTIVATE_HP_RATIO;
	static const double SP1_ACTIVATE_HP_RATIO;
	static const double NM2_ACTIVATE_HP_RATIO;
	static const double SP2_ACTIVATE_HP_RATIO;
	static const double NM3_ACTIVATE_HP_RATIO;
	static const double SP3_ACTIVATE_HP_RATIO;

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

	static const unsigned int SP3_MOFU_TICKS;
	static const unsigned int SP3_MOFU_SHOTS;
	static const unsigned int SP3_MOFU_TICK_INTERVAL;
	static const unsigned int SP3_MOFU_SHOT_INTERVAL;
	static const double SP3_MOFU_SHOT_SPEED;
	static const unsigned int SP3_MOFU_SHOT_COLLIDANT_SIZE;
	static const unsigned int SP3_MOFU_SHOT_DURABILITY;
	static const unsigned int SP3_ZK_CRASH_DAMAGE;

public:
	static MofuStatus STATUS;
	Mofu();
	virtual void update() override;
	virtual void draw() override;
	virtual void funeral() final override;
	static const unsigned int SP1_ACCOMPLISH_BONUS;
	static const unsigned int SP2_ACCOMPLISH_BONUS;
	static const unsigned int SP3_ACCOMPLISH_BONUS;
	static const unsigned int CRUSH_BONUS;
};