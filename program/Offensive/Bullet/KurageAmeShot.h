#pragma once
#include "enum.h"
#include "Offensive/Bullet/Bullet.h"

class KurageAmeShot : public Bullet {
private:
	KurageAmeShotMode mode;
	int generated_clock;
	static const double GRAVITY_CONSTANT;
	static const unsigned int WAITTIME_UNTIL_MODECHANGE;
	static const unsigned int COLLIDANT_SIZE;
	static const unsigned int DURABILITY;
	static const double DRAW_EXTRATE;
public:
	KurageAmeShot(double init_pos_x, double init_pos_y);
	void update() override;
	void draw() override;
};