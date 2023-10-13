#include <cmath>
#include "DxLib.h"
#include "enum.h"
#include "ImageHandles.h"
#include "DebugParams.h"
#include "Offensive/Bullet/ParabolicShot.h"

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
	SkinID given_skin_id
) :
	Offensive(given_skin_id),
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability, collidant_size),
	accel(init_accel),
	accel_arg(init_accel_arg),
	last_updated_clock2(DxLib::GetNowHiPerformanceCount())
{
}


void ParabolicShot::update() {
	double pos_delta_time = static_cast<double>(last_updated_clock - last_updated_clock2) / 1000 / 1000;

	double speed_x = speed * cos(arg);
	double speed_y = speed * sin(arg);

	position->x += speed_x * pos_delta_time;
	position->y += speed_y * pos_delta_time;

	last_updated_clock2 = last_updated_clock;
	double spd_delta_time = static_cast<double>(DxLib::GetNowHiPerformanceCount() - last_updated_clock) / 1000 / 1000;

	double accel_x = accel * cos(accel_arg);
	double accel_y = accel * sin(accel_arg);
	speed_x += accel_x * spd_delta_time;
	speed_y += accel_y * spd_delta_time;

	speed = sqrt(pow(speed_x, 2.0) + pow(speed_y, 2.0));
	arg = atan2(speed_y, speed_x);

	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}



void ParabolicShot::draw() {
	Position draw_pos = position->get_draw_position();

	switch (skin_id) {
	case SkinID::TOROI_SP1_TREAT:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.7, -arg, ImageHandles::OVAL_ORANGE, TRUE);
		break;
	}
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}