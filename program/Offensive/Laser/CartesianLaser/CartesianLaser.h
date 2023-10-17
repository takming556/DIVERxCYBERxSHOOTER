#pragma once
#include "enum.h"
#include "Position/InFieldPosition.h"
#include "Offensive/Laser/Laser.h"

class CartesianLaser : public Laser {
protected:
	InFieldPosition begin_pos;
	InFieldPosition end_pos;
	double width;
	InFieldPosition get_vert1_pos();
	InFieldPosition get_vert2_pos();
	InFieldPosition get_vert3_pos();
	InFieldPosition get_vert4_pos();
public:
	CartesianLaser(
		double init_begin_pos_x,
		double init_begin_pos_y,
		double init_end_pos_x,
		double init_end_pos_y,
		double init_width,
		double init_dps,
		bool init_active_flag,
		SkinID given_skin_id
	);
	virtual void update() override;
	virtual void draw() final override;
	void set_begin_pos(double alt_begin_pos_x, double alt_begin_pos_y);
	void set_begin_pos(InFieldPosition alt_begin_pos);
	void set_end_pos(double alt_end_pos_x, double alt_end_pos_y);
	void set_end_pos(InFieldPosition alt_end_pos);
	void set_pos(double alt_begin_pos_x, double alt_begin_pos_y, double alt_end_pos_x, double alt_end_pos_y);
	void set_pos(InFieldPosition alt_begin_pos, InFieldPosition alt_end_pos);
	void set_width(double alt_width);
	void set_dps(double alt_dps);
};