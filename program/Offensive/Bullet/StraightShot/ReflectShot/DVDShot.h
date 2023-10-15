#pragma once
#include "Offensive/Bullet/StraightShot/ReflectShot/ReflectShot.h"

class DVDShot : public ReflectShot {
private:
	unsigned int collide_count;
	void clone();
	void odd_clone();
	void even_clone();
	static const double DECOY_SHOT_SPEED;
	static const double COY_SHOT_SPEED;
	static const double SELF_SHOT_SPEED;
	static const unsigned int DECOY_COLLIDANT_SIZE;
	static const unsigned int COY_COLLIDANT_SIZE;
	static const unsigned int SELF_COLLIDANT_SIZE;
	static const double DRAW_ARG;
	static const double DRAW_EXTRATE;

public:
	DVDShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg
	);
	virtual void update() final override;
	virtual void draw() final override;
};