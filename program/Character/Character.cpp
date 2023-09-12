#include <vector>
#include <memory>
#include "DxLib.h"
#include "enum.h"
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
	unique_ptr<CollideRealm> given_collidant
) :
	position(make_unique<InFieldPosition>(init_pos_x, init_pos_y)),
	collidant(move(given_collidant)),
	last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
}


Character::~Character() = default;