#include "Offensive/Laser/Laser.h"


LaserID Laser::NEXT_ID;


Laser::Laser(unsigned int given_dps, bool init_active_flag) :
	dps(given_dps),
	active_flag(init_active_flag),
	terminated_flag(false)
{
}


Laser::Laser() = default;


void Laser::INITIALIZE() {
	NEXT_ID = 0;
}


LaserID Laser::GENERATE_ID() {
	unsigned int generated_id = NEXT_ID;
	++NEXT_ID;
	return generated_id;
}


bool Laser::is_active() {
	return active_flag;
}


void Laser::activate() {
	active_flag = true;
}


void Laser::inactivate() {
	active_flag = false;
}


void Laser::terminate() {
	terminated_flag = true;
}