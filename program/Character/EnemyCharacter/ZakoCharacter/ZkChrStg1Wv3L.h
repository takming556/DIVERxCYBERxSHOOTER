#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class RotatingStraightShotEmission;

class ZkChrStg1Wv3L : public ZakoCharacter { //クラゲ
private:
	unique_ptr<RotatingStraightShotEmission> barrage;
	
	double speed;
	double arg;
	int stay_clock_started;
	int stay_count;
	double last_updated_clock;

	Stg1WAVE3LMode status;

	static const unsigned int STAY_POS_Y;
	static const double INIT_ARG;
	static const double INIT_SPEED;

	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int BARRAGE_EMIT_NOZZLES;
	static const unsigned int BARRAGE_EMIT_INTERVAL;
	static const double BARRAGE_INIT_ARG;
	static const double BARRAGE_SHOT_SPEED;
	static const unsigned int BARRAGE_SHOT_COLLIDANT_SIZE;
	static const unsigned int BARRAGE_SHOT_DURABILITY;
public:
	ZkChrStg1Wv3L(
		enum CharacterID given_id,
		double init_pos_x,
		double init_pos_y,
		double barrage_rotate_speed
	);
	void update() override;
	void draw() override;
};