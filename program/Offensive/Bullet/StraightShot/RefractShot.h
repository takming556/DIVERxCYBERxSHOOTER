#pragma once
#include "Offensive/Bullet/StraightShot/StraightShot.h"

class RefractShot : virtual public StraightShot {
public:
	RefractShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		unsigned int collidant_size,
		unsigned int durability,
		SkinID given_skin_id

	);
	RefractShot() = default;
	void update() override;
	void draw() override;
};