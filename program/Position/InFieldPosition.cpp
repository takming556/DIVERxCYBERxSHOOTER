#include "DxLib.h"
#include "InFieldPosition.h"
#include "Field.h"
#include "Colors.h"

const int InFieldPosition::DRAW_POS_OFFSET_X = -(Field::PIXEL_SIZE_X / 2);
const int InFieldPosition::DRAW_POS_OFFSET_Y = -(Field::PIXEL_SIZE_Y / 2);
const double InFieldPosition::MIN_MOVABLE_BOUNDARY_X = 0;
const double InFieldPosition::MIN_MOVABLE_BOUNDARY_Y = 0;
const double InFieldPosition::MAX_MOVABLE_BOUNDARY_X = 620;
const double InFieldPosition::MAX_MOVABLE_BOUNDARY_Y = 742;
const double InFieldPosition::MIN_EXISTENCE_BOUNDARY_X = InFieldPosition::MIN_MOVABLE_BOUNDARY_X - (InFieldPosition::MAX_MOVABLE_BOUNDARY_X - InFieldPosition::MIN_MOVABLE_BOUNDARY_X) / 4;
const double InFieldPosition::MIN_EXISTENCE_BOUNDARY_Y = InFieldPosition::MIN_MOVABLE_BOUNDARY_Y - (InFieldPosition::MAX_MOVABLE_BOUNDARY_Y - InFieldPosition::MIN_MOVABLE_BOUNDARY_Y) / 4;
const double InFieldPosition::MAX_EXISTENCE_BOUNDARY_X = InFieldPosition::MAX_MOVABLE_BOUNDARY_X + (InFieldPosition::MAX_MOVABLE_BOUNDARY_X - InFieldPosition::MIN_MOVABLE_BOUNDARY_X) / 4;
const double InFieldPosition::MAX_EXISTENCE_BOUNDARY_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y + (InFieldPosition::MAX_MOVABLE_BOUNDARY_Y - InFieldPosition::MIN_MOVABLE_BOUNDARY_Y) / 4;


InFieldPosition::InFieldPosition(double init_x, double init_y) :
	Position(init_x, init_y)
{
}


Position InFieldPosition::get_draw_position() {
	double draw_pos_x = x + Field::DRAW_POSITION_X - Field::PIXEL_SIZE_X / 2;
	double draw_pos_y = -y + Field::DRAW_POSITION_Y + Field::PIXEL_SIZE_Y / 2;
	return Position(draw_pos_x, draw_pos_y);

}


Position InFieldPosition::GET_DRAW_POSITION(double given_infieldpos_x, double given_infieldpos_y) {
	double draw_pos_x = given_infieldpos_x + Field::DRAW_POSITION_X - Field::PIXEL_SIZE_X / 2;
	double draw_pos_y = -given_infieldpos_y + Field::DRAW_POSITION_Y + Field::PIXEL_SIZE_Y / 2;
	return Position(draw_pos_x, draw_pos_y);
}


void InFieldPosition::DRAW_MOVABLE_BOUNDARY() {
	Position MIN_VISIBLE_BOUNDARY = GET_DRAW_POSITION(MIN_MOVABLE_BOUNDARY_X, MIN_MOVABLE_BOUNDARY_Y);
	Position MAX_VISIBLE_BOUNDARY = GET_DRAW_POSITION(MAX_MOVABLE_BOUNDARY_X, MAX_MOVABLE_BOUNDARY_Y);
	DxLib::DrawBoxAA(
		MIN_VISIBLE_BOUNDARY.x, 
		MIN_VISIBLE_BOUNDARY.y, 
		MAX_VISIBLE_BOUNDARY.x, 
		MAX_VISIBLE_BOUNDARY.y, 
		Colors::MAZENTA, 
		FALSE, 
		2.0F
	);
}


void InFieldPosition::DRAW_EXISTENCE_BOUNDARY() {
	Position MIN_EXISTENCE_BOUNDARY = GET_DRAW_POSITION(MIN_EXISTENCE_BOUNDARY_X, MIN_EXISTENCE_BOUNDARY_Y);
	Position MAX_EXISTENCE_BOUNDARY = GET_DRAW_POSITION(MAX_EXISTENCE_BOUNDARY_X, MAX_EXISTENCE_BOUNDARY_Y);
	DxLib::DrawBoxAA(
		MIN_EXISTENCE_BOUNDARY.x,
		MIN_EXISTENCE_BOUNDARY.y,
		MAX_EXISTENCE_BOUNDARY.x,
		MAX_EXISTENCE_BOUNDARY.y,
		Colors::MAZENTA,
		FALSE,
		2.0F
	);
}