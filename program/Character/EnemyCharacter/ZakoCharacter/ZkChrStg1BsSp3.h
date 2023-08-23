#pragma once
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg1BsSp3 : public ZakoCharacter {
private:
	int last_barraged_clock;

	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;
	static const unsigned int NOZZLES;
	static const unsigned int INTERVAL;

public:
	ZkChrStg1BsSp3(double init_pos_x, double init_pos_y);
	void update() override;
	void draw() override;
};