#pragma once
#include "Offensive/Offensive.h"

class Bullet : virtual public Offensive {
protected:
	double arg;		//�i�s����(���W�A���C�E��0)
	double speed;	//�e�̑��x(pixel per second)
public:
	Bullet(double init_arg, double init_speed);
	Bullet() {}
	void draw_durability() override;
};