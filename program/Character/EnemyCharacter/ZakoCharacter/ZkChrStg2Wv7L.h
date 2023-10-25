#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg2Wv7L : public ZakoCharacter {
private:
	double arg;
	double speed;
	double last_updated_clock;
	double last_generated_clock;
	int turn_clock;
	Stg2WAVE7TurnFlag turn_status;
	int lap_count;

	static const double INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_ARG;
	static const double INIT_SPEED;
	static const unsigned int INIT_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int SHOT_NOZZLES;
	static const unsigned int SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int TURN_INTERVAL;

	static const double DRAW_EXTRATE;

public:
	ZkChrStg2Wv7L(enum CharacterID given_id);
	void update() override;
	void draw() override;

};