﻿#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg2Wv6R : public ZakoCharacter {
private:
	double last_tick_generated_clock;

	static const double INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_ARG;
	static const double INIT_SPEED;
	static const unsigned int INIT_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double SHOT_ARG;
	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int TICK_INTERVAL;

	static const double DRAW_EXTRATE;

public:
	ZkChrStg2Wv6R(enum CharacterID given_id);
	void update() override;
	void draw() override;
};