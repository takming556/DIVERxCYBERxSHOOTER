#include <numbers>
#include <cmath>
#include <memory>
#include <vector>
#include "DebugParams.h"
#include "Utils.h"
#include "Offensive/Laser/PolarLaser.h"
#include "CollideRealm/CollidePolygon.h"
#include "ImageHandles.h"

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
	Offensive(given_skin_id),
	Laser(init_dps, init_active_flag),
	emit_pos(InFieldPosition(init_emit_pos_x, init_emit_pos_y)),
	arg(init_arg),
	length(init_length),
	width(init_width)
{
	vector<InFieldPosition> vertices;
	vertices.push_back(get_vert1_pos());
	vertices.push_back(get_vert2_pos());
	vertices.push_back(get_vert3_pos());
	vertices.push_back(get_vert4_pos());
	collidant = make_unique<CollidePolygon>(vertices);
}


InFieldPosition PolarLaser::get_vert1_pos() {
	double r1 = width / 2.0;
	double theta1 = -1.0 / 2.0 * pi + arg;
	double x1 = r1 * cos(theta1) + emit_pos.x;
	double y1 = r1 * sin(theta1) + emit_pos.y;
	return InFieldPosition(x1, y1);
}


InFieldPosition PolarLaser::get_vert2_pos() {
	double tempx = length;
	double tempy = -(width / 2.0);
	double r2 = sqrt(pow(tempx, 2.0) + pow(tempy, 2.0));
	double theta2 = Utils::fixed_atan2(tempy, tempx) + arg;
	double x2 = r2 * cos(theta2) + emit_pos.x;
	double y2 = r2 * sin(theta2) + emit_pos.y;
	return InFieldPosition(x2, y2);
}


InFieldPosition PolarLaser::get_vert3_pos() {
	double tempx = length;
	double tempy = width / 2.0;
	double r3 = sqrt(pow(tempx, 2.0) + pow(tempy, 2.0));
	double theta3 = Utils::fixed_atan2(tempy, tempx) + arg;
	double x3 = r3 * cos(theta3) + emit_pos.x;
	double y3 = r3 * sin(theta3) + emit_pos.y;
	return InFieldPosition(x3, y3);
}


InFieldPosition PolarLaser::get_vert4_pos() {
	double r4 = width / 2.0;
	double theta4 = 1.0 / 2.0 * pi + arg;
	double x4 = r4 * cos(theta4) + emit_pos.x;
	double y4 = r4 * sin(theta4) + emit_pos.y;
	return InFieldPosition(x4, y4);
}


void PolarLaser::update() {
	vector<InFieldPosition> vertices;
	vertices.push_back(get_vert1_pos());
	vertices.push_back(get_vert2_pos());
	vertices.push_back(get_vert3_pos());
	vertices.push_back(get_vert4_pos());
	collidant->update(vertices);
}


void PolarLaser::draw() {
	if (is_active() == true) {
		switch (skin_id) {
		case SkinID::NEON_NM2_LASER:
			image_handles = ImageHandles::LASER_FUCHSIA;
			break;
		case SkinID::NEON_SP2_LASER:
			image_handles = ImageHandles::LASER_YELLOW;
			break;
		default:
			image_handles = ImageHandles::LASER_FUCHSIA;
			break;
		}
		DxLib::DrawModiGraph(
			get_vert1_pos().get_draw_position().x,
			get_vert1_pos().get_draw_position().y,
			get_vert2_pos().get_draw_position().x,
			get_vert2_pos().get_draw_position().y,
			get_vert3_pos().get_draw_position().x,
			get_vert3_pos().get_draw_position().y,
			get_vert4_pos().get_draw_position().x,
			get_vert4_pos().get_draw_position().y,
			image_handles,
			TRUE
		);

		if (DebugParams::DEBUG_FLAG == true) collidant->draw();
	}
}


void PolarLaser::set_emit_pos(double alt_emit_pos_x, double alt_emit_pos_y) {
	emit_pos = InFieldPosition(alt_emit_pos_x, alt_emit_pos_y);
}


void PolarLaser::set_emit_pos(InFieldPosition alt_emit_pos) {
	emit_pos = alt_emit_pos;
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