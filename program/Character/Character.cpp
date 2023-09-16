#include <vector>
#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "Colors.h"
#include "Character/Character.h"

using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::move;


Character::Character(
	enum CharacterID given_id,
	double init_pos_x,
	double init_pos_y,
	int init_hp,
	unique_ptr<CollideRealm> given_collidant
) :
	hp(init_hp),
	id(given_id),
	position(make_unique<InFieldPosition>(init_pos_x, init_pos_y)),
	collidant(move(given_collidant)),
	last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
}


Character::~Character() = default;


void Character::draw_hp() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::RED, L"%d", hp);
}


bool Character::is_dead() {
	return hp <= 0;
}