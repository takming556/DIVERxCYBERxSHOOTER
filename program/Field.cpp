#include <memory>
#include "DxLib.h"
#include "class.h"
#include "extern.h"

using std::make_unique;

const double Field::FIELD_DRAW_EXTRATE = 1.0;

Field::Field() :
	my_character(make_unique<MyCharacter1>())
{
}


void Field::update() {
}


void Field::draw() {
	DrawRotaGraph(FIELD_DRAW_POSITION_X, FIELD_DRAW_POSITION_Y, 1.0, 0, hFieldBackground, TRUE);
	my_character->draw();
}