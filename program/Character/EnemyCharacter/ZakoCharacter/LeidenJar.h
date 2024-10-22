#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"


class LeidenJar : public ZakoCharacter {
private:
	double arg;
	double speed;
	double shot_arg;
	double shot_speed;
	unsigned int shot_collidant_size;
	unsigned int shot_nozzles;
	double shot_last_generated_clock;
	double draw_arg;
	bool left_wall_last_collided_flag;
	bool right_wall_last_collided_flag;
	bool top_wall_last_collided_flag;
	bool bottom_wall_last_collided_flag;
	void reflect_on_rightline();
	void reflect_on_leftline();
	void reflect_on_topline();
	void reflect_on_bottomline();

	static const double INIT_SPEED;
	static const unsigned int COLLIDANT_SIZE;
	static const double INIT_SHOT_SPEED;
	static const unsigned int SHOT_COLLIDANT_SIZE;
	static const unsigned int SHOT_INTERVAL;
	static const unsigned int INITIAL_HP;
	static const double DRAW_ARG_ROTATE_SPEED;
public:
	LeidenJarStatus status;
	LeidenJar(
		double init_pos_x,
		double init_pos_y,
		CharacterID given_id
	);
	virtual ~LeidenJar() = default;
	virtual void update() final override;
	virtual void draw() final override;
};