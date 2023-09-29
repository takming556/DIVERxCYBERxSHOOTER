#pragma once
#include "enum.h"
#include "Position/InFieldPosition.h"
#include "Offensive/Laser/Laser.h"

class PolarLaser : public Laser {
private:
	InFieldPosition emit_pos;
	double arg;
	double length;
	double width;
	double dps;
	SkinID skin_id;
public:
	PolarLaser(
		InFieldPosition init_emit_pos,
		double init_arg,
		double init_length,
		double init_width,
		double init_dps,
		bool init_active_flag,
		SkinID given_skin_id
	);
	void update() override;
	void draw() override;
	void set_arg(double alt_arg);
	void set_length(double alt_length);
	void set_width(double alt_width);
	void set_dps(double alt_dps);
};