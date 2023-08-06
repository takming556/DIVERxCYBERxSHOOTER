#include <memory>
#include "DxLib.h"
#include "Offensive/Bullet/GravityShot.h"
#include "CollideRealm/CollideCircle.h"

using std::make_unique;


GravityShot::GravityShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	double init_mass,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID given_skin_id
) :
	Bullet(init_arg, init_speed),
	Offensive(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, collidant_size), durability),
	skin_id(given_skin_id),
	mass(init_mass)
{
}


void GravityShot::update() {

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double rx = 
}