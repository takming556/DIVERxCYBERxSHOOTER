#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg2Wv8R : public ZakoCharacter {
private:
	int line_up_x;
	double arg;
	double speed;
	double lower_down_speed;
	double collidant_radius;
	double last_updated_clock;
	double last_generated_clock;
	Stg2WAVE8MoveFlag move_status;
	int order_num;
	double draw_extrate;

	static const double INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_ARG;
	static const double INIT_SPEED;
	static const unsigned int INIT_HP;
	static const unsigned int INIT_COLLIDANT_SIZE;
	static const unsigned int SHOT_NOZZLES;
	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int LINE_UP_Y;
	static const double COLLIDANT_EXPANDED_RATE;
	static const double INIT_DRAW_EXTRATE;

public:
	ZkChrStg2Wv8R(enum CharacterID given_id, int line_up_position_x, double lower_speed);
	void update() override;
	void draw() override;
	static Stg2WAVE8WaitFlag WAIT_FLAG_R18;
	static Stg2WAVE8WaitFlag WAIT_FLAG_R27;
	static Stg2WAVE8WaitFlag WAIT_FLAG_R36;
	static Stg2WAVE8WaitFlag WAIT_FLAG_R45;
};
