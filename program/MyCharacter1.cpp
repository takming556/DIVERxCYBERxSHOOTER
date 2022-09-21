#include <memory>
#include "DxLib.h"
#include "class.h"
#include "extern.h"

using std::make_unique;

const string MyCharacter1::CHARACTER_NAME("ƒfƒWŽq");

MyCharacter1::MyCharacter1() :
	Character(MyCharacter::INITIAL_POSITION_X, MyCharacter::INITIAL_POSITION_Y, make_unique<CollideCircle>(MyCharacter::INITIAL_POSITION_X, MyCharacter::INITIAL_POSITION_Y, MyCharacter::COLLIDANT_SIZE)),
	MyCharacter(CHARACTER_NAME)
{
}


void MyCharacter1::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, 0, ImageHandles::HAND_POWER, TRUE);
	collidant->draw();
}