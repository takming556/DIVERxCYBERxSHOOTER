#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChrStg2BsNm4 : public ZakoCharacter {
private:
	double pos_x;
	double pos_y;
	double random_arg;
	double random_speed;
	int random_interval;
	int kept_clock;
	double last_updated_clock;

	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;

	static const double DRAW_EXTRATE;

public:
	ZkChrStg2BsNm4(
		CharacterID given_id,
		double boss_pos_x,
		double boss_pos_y
	);
	void update() override;
	void draw() override;
	static bool ESCAPE_FLAG;
};