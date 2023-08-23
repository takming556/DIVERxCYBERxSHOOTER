#pragma once
#include "Offensive/Bullet/Bullet.h"

class GravityShot : public Bullet {
protected:
	enum SkinID skin_id;
	const double intensity;
	double accel_x;
	double accel_y;
	double speed_x;
	double speed_y;
	LONGLONG last_updated_clock2;
public:
	GravityShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		double init_intensity,
		unsigned int collidant_size,
		unsigned int durability,
		enum SkinID given_skin_id
	);
	void update() override;
	void draw() override;
};