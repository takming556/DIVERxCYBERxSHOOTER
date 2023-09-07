#pragma once
#include "StraightShot.h"

class ReflectShot : public StraightShot {
protected:
	bool left_wall_last_collided_flag;
	bool right_wall_last_collided_flag;
	bool up_wall_last_collided_flag;
	bool bottom_wall_last_collided_flag;
	void reflect();
public:
	ReflectShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		unsigned int collidant_size,
		unsigned int durability,
		enum SkinID given_skin_id
	);
	void update() override;
	void draw() override;
};