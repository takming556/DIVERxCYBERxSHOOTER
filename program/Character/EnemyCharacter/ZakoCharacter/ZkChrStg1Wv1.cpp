#include <memory>
#include <cmath>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;
using std::sin;
using std::cos;


const unsigned int ZkChrStg1Wv1::TICKS = 3;
const unsigned int ZkChrStg1Wv1::SHOTS = 4;
const unsigned int ZkChrStg1Wv1::TICK_INTERVAL = 125;
const unsigned int ZkChrStg1Wv1::SHOT_INTERVAL = 2000;
const unsigned int ZkChrStg1Wv1::INITIAL_HP = 5;
const unsigned int ZkChrStg1Wv1::COLLIDANT_SIZE = 20;



ZkChrStg1Wv1::ZkChrStg1Wv1(int init_pos_x, int init_pos_y, double init_arg, double init_speed) :
	Character(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)),
	EnemyCharacter(INITIAL_HP),
	speed(init_speed),
	arg(init_arg),
	tick_count(0),
	shot_count(0),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_shot_completed_clock(DxLib::GetNowCount()),
	last_tick_fired_clock(DxLib::GetNowCount())
{
}


void ZkChrStg1Wv1::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	if (shot_count < SHOTS) {
		if (tick_count < TICKS) {
			int tick_fire_delta_time = DxLib::GetNowCount() - last_tick_fired_clock;
			if (tick_fire_delta_time > TICK_INTERVAL) {

				unique_ptr<Offensive> straight_shot = make_unique<HomingShot>(position->x, position->y, (1.0 / 2.0) * pi, 200, 20, 1, SkinID::NORMAL_BLUE);
				Field::ENEMY_OFFENSIVES->push_back(move(straight_shot));

				++tick_count;
				last_tick_fired_clock = DxLib::GetNowCount();
			}
		}
		else {
			int shot_complete_delta_time = DxLib::GetNowCount() - last_shot_completed_clock;
			if (shot_complete_delta_time > SHOT_INTERVAL) {
				++shot_count;
				tick_count = 0;
				last_shot_completed_clock = DxLib::GetNowCount();
			}
		}
	}

}


void ZkChrStg1Wv1::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, 0, ImageHandles::KURAGE, TRUE);
	collidant->draw();
}