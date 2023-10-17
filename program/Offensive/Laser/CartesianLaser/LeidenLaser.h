#pragma once
#include "Offensive/Laser/CartesianLaser/CartesianLaser.h"
#include "Offensive/Laser/CartesianLaser/LeidenLaser.h"
#include "enum.h"

class LeidenLaser : public CartesianLaser {
private:
	bool last_collided_with_mychr_flag;
	static const unsigned int WIDTH;
	static const unsigned int DPS;
public:
	LeidenLaser(
		double init_begin_pos_x,
		double init_begin_pos_y,
		double init_end_pos_x,
		double init_end_pos_y
	);
	virtual void update() final override;
	unsigned int collide_count;
};