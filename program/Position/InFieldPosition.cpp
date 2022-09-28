#include "class.h"

InFieldPosition::InFieldPosition(double init_x, double init_y) :
	Position(init_x, init_y)
{
}


Position InFieldPosition::get_draw_position() {
	double distance_from_center_y = Field::FIELD_DRAW_POSITION_Y - y;

	double draw_pos_x = x + Field::FIELD_DRAW_POSITION_X + DRAW_POS_OFFSET_X;
	double draw_pos_y = y + Field::FIELD_DRAW_POSITION_Y + DRAW_POS_OFFSET_Y + distance_from_center_y * 2;
	return Position(draw_pos_x, draw_pos_y);
}