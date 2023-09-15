#pragma once
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "enum.h"

class ZkChrStg3Wv3LR : public ZakoCharacter {
private:
	double speed;
	double arg;
	int tick_count;
	int shot_count;
	double last_updated_clock;
	double last_tick_generated_clock;
	double last_shot_completed_clock;
	double move_clock;
	int launch_ways;

	enum Stg3WAVE3MoveFlag move_status;

	static const double L_INIT_POS_X;
	static const double R_INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_SPEED;
	static const double INIT_ARG;
	static const unsigned int INIT_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int TICKS;
	static const unsigned int SHOTS;
	static const unsigned int TICK_INTERVAL;
	static const unsigned int SHOT_INTERVAL;
	static const double SHIFT_ARG;
	static const unsigned int ENTER_TIME;
	static const unsigned int STAY_TIME;

	static const double DRAW_EXTRATE;

	static int INIT_POS_X(enum CharacterID given_id);

public:
	ZkChrStg3Wv3LR(enum CharacterID given_id);
	void update() override;
	void draw() override;
};