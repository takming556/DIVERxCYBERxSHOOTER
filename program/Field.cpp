#include "DxLib.h"
#include "class.h"
#include "extern.h"

const double Field::FIELD_DRAW_EXTRATE = 1.0;

Field::Field() {
}


void Field::draw() {
	DrawRotaGraph(FIELD_DRAW_POSITION_X, FIELD_DRAW_POSITION_Y, 1.0, 0, hFieldBackground, TRUE);
}