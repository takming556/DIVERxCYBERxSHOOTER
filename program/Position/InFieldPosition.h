#pragma once
#include "Position/Position.h"


class InFieldPosition : public Position {
private:
	static const int DRAW_POS_OFFSET_X;
	static const int DRAW_POS_OFFSET_Y;
public:
	InFieldPosition(double init_x, double init_y);
	InFieldPosition();
	Position get_draw_position();
	static Position GET_DRAW_POSITION(double given_infieldpos_x, double given_infieldpos_y);
	static const double MIN_MOVABLE_BOUNDARY_X;
	static const double MIN_MOVABLE_BOUNDARY_Y;
	static const double MAX_MOVABLE_BOUNDARY_X;
	static const double MAX_MOVABLE_BOUNDARY_Y;
	static const double MIN_EXISTENCE_BOUNDARY_X;
	static const double MIN_EXISTENCE_BOUNDARY_Y;
	static const double MAX_EXISTENCE_BOUNDARY_X;
	static const double MAX_EXISTENCE_BOUNDARY_Y;
	static void DRAW_MOVABLE_BOUNDARY();
	static void DRAW_EXISTENCE_BOUNDARY();
};