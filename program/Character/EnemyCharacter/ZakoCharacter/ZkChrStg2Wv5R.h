﻿#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg2Wv5R : public ZakoCharacter {
private:
	double arg;
	double speed;
	double shot_arg;
	double last_tick_generated_clock;
	double move_clock;

	Stg2WAVE5MoveFlag move_status;

	static const double INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_ARG;
	static const double INIT_SPEED;
	static const unsigned int INIT_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int TICK_INTERVAL;
	static const unsigned int ENTER_TIME;
	static const unsigned int STAY_TIME;

	static const double DRAW_EXTRATE;

public:
	ZkChrStg2Wv5R();
	void update() override;
	void draw() override;
};