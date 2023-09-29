#include "Offensive/Laser/Laser.h"

Laser::Laser(bool init_active_flag) :
	active_flag(init_active_flag)
{
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