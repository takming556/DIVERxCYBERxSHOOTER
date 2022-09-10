#include "DxLib.h"
#include "class.h"
#include "extern.h"

MyCharacter1::MyCharacter1() :
	MyCharacter(character_name)
{
}


void MyCharacter1::draw() {
	int draw_pos_x = Field::FIELD_DRAW_POSITION_X + position_x;
	int draw_pos_y = Field::FIELD_DRAW_POSITION_Y + position_y;
	DrawRotaGraph(draw_pos_x, draw_pos_y, 1.0, 0, hPien, TRUE);
}