#pragma once
#include "Offensive/Bullet/Bullet.h"

class HomingShot : public Bullet {
private:
	enum SkinID skin_id;
	static const double SUSPENSION_TIME;
	int last_arg_updated_clock;

public:
	HomingShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		unsigned int collidant_size,
		unsigned int durability,
		enum SkinID skin_id
	);
	void update() override;
	void draw() override;
};