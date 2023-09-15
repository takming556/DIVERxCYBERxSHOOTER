#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class RotatingStraightShotEmission;

class ZkChrStg1Wv2 : public ZakoCharacter {
private:
	double speed;
	double arg;
	unique_ptr<RotatingStraightShotEmission> barrage;

	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int BARRAGE_EMIT_NOZZLES;
	static const unsigned int BARRAGE_EMITS;
	static const unsigned int BARRAGE_EMIT_INTERVAL;
	static const double BARRAGE_INIT_ARG;
	static const double BARRAGE_SHOT_SPEED;
	static const unsigned int BARRAGE_SHOT_COLLIDANT_SIZE;
	static const unsigned int BARRAGE_SHOT_DURABILITY;
public:
	ZkChrStg1Wv2(
		enum CharacterID given_id,
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		double barrage_rotate_speed
	);
	void update() override;
	void draw() override;
};
