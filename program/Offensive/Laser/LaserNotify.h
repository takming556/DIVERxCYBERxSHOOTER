#pragma once
#include "DxLib.h"

using std::unique_ptr;
using LaserNotifyID = unsigned int;

class LaserNotify {
protected:
	static LaserNotifyID NEXT_ID;
private:
	InFieldPosition emit_pos;
	double arg;
	unsigned int length;
	unsigned int width;
	unsigned int color;
	unsigned int emit_time;
	Position draw_position_top_left;
	Position draw_position_top_right;
	Position draw_position_bottom_right;
	Position draw_position_bottom_left;
	unsigned int emit_start_clock;
	unsigned int emit_end_clock;
public:
	LaserNotify(
		double init_emit_pos_x,
		double init_emit_pos_y,
		double init_arg,
		unsigned int init_length,
		unsigned int init_width,
		unsigned int init_color,
		unsigned int init_emit_time
	);
	static void INITIALIZE();
	void update();
	void draw();
	static LaserNotifyID GENERATE_ID();
};