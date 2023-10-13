#pragma once
#include"enum.h"
#include"Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg3Wv5BLR : public ZakoCharacter {
private:
	double arg;
	double speed;
	double last_updated_clock;
	int last_tick_generated_clock;

	Stg3WAVE5BMode mode;
	Stg3WAVE5BLR lr_flag;

	static const double INIT_POS_X_L;
	static const double INIT_POS_X_R;
	static const double INIT_POS_Y;
	static const double INIT_ARG_L;
	static const double INIT_ARG_R;
	static const double INIT_SPEED;
	static const unsigned int INIT_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int TICK_INTERVAL;

	static const double DRAW_EXTRATE;

	static int INIT_POS_X(Stg3WAVE5BLR given_lr);
	static double INIT_ARG(Stg3WAVE5BLR given_lr);
	
public:
	ZkChrStg3Wv5BLR(CharacterID given_id, Stg3WAVE5BLR lr);
	void update() override;
	void draw() override;
};