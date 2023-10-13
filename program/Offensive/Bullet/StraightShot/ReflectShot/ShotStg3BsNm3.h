#pragma once
#include "Offensive/Bullet/StraightShot/ReflectShot/ReflectShot.h"

class ShotStg3BsNm3 : public ReflectShot {
private:
	unsigned int collide_count;
public:
	ShotStg3BsNm3(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		unsigned int collidant_size,
		unsigned int durability,
		SkinID given_skin_id
	);
	virtual void update() final override;
	virtual void draw() final override;
};