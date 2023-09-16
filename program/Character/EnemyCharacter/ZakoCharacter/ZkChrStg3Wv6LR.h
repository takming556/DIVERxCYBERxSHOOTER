#pragma once
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "enum.h"

class ZkChrStg3Wv6LR :
 public ZakoCharacter {
private:
	double speed;
	double arg;
	double last_tick_generated_clock;
	double last_shot_completed_clock;
	int shot_count;
	int tick_count;


	static const double L_INIT_POS_X;
	static const double R_INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_SPEED;
	static const double L_INIT_ARG;
	static const double R_INIT_ARG;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int INIT_HP;
	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;
	static const unsigned int SHOTS;
	static const unsigned int TICKS;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int TICK_INTERVAL;

	static int INIT_POS_X(enum CharacterID given_id);
	static double INIT_ARG(enum CharacterID given_id);

public:
	ZkChrStg3Wv6LR(enum CharacterID given_id);
	void update() override;
	void draw() override;
};