﻿#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg1Wv3S : public ZakoCharacter { //クジラ
private:
	double arg;
	double speed;
	int stay_pos_y;
	int stay_count;
	int stay_clock_started;
	unsigned int tick_count;
	int last_shot_completed_clock;
	int last_tick_fired_clock;
	double last_updated_clock;

	Stg1WAVE3SMode status;

	static const double INIT_ARG;
	static const double INIT_SPEED;
	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;

	static const unsigned int TICKS;
	static const unsigned int TICK_INTERVAL;
	static const unsigned int SHOT_INTERVAL;
	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int SHOT_DURABILITY;

	static const double DRAW_EXTRATE;

public:
	ZkChrStg1Wv3S(
		enum CharacterID given_id,
		double init_pos_x,
		double init_pos_y
		);
	void update() override;
	void draw() override;
};