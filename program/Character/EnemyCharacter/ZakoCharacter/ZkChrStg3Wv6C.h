#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg3Wv6C : public ZakoCharacter {
private:
	double speed;
	double arg;
	unsigned int generated_x;
	unsigned int generated_y;
	int last_generated_clock;
	int move_clock;
	Stg3WAVE6CMoveFlag move_status;
	Stg3WAVE6CGenerateFlag status_flag;

	static const double INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_SPEED;
	static const double INIT_ARG;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int INITIAL_HP;
	static const unsigned int GENERATED_INTERVAL;
	static const double SHOT_RADIANT;
	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int ENTER_TIME;
	static const unsigned int STAY_TIME;
	static const double DRAW_EXTRATE;

public:
	ZkChrStg3Wv6C();
	void update() override;
	void draw() override;
};