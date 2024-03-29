﻿#pragma once
#include "Offensive/Bullet/Bullet.h"


class CurvingShot : public Bullet {
protected:
	double curve_speed;
	double last_arg;
	double last_speed;
public:
	CurvingShot(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		double curve_speed,
		unsigned int collidant_size,
		unsigned int durability,
		SkinID skin_id
	);
	void update() override;
	void draw() override;
	void set_curve_speed(double given_curve_speed);
};