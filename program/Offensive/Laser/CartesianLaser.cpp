#include <cmath>
#include <numbers>
#include <vector>
#include <memory>
#include "DxLib.h"
#include "Offensive/Laser/CartesianLaser.h"
#include "ImageHandles.h"
#include "Utils.h"
#include "DebugParams.h"

using std::make_unique;
using std::vector;
using std::numbers::pi;
using std::sin;
using std::cos;



CartesianLaser::CartesianLaser(
	double init_begin_pos_x,
	double init_begin_pos_y,
	double init_end_pos_x,
	double init_end_pos_y,
	double init_width,
	double init_dps,
	bool init_active_flag,
	SkinID given_skin_id
):
	Offensive(given_skin_id),
	Laser(init_dps, init_active_flag),
	begin_pos(InFieldPosition(init_begin_pos_x, init_begin_pos_y)),
	end_pos(InFieldPosition(init_end_pos_x, init_end_pos_y)),
	width(init_width)
{
	vector<InFieldPosition> vertices;
	vertices.push_back(get_vert1_pos());
	vertices.push_back(get_vert2_pos());
	vertices.push_back(get_vert3_pos());
	vertices.push_back(get_vert4_pos());

	collidant = make_unique<CollidePolygon>(vertices);
}


InFieldPosition CartesianLaser::get_vert1_pos() {
	double tempx = end_pos.x - begin_pos.x;
	double tempy = end_pos.y - begin_pos.y;
	double arg = Utils::fixed_atan2(tempy, tempx);
	double r = width / 2.0;
	double theta1 = -1.0 / 2.0 * pi + arg;
	double x1 = r * cos(theta1) + begin_pos.x;
	double y1 = r * sin(theta1) + begin_pos.y;
	return InFieldPosition(x1, y1);
}


InFieldPosition CartesianLaser::get_vert2_pos() {
	double tempx = end_pos.x - begin_pos.x;
	double tempy = end_pos.y - begin_pos.y;
	double arg = Utils::fixed_atan2(tempy, tempx);
	double r = width / 2.0;
	double theta2 = -1.0 / 2.0 * pi + arg;
	double x2 = r * cos(theta2) + end_pos.x;
	double y2 = r * sin(theta2) + end_pos.y;
	return InFieldPosition(x2, y2);
}


InFieldPosition CartesianLaser::get_vert3_pos() {
	double tempx = end_pos.x - begin_pos.x;
	double tempy = end_pos.y - begin_pos.y;
	double arg = Utils::fixed_atan2(tempy, tempx);
	double r = width / 2.0;
	double theta3 = 1.0 / 2.0 * pi + arg;
	double x3 = r * cos(theta3) + end_pos.x;
	double y3 = r * sin(theta3) + end_pos.y;
	return InFieldPosition(x3, y3);
}


InFieldPosition CartesianLaser::get_vert4_pos() {
	double tempx = end_pos.x - begin_pos.x;
	double tempy = end_pos.y - begin_pos.y;
	double arg = Utils::fixed_atan2(tempy, tempx);
	double r = width / 2.0;
	double theta4 = 1.0 / 2.0 * pi + arg;
	double x4 = r * cos(theta4) + begin_pos.x;
	double y4 = r * sin(theta4) + begin_pos.y;
	return InFieldPosition(x4, y4);
}


void CartesianLaser::update() {
	vector<InFieldPosition> vertices;
	vertices.push_back(get_vert1_pos());
	vertices.push_back(get_vert2_pos());
	vertices.push_back(get_vert3_pos());
	vertices.push_back(get_vert4_pos());
	collidant->update(vertices);
}


void CartesianLaser::draw(){
	if (is_active() == true) {

		int image_handle;

		switch (skin_id) {
		case SkinID::TOROI_SP3_SLASH:
			image_handle = ImageHandles::LASER_RED;
			break;

		case SkinID::TOROI_SP3_BESIEGE:
			image_handle = ImageHandles::LASER_PURPLE;
			break;
		default:
			image_handle = ImageHandles::LASER_AQUA;
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
			image_handle,
			TRUE
		);

		if (DebugParams::DEBUG_FLAG == true) collidant->draw();

	}
}


void CartesianLaser::set_begin_pos(double alt_begin_pos_x, double alt_begin_pos_y) {
	begin_pos = InFieldPosition(alt_begin_pos_x, alt_begin_pos_y);
}


void CartesianLaser::set_begin_pos(InFieldPosition alt_begin_pos) {
	begin_pos = alt_begin_pos;
}


void CartesianLaser::set_end_pos(double alt_end_pos_x, double alt_end_pos_y) {
	end_pos = InFieldPosition(alt_end_pos_x, alt_end_pos_y);
}


void CartesianLaser::set_end_pos(InFieldPosition alt_end_pos) {
	end_pos = alt_end_pos;
}


void CartesianLaser::set_pos(double alt_begin_pos_x, double alt_begin_pos_y, double alt_end_pos_x, double alt_end_pos_y) {
	begin_pos = InFieldPosition(alt_begin_pos_x, alt_begin_pos_y);
	end_pos = InFieldPosition(alt_end_pos_x, alt_end_pos_y);
}


void CartesianLaser::set_pos(InFieldPosition alt_begin_pos, InFieldPosition alt_end_pos) {
	begin_pos = alt_begin_pos;
	end_pos = alt_end_pos;
}


void CartesianLaser::set_width(double alt_width) {
	width = alt_width;
}


void CartesianLaser::set_dps(double alt_dps) {
	dps = alt_dps;
}