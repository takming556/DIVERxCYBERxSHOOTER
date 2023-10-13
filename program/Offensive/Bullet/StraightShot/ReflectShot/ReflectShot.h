#pragma once
#include "Offensive/Bullet/StraightShot/StraightShot.h"

class ReflectShot : virtual public StraightShot {
protected:
	bool left_wall_last_collided_flag;
	bool right_wall_last_collided_flag;
	bool top_wall_last_collided_flag;
	bool bottom_wall_last_collided_flag;
	void reflect_on_rightline();
	void reflect_on_leftline();
	void reflect_on_topline();
	void reflect_on_bottomline();
public:
	ReflectShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		unsigned int collidant_size,
		unsigned int durability,
		SkinID given_skin_id
	);
	ReflectShot() = default;
	void update() override;
	void draw() override;
};