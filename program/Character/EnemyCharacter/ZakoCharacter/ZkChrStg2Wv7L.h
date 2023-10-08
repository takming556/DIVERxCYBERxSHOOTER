#pragma once
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "enum.h"

class ZkChrStg2Wv7L : public ZakoCharacter {
private:
	double speed;
	double arg;
	double last_updated_clock;
	double last_generated_clock;
	int turn_clock;
	Stg2WAVE7TurnFlag turn_status;
	int lap_count;

	static const double INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_SPEED;
	static const double INIT_ARG;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int INIT_HP;
	static const unsigned int SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int TURN_INTERVAL;

	static const double DRAW_EXTRATE;

public:
	ZkChrStg2Wv7L(enum CharacterID given_id);	// 引数に左列か右列かを入れるようにする
	void update() override;
	void draw() override;

};