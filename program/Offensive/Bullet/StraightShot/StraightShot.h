#pragma once
#include "Offensive/Bullet/Bullet.h"

class StraightShot : virtual public Bullet {
public:
	StraightShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		unsigned int collidant_size,
		unsigned int durability,
		enum SkinID given_skin_id
	);
	StraightShot() = default;
	void update() override;
	void draw() override;
};