#include <memory>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;

const unsigned int ZkChrStg1Wv2::SHOTS = 3;
const unsigned int ZkChrStg1Wv2::SHOT_INTERVAL = 2000;
const unsigned int ZkChrStg1Wv2::INITIAL_HP = 5;
const unsigned int ZkChrStg1Wv2::COLLIDANT_SIZE = 20;

ZkChrStg1Wv2::ZkChrStg1Wv2(double init_pos_x, double init_pos_y, double init_arg, double init_speed) :
	speed(init_speed),
	arg(init_arg),
	//tick_count(0),
	shot_count(0),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_shot_completed_clock(DxLib::GetNowCount())
	//last_tick_fired_clock(DxLib::GetNowCount())
{
}


void ZkChrStg1Wv2::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	if (shot_count < SHOTS) {

		int shot_complete_delta_time = DxLib::GetNowCount() - last_shot_completed_clock;
		if (shot_complete_delta_time > SHOT_INTERVAL) {

			unique_ptr<Offensive> straight_shot = make_unique<StraightShot>(position->x, position->y, arg_toward_mychr, 200, 20, 1, SkinID::NORMAL_BLUE);
			Field::ENEMY_OFFENSIVES->push_back(move(straight_shot));

			++shot_count;
			last_shot_completed_clock = DxLib::GetNowCount();
		}
	}

}