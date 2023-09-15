#pragma once
#include "Offensive/Bullet/StraightShot/StraightShot.h"

class FloatingTerrorShot : public StraightShot {
private:
	enum FloatingTerrorShotMode status;
	static const unsigned int MODE_SWITCH_Y;
	static const double FLOATING_SPEED;
	static const double TERROR_SPEED;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int DURABILITY;

public:
	FloatingTerrorShot(double init_pos_x, double init_pos_y);
	void update() override;
};