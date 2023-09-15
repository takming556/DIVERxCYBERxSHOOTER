#pragma once
#include "enum.h"
#include "Offensive/Bullet/Bullet.h"

class SwayingShot : public Bullet {
private:
	SkinID skin_id;
	double sway_intensity;
	double sway_frequency;
	double initial_arg;
	double theta;
public:
	SwayingShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		double sway_intensity,
		double sway_frequency,
		unsigned int collidant_size,
		unsigned int durability,
		enum SkinID skin_id
	);
	void update() override;
	void draw() override;
};