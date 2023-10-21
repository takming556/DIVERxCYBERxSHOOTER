#pragma once
#include <vector>
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg3Wv4C : public ZakoCharacter {
private:
	double arg;
	double speed;
	double portal_arg;
	double portal_speed;
	// vector<unsigned int> portal_ids;
	int portal_id_count;
	vector<unsigned int> portal_poses_x;
	vector<double> laser_args;
	Position draw_position_begin;
	Position draw_position_end;
	vector<Position> draw_positions_begin;
	vector<Position> draw_positions_end;
	// LaserID laser_id;
	// vector<LaserID> laser_ids;
	int laser_notify_count;
	int laser_emit_count;
	double last_updated_clock;
	int kept_clock;
	int last_tick_generated_clock;
	
	// Stg3WAVE4CMode mode;

	static const unsigned int INIT_POS_X;
	static const unsigned int INIT_POS_Y;
	static const double INIT_ARG;
	static const double INIT_SPEED;
	static const unsigned int INIT_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int PORTAL_POS_Y;
	static const double PORTAL_INIT_ARG;
	static const double PORTAL_INIT_SPEED;
	static const unsigned int PORTAL_COLLIDANT_SIZE;
	static const unsigned int LASER_NOTIFY_COLOR;
	static const unsigned int LASER_LENGTH;
	static const unsigned int LASER_WIDTH;
	static const double LASER_DPS;


	static const double DRAW_EXTRATE;

public:
	ZkChrStg3Wv4C(CharacterID given_id);
	void update() override;
	void draw() override;
	static vector<unsigned int> PORTAL_IDS;
	static vector<LaserID> LASER_IDS;
	static Stg3WAVE4CMode MODE;
	static void INITIALIZE();
};