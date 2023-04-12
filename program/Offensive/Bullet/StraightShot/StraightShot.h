#pragma once
#include "Offensive/Bullet/Bullet.h"

class StraightShot : virtual public Bullet {
protected:
	enum SkinID skin_id;
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
	StraightShot(enum SkinID given_skin_id);
	void update() override;
	void draw() override;
};