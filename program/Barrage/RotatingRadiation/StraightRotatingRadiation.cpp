#include <memory>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;

StraightRotatingRadiation::StraightRotatingRadiation
(
	double init_pos_x,
	double init_pos_y,
	double init_emit_arg,
	double given_rotate_speed,
	unsigned int given_emit_nozzles,
	unsigned int given_emits,
	unsigned int given_emit_interval,
	double given_shot_speed,
	unsigned int given_collidant_size,
	unsigned int given_durability,
	enum TeamID given_team_id,
	enum SkinID given_skin_id
):
	RotatingRadiation(init_pos_x, init_pos_y, given_rotate_speed, given_emit_nozzles),
	giving_speed(given_shot_speed),
	giving_collidant_size(given_collidant_size),
	giving_durability(given_durability),
	giving_skin_id(given_skin_id),
	perform_completed_flag(false),
	rotate_speed(given_rotate_speed),
	emit_arg(init_emit_arg),
	emits(given_emits),
	emit_count(0),
	emit_interval(given_emit_interval),
	last_emitted_clock(DxLib::GetNowCount()),
	team_id(given_team_id)
{
}


void StraightRotatingRadiation::update() {

}