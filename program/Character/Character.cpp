#include <vector>
#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "Colors.h"
#include "Character/Character.h"
#include "CollideRealm/CollideCircle.h"

using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::move;


Character::Character(
	enum CharacterID givenId,
	double initPosX,
	double initPosY,
	int initHp,
	unique_ptr<CollideCircle> givenCollidant
) :
	hp(initHp),
	id(givenId),
	position(make_unique<InFieldPosition>(initPosX, initPosY)),
	collidant(move(givenCollidant)),
	lastUpdatedClock(DxLib::GetNowHiPerformanceCount())
{
}


Character::~Character() = default;

void Character::DrawHp() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::RED, L"%d", hp);
}

bool Character::IsDead() const {
	if (hp <= 0)
		return true;
	else
		return false;
}