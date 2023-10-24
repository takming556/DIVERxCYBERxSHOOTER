#pragma once
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"


class LeidenJar : public ZakoCharacter {
private:
	double arg;
	double speed;
	LeidenJarStatus status;
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
	static const unsigned int INITIAL_HP;
	static const double DRAW_ARG_ROTATE_SPEED;
public:
	LeidenJar(
		double init_pos_x,
		double init_pos_y,
		CharacterID given_id
	);
	virtual void update() final override;
	virtual void draw() final override;
};