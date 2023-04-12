#include <vector>
#include <memory>
#include "DxLib.h"
#include "Character/Character.h"

using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::move;


Character::Character(int init_pos_x, int init_pos_y, unique_ptr<CollideRealm> given_collidant) :
	position(make_unique<InFieldPosition>((double)init_pos_x, (double)init_pos_y)),
	collidant(move(given_collidant)),
	last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
}


Character::~Character() = default;


//bool Character::check_collision_with(unique_ptr<vector<unique_ptr<Offensive>>>& given_offensives) {
//	bool is_collided_with_no_less_than_one_offensive = false;
//	for (const auto& given_offensive : *given_offensives) {
//		if (collidant->is_collided_with(given_offensive->collidant)) is_collided_with_no_less_than_one_offensive = true;
//	}
//	return is_collided_with_no_less_than_one_offensive;
//}