#include <memory>
#include "DxLib.h"
#include "class.h"
#include "extern.h"

using std::make_unique;

const string IchigoChan::CHARACTER_NAME("‚¢‚¿‚²‚¿‚á‚ñ");
const double IchigoChan::DRAW_EXTRATE = 0.05;

IchigoChan::IchigoChan() :
	Character(MyCharacter::INITIAL_POSITION_X, MyCharacter::INITIAL_POSITION_Y, make_unique<CollideCircle>(MyCharacter::INITIAL_POSITION_X, MyCharacter::INITIAL_POSITION_Y, MyCharacter::COLLIDANT_SIZE)),
	MyCharacter(CHARACTER_NAME)
{
}


void IchigoChan::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ICHIGOCHAN, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}