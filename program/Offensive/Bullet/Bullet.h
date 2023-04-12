#pragma once
#include "Offensive/Offensive.h"

class Bullet : virtual public Offensive {
protected:
	double arg;		//進行方向(ラジアン，右が0)
	double speed;	//弾の速度(pixel per second)
public:
	Bullet(double init_arg, double init_speed);
	Bullet() {}
	void draw_durability() override;
};