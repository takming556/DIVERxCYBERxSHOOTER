#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/MyCharacter/Ichigochan.h"
#include "CollideRealm/CollideCircle.h"
#include "ImageHandles.h"
#include "DebugParams.h"


using std::make_unique;

const string IchigoChan::CHARACTER_NAME("いちごちゃん");
const double IchigoChan::DRAW_EXTRATE = 0.05;

IchigoChan::IchigoChan() :
	Character(
		CharacterID::ICHIGO_CHAN,
		MyCharacter::INITIAL_POSITION_X,
		MyCharacter::INITIAL_POSITION_Y,
		MyCharacter::INITIAL_HP,
		make_unique<CollideCircle>(MyCharacter::INITIAL_POSITION_X, MyCharacter::INITIAL_POSITION_Y, MyCharacter::COLLIDANT_SIZE)
	),
	MyCharacter(CHARACTER_NAME)
{
}


void IchigoChan::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ICHIGOCHAN, TRUE);
	if (DebugParams::DEBUG_FLAG == true || MyCharacter::SLOWMOVE_FLAG == true) collidant->draw();
}