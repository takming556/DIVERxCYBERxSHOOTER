#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg3Wv4C : public ZakoCharacter {
private:
	double arg;
	double speed;
	double shot_arg;
	double shot_speed;
	BulletID shot_id[6];
	int shot_id_count;
	double last_updated_clock;
	int kept_clock;
	int last_tick_generated_clock;
	
	Stg3WAVE4CMode mode;

	static const unsigned int INIT_POS_X;
	static const unsigned int INIT_POS_Y;
	static const double INIT_ARG;
	static const double INIT_SPEED;
	static const unsigned int INIT_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double SHOT_INIT_ARG;
	static const double SHOT_INIT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;

	static const double DRAW_EXTRATE;

public:
	ZkChrStg3Wv4C(CharacterID given_id);
	void update() override;
	void draw() override;
};