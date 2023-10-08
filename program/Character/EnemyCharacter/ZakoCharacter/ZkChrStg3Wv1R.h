#pragma once
#include"Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include"enum.h"

class ZkChrStg3Wv1R : public ZakoCharacter {
private:
	double speed;
	double arg;
	double last_tick_generated_clock;
	Stg3WAVE1Mode mode;
	int shotcount;
	static const double INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_SPEED;
	static const double INIT_ARG;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int INIT_HP;
	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;
	static const unsigned int TICK_INTERVAL;


public:
	ZkChrStg3Wv1R(CharacterID given_id);
	void update() override;
	void draw() override;


};