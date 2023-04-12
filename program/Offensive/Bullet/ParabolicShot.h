#pragma once
#include "Offensive/Bullet/Bullet.h"

class ParabolicShot : public Bullet {
	static double flight_accel_constant;
	static double flight_accel_arg;
};