#pragma once
#include "Offensive/Bullet/StraightShot/ReflectShot/ReflectShot.h"

class MultiplyShot : public ReflectShot {
private:
	int kept_clock;
	void clone();
	static const double SPEED;
	static const unsigned int  COLLIDANT_SIZE;
	static const unsigned int MULTIPLY_INTERVAL;
	static const double DRAW_EXTRATE;
	
public:
	MultiplyShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg
	);
	virtual void update() final override;
	virtual void draw() final override;

};