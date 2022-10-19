#include <memory>
#include <cmath>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;
using std::sin;
using std::cos;


const unsigned int ZkChrStg1Wv3S::TICKS = 3;
//const unsigned int ZkChrStg1Wv3S::SHOTS = ;
const unsigned int ZkChrStg1Wv3S::TICK_INTERVAL = 125;
const unsigned int ZkChrStg1Wv3S::SHOT_INTERVAL = 2000;
const unsigned int ZkChrStg1Wv3S::INITIAL_HP = 15;
const unsigned int ZkChrStg1Wv3S::COLLIDANT_SIZE = 20;
const double ZkChrStg1Wv3S::DRAW_EXTRATE = 0.07;

const double ZkChrStg1Wv3S::SHOT_SPEED = 200;
const unsigned int ZkChrStg1Wv3S::SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv3S::SHOT_DURABILITY = 1;
//const double ZkChrStg1Wv3S::SHOT_DRAW_EXTRATE = ;


ZkChrStg1Wv3S::ZkChrStg1Wv3S(int init_pos_x, int init_pos_y) :
	Character(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)),
	EnemyCharacter(INITIAL_HP),
	//speed(init_speed),
	//arg(init_arg),
	tick_count(0),
	//shot_count(0),
	//last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_shot_completed_clock(DxLib::GetNowCount()),
	last_tick_fired_clock(DxLib::GetNowCount())
{
}


void ZkChrStg1Wv3S::update() {
	//LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	//double distance = speed * update_delta_time / 1000 / 1000;
	//double distance_x = distance * cos(arg);
	//double distance_y = distance * sin(arg);
	//position->x += distance_x;
	//position->y += distance_y;
	//last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	if (tick_count < TICKS) {
		int tick_fire_delta_time = DxLib::GetNowCount() - last_tick_fired_clock;
		if (tick_fire_delta_time > TICK_INTERVAL) {

			InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
			double delta_x_mychr = my_chr_pos.x - position->x;
			double delta_y_mychr = my_chr_pos.y - position->y;
			double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
			Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
				position->x,
				position->y,
				arg_toward_mychr,
				SHOT_SPEED,
				SHOT_COLLIDANT_SIZE,
				SHOT_DURABILITY,
				SkinID::NORMAL_BLUE
				)
			);

			++tick_count;
			last_tick_fired_clock = DxLib::GetNowCount();
		}
	}
	else {
		int shot_complete_delta_time = DxLib::GetNowCount() - last_shot_completed_clock;
		if (shot_complete_delta_time > SHOT_INTERVAL) {
			tick_count = 0;
			last_shot_completed_clock = DxLib::GetNowCount();
		}
	}

}


void ZkChrStg1Wv3S::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KUJIRA, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}