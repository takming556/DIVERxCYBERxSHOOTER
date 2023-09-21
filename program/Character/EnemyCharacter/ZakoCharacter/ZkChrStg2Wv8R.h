#pragma once
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "enum.h"

class ZkChrStg2Wv8R : public ZakoCharacter {
private:
	int line_up_x;
	double speed;
	double lower_down_speed;
	double arg;
	double last_updated_clock;
	double last_generated_clock;
	Stg2WAVE8MoveFlag move_status;
	int order_num;

	static const double INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_SPEED;
	static const double INIT_ARG;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int INIT_HP;
	static const unsigned int LINE_UP_Y;

	static const double DRAW_EXTRATE;

public:
	ZkChrStg2Wv8R(enum CharacterID given_id, int line_up_position_x, double lower_speed);
	void update() override;
	void draw() override;
	static Stg2WAVE8WaitFlag WAIT_FLAG_R18;
	static Stg2WAVE8WaitFlag WAIT_FLAG_R27;
	static Stg2WAVE8WaitFlag WAIT_FLAG_R36;
	static Stg2WAVE8WaitFlag WAIT_FLAG_R45;
};
