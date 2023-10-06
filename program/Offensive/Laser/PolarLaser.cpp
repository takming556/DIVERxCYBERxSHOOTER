#include <numbers>
#include <cmath>
#include <memory>
#include <vector>
#include "DebugParams.h"
#include "Utils.h"
#include "Offensive/Laser/PolarLaser.h"
#include "CollideRealm/CollidePolygon.h"

using std::vector;
using std::make_unique;
using std::sin;
using std::cos;
using std::pow;
using std::sqrt;
using std::numbers::pi;


PolarLaser::PolarLaser(
	double init_emit_pos_x,
	double init_emit_pos_y,
	double init_arg,
	double init_length,
	double init_width,
	double init_dps,
	bool init_active_flag,
	SkinID given_skin_id
) :
	Laser(init_active_flag),
	emit_pos(InFieldPosition(init_emit_pos_x, init_emit_pos_y)),
	arg(init_arg),
	length(init_length),
	width(init_width),
	dps(init_dps),
	skin_id(given_skin_id)
{
	double tempx;
	double tempy;

	double r1 = width / 2.0;
	double theta1 = -1.0 / 2.0 * pi + arg;
	double x1 = r1 * cos(theta1) + emit_pos.x;
	double y1 = r1 * sin(theta1) + emit_pos.y;

	tempx = length;
	tempy = -(width / 2.0);
	double r2 = sqrt(pow(tempx, 2.0) + pow(tempy, 2.0));
	double theta2 = Utils::fixed_atan2(tempy, tempx) + arg;
	double x2 = r2 * cos(theta2) + emit_pos.x;
	double y2 = r2 * sin(theta2) + emit_pos.y;

	tempx = length;
	tempy = width / 2.0;
	double r3 = sqrt(pow(tempx, 2.0) + pow(tempy, 2.0));
	double theta3 = Utils::fixed_atan2(tempy, tempx) + arg;
	double x3 = r3 * cos(theta3) + emit_pos.x;
	double y3 = r3 * sin(theta3) + emit_pos.y;

	double r4 = width / 2.0;
	double theta4 = 1.0 / 2.0 * pi + arg;
	double x4 = r4 * cos(theta4) + emit_pos.x;
	double y4 = r4 * sin(theta4) + emit_pos.y;

	InFieldPosition vert1(x1, y1);
	InFieldPosition vert2(x2, y2);
	InFieldPosition vert3(x3, y3);
	InFieldPosition vert4(x4, y4);

	vector<InFieldPosition> vertices;
	vertices.push_back(vert1);
	vertices.push_back(vert2);
	vertices.push_back(vert3);
	vertices.push_back(vert4);

	collidant = make_unique<CollidePolygon>(vertices);
}


void PolarLaser::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	double tempx;
	double tempy;

	double r1 = width / 2.0;
	double theta1 = -1.0 / 2.0 * pi + arg;
	double x1 = r1 * cos(theta1) + emit_pos.x;
	double y1 = r1 * sin(theta1) + emit_pos.y;

	tempx = length;
	tempy = -(width / 2.0);
	double r2 = sqrt(pow(tempx, 2.0) + pow(tempy, 2.0));
	double theta2 = Utils::fixed_atan2(tempy, tempx) + arg;
	double x2 = r2 * cos(theta2) + emit_pos.x;
	double y2 = r2 * sin(theta2) + emit_pos.y;

	tempx = length;
	tempy = width / 2.0;
	double r3 = sqrt(pow(tempx, 2.0) + pow(tempy, 2.0));
	double theta3 = Utils::fixed_atan2(tempy, tempx) + arg;
	double x3 = r3 * cos(theta3) + emit_pos.x;
	double y3 = r3 * sin(theta3) + emit_pos.y;

	double r4 = width / 2.0;
	double theta4 = 1.0 / 2.0 * pi + arg;
	double x4 = r4 * cos(theta4) + emit_pos.x;
	double y4 = r4 * sin(theta4) + emit_pos.y;

	InFieldPosition vert1(x1, y1);
	InFieldPosition vert2(x2, y2);
	InFieldPosition vert3(x3, y3);
	InFieldPosition vert4(x4, y4);

	vector<InFieldPosition> vertices;
	vertices.push_back(vert1);
	vertices.push_back(vert2);
	vertices.push_back(vert3);
	vertices.push_back(vert4);

	collidant->update(vertices);
}


void PolarLaser::draw() {
	int frame_update_delta_time = DxLib::GetNowCount() - last_frame_updated_clock;

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