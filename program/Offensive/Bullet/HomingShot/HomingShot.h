#pragma once
#include "Offensive/Bullet/Bullet.h"

class HomingShot : public Bullet {
private:
	double suspension_time;
	int last_arg_updated_clock;

public:
	HomingShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		double homing_intensity,
		unsigned int collidant_size,
		unsigned int durability,
		SkinID skin_id
	);
	void update() override;
	void draw() override;
};