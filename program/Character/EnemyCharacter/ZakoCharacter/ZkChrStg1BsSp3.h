#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg1BsSp3 : public ZakoCharacter {
private:
	int last_barraged_clock;

	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int NOZZLES;
	static const unsigned int INTERVAL;

	static const double DRAW_EXTRATE;

public:
	ZkChrStg1BsSp3(
		enum CharacterID given_id,
		double init_pos_x,
		double init_pos_y
	);
	void update() override;
	void draw() override;
};