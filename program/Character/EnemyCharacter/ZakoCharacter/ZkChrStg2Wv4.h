#pragma once
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg2Wv4 : public ZakoCharacter {
private:
	int last_shot_clock;
	unsigned int shot_count;
	double speed;
	double arg;
	bool reflection_flag;
	static const double DRAW_EXTRATE;
	static const unsigned int SHOTS;
	static const unsigned int SHOT_INTERVAL;

public:
	ZkChrStg2Wv4(
		double init_pos_x,
		double init_pos_y,
		double init_speed,
		double init_arg,
		unsigned int init_hp,
		unsigned int collidant_size
	);
	void update() override;
	void draw() override;
};