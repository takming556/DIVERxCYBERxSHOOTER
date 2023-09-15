#include <memory>
#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Offensive/Bullet/GravityShot.h"
#include "CollideRealm/CollideCircle.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "ImageHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::sin;			// 正弦関数
using std::cos;			// 余弦関数
using std::atan2;		// 逆正接関数
using std::pow;			// べき乗関数
using std::sqrt;		// 平方根関数
using std::abs;			// 絶対値関数
using std::numbers::pi;	// 円周率


GravityShot::GravityShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	double init_intensity,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID given_skin_id
) :
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability),
	Offensive(make_unique<CollideCircle>(init_pos_x, init_pos_y, collidant_size)),
	skin_id(given_skin_id),
	intensity(init_intensity),
	accel_x(0.0),
	accel_y(0.0),
	speed_x(init_speed * cos(init_arg)),
	speed_y(init_speed * sin(init_arg)),
	last_updated_clock2(DxLib::GetNowHiPerformanceCount())
{
}


void GravityShot::update() {

	//LONGLONG delta_time = (DxLib::GetNowHiPerformanceCount() - last_updated_clock) / 1000 / 1000;

	double pos_delta_time = (double)(last_updated_clock - last_updated_clock2) / 1000 / 1000;
	position->x += speed_x * pos_delta_time;
	position->y += speed_y * pos_delta_time;
	last_updated_clock2 = last_updated_clock;
	double spd_delta_time = (double)(DxLib::GetNowHiPerformanceCount() - last_updated_clock) / 1000 / 1000;
	speed_x += accel_x * spd_delta_time;
	speed_y += accel_y * spd_delta_time;

	double xA = position->x;
	double xB = Field::MY_CHARACTER->position->x;
	double yA = position->y;
	double yB = Field::MY_CHARACTER->position->y;

	double accel = intensity / (pow(xA - xB, 2.0) + pow(yA - yB, 2.0));
	double argAB = atan2(yB - yA, xB - xA);
	accel_x = accel * cos(argAB);
	accel_y = accel * sin(argAB);

	speed = sqrt(pow(speed_x, 2.0) + pow(speed_y, 2.0));
	arg = atan2(speed_y, speed_x);

	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

}


void GravityShot::draw() {
	Position draw_pos = position->get_draw_position();

	switch (skin_id) {
	case SkinID::GRAVITYSHOTTEST:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::ANCHOR_YELLOW, TRUE);
		break;
	case SkinID::MAGNETIC_ARROW:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::ANCHOR_YELLOW, TRUE);
		break;
	}

	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}