#include <numbers>
#include <cmath>
#include "DxLib.h"
#include "Field.h"
#include "Offensive/Laser/LaserNotify.h"
#include "Colors.h"

using std::sin;
using std::cos;

LaserNotifyID LaserNotify::NEXT_ID;

LaserNotify::LaserNotify(
	double init_emit_pos_x,
	double init_emit_pos_y,
	double init_arg,
	unsigned int init_length,
	unsigned int init_width,
	unsigned int init_color,
	unsigned int init_emit_time
) :
	emit_pos(InFieldPosition(init_emit_pos_x, init_emit_pos_y)),
	arg(init_arg),
	length(init_length),
	width(init_width),
	color(init_color),
	emit_time(init_emit_time),
	emit_start_clock(DxLib::GetNowCount()),
	emit_end_clock(DxLib::GetNowCount())
	//position_top_left(Position(0,0)),
	//position_top_right(Position(0,0)),
	//position_bottom_right(Position(0,0)),
	//position_bottom_left(Position(0,0))
{
	double nm2_laser_notify_end_x = emit_pos.x + cos(arg) * length;
	double nm2_laser_notify_end_y = emit_pos.y + sin(arg) * length;
	InFieldPosition position_end(nm2_laser_notify_end_x, nm2_laser_notify_end_y);			// InFieldPositionで終端座標の算出

	InFieldPosition position_top_left(
		emit_pos.x + sin(arg) * width / 2.0,
		emit_pos.y - cos(arg) * width / 2.0
	);
	InFieldPosition position_top_right(
		emit_pos.x - sin(arg) * width / 2.0,
		emit_pos.y + cos(arg) * width / 2.0
	);
	InFieldPosition position_bottom_right(
		position_end.x - sin(arg) * width / 2.0,
		position_end.y + cos(arg) * width / 2.0
	);
	InFieldPosition position_bottom_left(
		position_end.x + sin(arg) * width / 2.0,
		position_end.y - cos(arg) * width / 2.0
	);

	draw_position_top_left = position_top_left.get_draw_position();				// InFieldPostionからPositionに変換
	draw_position_top_right = position_top_right.get_draw_position();
	draw_position_bottom_right = position_bottom_right.get_draw_position();
	draw_position_bottom_left = position_bottom_left.get_draw_position();

	emit_start_clock = DxLib::GetNowCount();
	emit_end_clock = emit_start_clock + emit_time;
}

void LaserNotify::INITIALIZE() {
	NEXT_ID = 0;
}

LaserNotifyID LaserNotify::GENERATE_ID() {
	unsigned int generated_id = NEXT_ID;
	++NEXT_ID;
	return generated_id;
}

void LaserNotify::update(){
	/*int elapsed_time = DxLib::GetNowCount() - emit_start_clock;
	if (elapsed_time < emit_end_clock) {
		draw();
	}*/
}

void LaserNotify::draw() {
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DxLib::DrawQuadrangle(
		draw_position_top_left.x, draw_position_top_left.y,
		draw_position_top_right.x, draw_position_top_right.y,
		draw_position_bottom_right.x, draw_position_bottom_right.y,
		draw_position_bottom_left.x, draw_position_bottom_left.y,
		color,
		true
	);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}