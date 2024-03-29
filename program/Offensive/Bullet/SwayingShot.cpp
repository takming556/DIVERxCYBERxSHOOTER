﻿#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Offensive/Bullet/SwayingShot.h"
#include "ImageHandles.h"
#include "DebugParams.h"
#include "Colors.h"

using std::sin;
using std::cos;
using std::atan;
using std::numbers::pi;


SwayingShot::SwayingShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	double sway_intensity,
	double sway_frequency,
	unsigned int collidant_size,
	unsigned int durability,
	SkinID given_skin_id
) :
	Offensive(given_skin_id),
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability, collidant_size),
	sway_intensity(sway_intensity),
	sway_frequency(sway_frequency),
	initial_arg(init_arg),
	theta(0)
{
}


void SwayingShot::update() {

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	theta += 2 * pi * update_delta_time * sway_frequency / 1000 / 1000;
	arg = initial_arg + sway_intensity * pi * cos(theta);
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}


void SwayingShot::draw() {
	Position draw_pos = position->get_draw_position();

	switch (skin_id) {
	//case SkinID::ICHIGO_CHAN:
	//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, -arg, ImageHandles::HEART, TRUE);
	//	break;

	//case SkinID::NORMAL_BLUE:
	//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BLUE_MARBLE, TRUE);
	//	break;

	case SkinID::BUBBLE_GENERIC:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_AQUA, TRUE);
		break;

	//case SkinID::KUNAI_RED:
	//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::ORANGE_TRIANGLE, TRUE);
	//	break;
	}

	if (DebugParams::DEBUG_FLAG == true) {
		DxLib::DrawFormatString(draw_pos.x + 15, draw_pos.y - 7, Colors::RED, L"%lf", theta / pi);
		DxLib::DrawFormatString(draw_pos.x + 15, draw_pos.y + 8, Colors::GREEN, L"%lf", arg / pi);
	}
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}