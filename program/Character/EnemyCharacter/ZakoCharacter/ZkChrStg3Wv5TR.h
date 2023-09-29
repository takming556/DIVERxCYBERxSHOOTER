#pragma once
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "enum.h"

class ZkChrStg3Wv5TR : public ZakoCharacter {
private:
	double arg;
	double last_updated_clock;
	int last_tick_generated_clock;

	bool reflect_flag;

	static const unsigned int INIT_POS_X;
	static const unsigned int INIT_POS_Y;
	static const double INIT_SPEED;
	static const double INIT_ARG;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int INIT_HP;
	static const double SHOT_SPEED;
	static const double SHOT_ARG;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int TICK_INTERVAL;

	static const double DRAW_EXTRATE;

public:
	ZkChrStg3Wv5TR(CharacterID given_id);
	void update() override;
	void draw() override;
};