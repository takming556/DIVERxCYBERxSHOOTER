#include <memory>
#include <cmath>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;
using std::sin;
using std::cos;


ZkChrStg1Wv1::ZkChrStg1Wv1(int init_pos_x, int init_pos_y, double init_arg, double init_speed) :
	Character(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)),
	EnemyCharacter(INITIAL_HP),
	speed(init_speed),
	arg(init_arg),
	tick_count(0),
	shot_count(0),
	previously_updated_clock(1),
	previously_shot_completed_clock(0),
	previously_tick_fired_clock(0)
{
}


void ZkChrStg1Wv1::update() {
	LONGLONG elapsed_time_since_previously_updated = DxLib::GetNowHiPerformanceCount() - previously_updated_clock;
	double distance = speed * elapsed_time_since_previously_updated / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	previously_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	if (shot_count < SHOTS) {
		if (tick_count < TICKS) {
			int elapsed_time_since_previously_tick_fired = DxLib::GetNowCount() - previously_tick_fired_clock;
			if (elapsed_time_since_previously_tick_fired > TICK_INTERVAL) {

				unique_ptr<Offensive> straight_shot = make_unique<StraightShot>(position->x, position->y, 1.0 / 4.0 * pi, 200, 20, 1, SkinID::NORMAL_BLUE);
				Field::ENEMY_OFFENSIVES->push_back(move(straight_shot));

				++tick_count;
				previously_tick_fired_clock = DxLib::GetNowCount();
			}
		}
		else {
			int elapsed_time_since_previously_shot_completed = DxLib::GetNowCount() - previously_shot_completed_clock;
			if (elapsed_time_since_previously_shot_completed > SHOT_INTERVAL) {
				++shot_count;
				tick_count = 0;
				previously_shot_completed_clock = DxLib::GetNowCount();
			}
		}
	}

}


void ZkChrStg1Wv1::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, 0, ImageHandles::KURAGE, TRUE);
	collidant->draw();
}