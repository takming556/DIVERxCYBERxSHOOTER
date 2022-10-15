#include "class.h"


const int InFieldPosition::DRAW_POS_OFFSET_X = -(Field::PIXEL_SIZE_X / 2);
const int InFieldPosition::DRAW_POS_OFFSET_Y = -(Field::PIXEL_SIZE_Y / 2);



InFieldPosition::InFieldPosition(double init_x, double init_y) :
	Position(init_x, init_y)
{
}


Position InFieldPosition::get_draw_position() {
	double distance_from_center_y = Field::DRAW_POSITION_Y - y;

	double draw_pos_x = x + Field::DRAW_POSITION_X + DRAW_POS_OFFSET_X;
	double draw_pos_y = y + Field::DRAW_POSITION_Y + DRAW_POS_OFFSET_Y + distance_from_center_y * 2;
	return Position(draw_pos_x, draw_pos_y);
}