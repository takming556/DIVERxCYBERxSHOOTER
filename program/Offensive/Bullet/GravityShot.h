#pragma once
#include "Offensive/Bullet/Bullet.h"

class GravityShot : public Bullet {
protected:
	enum SkinID skin_id;
	double mass;
public:
	GravityShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		double mass,
		unsigned int collidant_size,
		unsigned int durability,
		enum SkinID given_skin_id
	);
	void update() override;
	void draw() override;
};