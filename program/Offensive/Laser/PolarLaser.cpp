#include "DebugParams.h"
#include "Offensive/Laser/PolarLaser.h"

PolarLaser::PolarLaser(
	InFieldPosition init_emit_pos,
	double init_arg,
	double init_length,
	double init_width,
	double init_dps,
	bool init_active_flag,
	SkinID given_skin_id
) :
	Laser(init_active_flag),
	arg(init_arg),
	length(init_length),
	width(init_width),
	dps(init_dps),
	skin_id(given_skin_id)
{
}


void PolarLaser::update() {

}


void PolarLaser::draw() {
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}


void PolarLaser::set_arg(double alt_arg) {
	arg = alt_arg;
}


void PolarLaser::set_length(double alt_length) {
	length = alt_length;
}


void PolarLaser::set_width(double alt_width) {
	width = alt_width;
}


void PolarLaser::set_dps(double alt_dps) {
	dps = alt_dps;
}