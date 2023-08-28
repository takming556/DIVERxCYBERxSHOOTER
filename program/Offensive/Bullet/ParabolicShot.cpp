#include <memory>
#include <cmath>
#include "enum.h"
#include "ImageHandles.h"
#include "DebugParams.h"
#include "Offensive/Bullet/ParabolicShot.h"
#include "CollideRealm/CollideCircle.h"

using std::make_unique;
using std::sin;
using std::cos;
using std::atan2;
using std::pow;
using std::sqrt;


ParabolicShot::ParabolicShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,	
	double init_accel,
	double init_accel_arg,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID given_skin_id
) :
	Offensive(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, collidant_size), durability),
	Bullet(init_arg, init_speed),
	accel(accel),
	accel_arg(accel_arg)
{
}


void ParabolicShot::update() {
	double speed_x = speed * cos(arg);
	double speed_y = speed * sin(arg);
	LONGLONG delta_time = static_cast<double>(DxLib::GetNowHiPerformanceCount() - last_updated_clock) / 1000 / 1000;
	position->x += speed_x * delta_time;
	position->y += speed_y * delta_time;

	double accel_x = accel * cos(accel_arg);
	double accel_y = accel * sin(accel_arg);
	speed_x += accel_x * delta_time;
	speed_y += accel_y * delta_time;

	speed = sqrt(pow(speed_x, 2.0) + pow(speed_y, 2.0));
	arg = atan2(speed_y, speed_x);

	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}



void ParabolicShot::draw() {
	Position draw_pos = position->get_draw_position();

	switch (skin_id) {
	case SkinID::NORMAL_BLUE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BLUE_MARBLE, TRUE);
		break;
	}
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}