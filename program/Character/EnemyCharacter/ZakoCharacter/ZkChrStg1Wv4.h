#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class SimpleStraightShotEmission;

class ZkChrStg1Wv4 : public ZakoCharacter { //クジラ
private:
	unique_ptr<SimpleStraightShotEmission> barrage;
	int last_lines_tick_fired_clock;
	int last_lines_shot_completed_clock;
	unsigned int tick_count;
	unsigned int shot_count;

	static const unsigned int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const unsigned int LINES_TICKS;
	static const unsigned int LINES_SHOTS;
	static const unsigned int LINES_TICK_INTERVAL;
	static const unsigned int LINES_SHOT_INTERVAL;
	static const double LINES_SHOT_SPEED;
	static const unsigned int LINES_SHOT_COLLIDANT_SIZE;
	static const unsigned int LINES_SHOT_DURABILITY;
	static const double LINES_SHOT_DRAW_EXTRATE;

	static const unsigned int BARRAGE_EMIT_NOZZLES;
	static const unsigned int BARRAGE_EMITS;
	static const unsigned int BARRAGE_EMIT_INTERVAL;
	static const double BARRAGE_INIT_ARG;
	static const double BARRAGE_SHOT_SPEED;
	static const unsigned int BARRAGE_SHOT_COLLIDANT_SIZE;
	static const unsigned int BARRAGE_SHOT_DURABILITY;
	static const double BARRAGE_SHOT_DRAW_EXTRATE;
public:
	ZkChrStg1Wv4(
		enum CharacterID given_id,
		double init_pos_x,
		double init_pos_y
	);
	void update() override;
	void draw() override;


};