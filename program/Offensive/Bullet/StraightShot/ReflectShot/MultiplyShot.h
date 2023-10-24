#pragma once
#include "Offensive/Bullet/StraightShot/ReflectShot/ReflectShot.h"

class MultiplyShot : public ReflectShot {
private:
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