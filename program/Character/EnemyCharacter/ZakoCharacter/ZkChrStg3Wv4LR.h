#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg3Wv4LR : public ZakoCharacter {
private:
	int init_pos_x;
	double arg;
	double last_updated_clock;
	int last_tick_generated_clock;

	Stg3WAVE4Mode mode;
	Stg3WAVE4LR lr_flag;

	static const unsigned int INIT_POS_X_L;
	static const unsigned int INIT_POS_X_R;
	static const unsigned int INIT_POS_Y;
	static const double INIT_ARG;
	static const double INIT_SPEED;
	static const unsigned int INIT_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double SHOT_SPEED;
	static const unsigned int  SHOT_COLLIDANT_SIZE;
	static const unsigned int TICK_INTERVAL;

	static const double DRAW_EXTRATE;

	static int INIT_POS_X(Stg3WAVE4LR given_lr);
	
public:
	ZkChrStg3Wv4LR(CharacterID given_id, Stg3WAVE4LR lr);
	void update() override;
	void draw() override;
};