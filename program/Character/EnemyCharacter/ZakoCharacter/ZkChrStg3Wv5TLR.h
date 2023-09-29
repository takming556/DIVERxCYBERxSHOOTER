#pragma once
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "enum.h"

class ZkChrStg3Wv5TLR : public ZakoCharacter {
private:
	double arg;
	int reflect_count;
	double last_updated_clock;
	int last_tick_generated_clock;

	Stg3WAVE5TLR lr_flag;
	bool init_move_flag;
	int reverse_flag;
	
	static const unsigned int INIT_POS_X_L;
	static const unsigned int INIT_POS_X_R;
	static const unsigned int INIT_POS_Y;
	static const double INIT_SPEED;
	static const double INIT_ARG_L;
	static const double INIT_ARG_R;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int INIT_HP;
	static const double SHOT_SPEED;
	static const double SHOT_ARG;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int TICK_INTERVAL;

	static const double DRAW_EXTRATE;

	static int INIT_POS_X(Stg3WAVE5TLR given_lr);
	static double INIT_ARG(Stg3WAVE5TLR given_lr);
	static int INIT_REVERSE_FLAG(Stg3WAVE5TLR given_lr);

public:
	ZkChrStg3Wv5TLR(CharacterID given_id, Stg3WAVE5TLR lr);
	void update() override;
	void draw() override;
};