#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Barrage/Emission/StraightShotEmission/SimpleStraightShotEmission.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "SoundHandles.h"

using std::unique_ptr;
using std::make_unique;
using std::numbers::pi;

SimpleStraightShotEmission::SimpleStraightShotEmission(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	bool given_emit_unlimited_flag,
	unsigned int given_emits,
	unsigned int given_emit_nozzles,
	unsigned int given_emit_interval,
	double given_shot_speed,
	unsigned int given_shot_collidant_size,
	unsigned int given_shot_durability,
	enum TeamID given_shot_team_id,
	enum SkinID given_shot_skin_id
) :
	x(init_pos_x),
	y(init_pos_y),
	arg(init_arg),
	emit_unlimited_flag(given_emit_unlimited_flag),
	emits(given_emits),
	emit_nozzles(given_emit_nozzles),
	emit_interval(given_emit_interval),
	emit_count(0),
	last_emitted_clock(DxLib::GetNowCount()),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	shot_speed(given_shot_speed),
	shot_collidant_size(given_shot_collidant_size),
	shot_durability(given_shot_durability),
	shot_team_id(given_shot_team_id),
	shot_skin_id(given_shot_skin_id)
{
}


void SimpleStraightShotEmission::update(double upd_pos_x, double upd_pos_y) {

	x = upd_pos_x;
	y = upd_pos_y;

	if ((emit_count < emits || emit_unlimited_flag == true) && DxLib::GetNowCount() > last_emitted_clock + emit_interval) {
		emit();
		++emit_count;
		last_emitted_clock = DxLib::GetNowCount();
	}
}


void SimpleStraightShotEmission::emit() {
	for (int i = 0; i < emit_nozzles; i++) {
		double this_arg = 2 * pi / emit_nozzles * i + arg;
		if (shot_team_id == TeamID::MY) {
			(*Field::MY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
				x,
				y,
				this_arg,
				shot_speed,
				shot_collidant_size,
				shot_durability,
				shot_skin_id
			);
			//Field::MY_BULLETS->push_back(make_unique<StraightShot>(
			//	x,
			//	y,
			//	this_arg,
			//	shot_speed,
			//	shot_collidant_size,
			//	shot_durability,
			//	shot_skin_id
			//	)
			//);
		}
		else if (shot_team_id == TeamID::ENEMY) {
			(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
				x,
				y,
				this_arg,
				shot_speed,
				shot_collidant_size,
				shot_durability,
				shot_skin_id
			);
			//Field::ENEMY_BULLETS->push_back(make_unique<StraightShot>(
			//	x,
			//	y,
			//	this_arg,
			//	shot_speed,
			//	shot_collidant_size,
			//	shot_durability,
			//	shot_skin_id
			//	)
			//);
		}

		DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

	}
	int emit_delta_time = DxLib::GetNowCount() - last_emitted_clock;
}