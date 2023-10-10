#include "Offensive/Laser/CartesianLaser.h"


CartesianLaser::CartesianLaser(
	double init_begin_pos_x,
	double init_begin_pos_y,
	double init_end_pos_x,
	double init_end_pos_y,
	double init_width,
	double init_dps,
	bool init_active_flag,
	SkinID given_skin_id
)
{
}


void CartesianLaser::update() {

}


void CartesianLaser::draw(){}


void CartesianLaser::set_begin_pos(double alt_begin_pos_x, double alt_begin_pos_y) {}


void CartesianLaser::set_begin_pos(InFieldPosition alt_begin_pos) {}


void CartesianLaser::set_end_pos(double alt_end_pos_x, double alt_end_pos_y) {}


void CartesianLaser::set_end_pos(InFieldPosition alt_end_pos) {}


void CartesianLaser::set_pos(double alt_begin_pos_x, double alt_begin_pos_y, double alt_end_pos_x, double alt_end_pos_y) {}


void CartesianLaser::set_pos(InFieldPosition alt_begin_pos, InFieldPosition alt_end_pos) {}


void CartesianLaser::set_width(double alt_width) {}


void CartesianLaser::set_dps(double alt_dps) {}
