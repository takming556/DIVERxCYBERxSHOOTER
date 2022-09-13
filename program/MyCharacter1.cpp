#include "DxLib.h"
#include "class.h"
#include "extern.h"


const string MyCharacter1::character_name("ƒfƒWq");

MyCharacter1::MyCharacter1() :
	MyCharacter(character_name)
{
}


void MyCharacter1::draw() {
	Position draw_pos = position->get_draw_position();
	DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, 0, hHandPower, TRUE);
	collidant->draw();
}