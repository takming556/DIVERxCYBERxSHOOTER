#pragma once
#include"Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include"enum.h"

class ZkChrStg3Wv5BL : public ZakoCharacter {
private:
	double speed;
	double arg;

	double last_updated_clock;
	int last_tick_generated_clock;

	Stg3WAVE5BMode mode;

	static const double INIT_POS_X;
	static const double INIT_POS_Y;
	static const double INIT_SPEED;
	static const double INIT_ARG;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int INIT_HP;
	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int TICK_INTERVAL;

	static const double DRAW_EXTRATE;
	
public:
	ZkChrStg3Wv5BL(CharacterID given_id, Stg3WAVE5BLR lr);
	void update() override;
	void draw() override;

};