#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg1Wv3S : public ZakoCharacter { //クジラ
private:
	unsigned int tick_count;
	int last_shot_completed_clock;
	int last_tick_fired_clock;

	static const unsigned int TICKS;
	static const unsigned int TICK_INTERVAL;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const double SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int SHOT_DURABILITY;
public:
	ZkChrStg1Wv3S(
		enum CharacterID given_id,
		double init_pos_x,
		double init_pos_y
		);
	void update() override;
	void draw() override;
};