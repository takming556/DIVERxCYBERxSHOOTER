#include <memory>
#include <cmath>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;
using std::sin;
using std::cos;

const unsigned int ZkChrStg1Wv4::HP = 5;
const unsigned int ZkChrStg1Wv4::LINES_TICKS = 3;
const unsigned int ZkChrStg1Wv4::LINES_SHOTS = 3;
const unsigned int ZkChrStg1Wv4::LINES_TICK_INTERVAL = 125;
const unsigned int ZkChrStg1Wv4::LINES_SHOT_INTERVAL = 2000;
const unsigned int ZkChrStg1Wv4::COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv4::BARRAGE_EMIT_NOZZLES = 5;
const unsigned int ZkChrStg1Wv4::BARRAGE_EMITS = 1;
const unsigned int ZkChrStg1Wv4::BARRAGE_EMIT_INTERVAL = 2000;
const double ZkChrStg1Wv4::BARRAGE_INIT_ARG = 0.0;
const double ZkChrStg1Wv4::BARRAGE_SHOT_SPEED = 200;
const unsigned int ZkChrStg1Wv4::BARRAGE_SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv4::BARRAGE_SHOT_DURABILITY = 1;


ZkChrStg1Wv4::ZkChrStg1Wv4(double init_pos_x, double init_pos_y) :
	Character(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)),
	EnemyCharacter(HP),
	//speed(init_speed),
	//arg(init_arg),
	tick_count(0),
	shot_count(0),
	//last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_lines_tick_fired_clock(DxLib::GetNowCount()),
	last_lines_shot_completed_clock(DxLib::GetNowCount()),
	barrage(make_unique<SimpleStraightShotEmission>(
		init_pos_x,
		init_pos_y,
		BARRAGE_INIT_ARG,
		false,
		BARRAGE_EMITS,
		BARRAGE_EMIT_NOZZLES,
		BARRAGE_EMIT_INTERVAL,
		BARRAGE_SHOT_SPEED,
		BARRAGE_SHOT_COLLIDANT_SIZE,
		BARRAGE_SHOT_DURABILITY,
		TeamID::ENEMY,
		SkinID::NORMAL_BLUE
		)
	)
{
}


void ZkChrStg1Wv4::update() {
	//LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	//double distance = speed * update_delta_time / 1000 / 1000;
	//double distance_x = distance * cos(arg);
	//double distance_y = distance * sin(arg);
	//position->x += distance_x;
	//position->y += distance_y;
	//last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
	barrage->update(position->x, position->y);

	if (shot_count < LINES_SHOTS) {
		if (tick_count < LINES_TICKS) {
			int tick_fire_delta_time = DxLib::GetNowCount() - last_lines_tick_fired_clock;
			if (tick_fire_delta_time > LINES_TICK_INTERVAL) {

				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double delta_x_mychr = my_chr_pos.x - position->x;
				double delta_y_mychr = my_chr_pos.y - position->y;
				double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr,
					200,
					20,
					1,
					SkinID::NORMAL_BLUE
					)
				);
				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr + (1.0 / 12.0) * pi,
					200,
					20,
					1,
					SkinID::NORMAL_BLUE
					)
				);
				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr,
					200,
					20,
					1,
					SkinID::NORMAL_BLUE
					)
				);


				++tick_count;
				last_lines_tick_fired_clock = DxLib::GetNowCount();
			}
		}
		else {
			int shot_complete_delta_time = DxLib::GetNowCount() - last_lines_shot_completed_clock;
			if (shot_complete_delta_time > LINES_SHOT_INTERVAL) {
				++shot_count;
				tick_count = 0;
				last_lines_shot_completed_clock = DxLib::GetNowCount();
			}
		}
	}

}


void ZkChrStg1Wv4::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, 0, ImageHandles::KUJIRA, TRUE);
	collidant->draw();
}