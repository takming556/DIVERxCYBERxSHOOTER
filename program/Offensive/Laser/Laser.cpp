#include "Offensive/Laser/Laser.h"

Laser::Laser(bool init_active_flag) :
	active_flag(init_active_flag),
	terminated_flag(false)
{
}


Laser::Laser() = default;


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