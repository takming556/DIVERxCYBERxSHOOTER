#include <memory>
#include <cmath>
#include "DxLib.h"
#include "class.h"

using std::make_unique;
using std::sin;
using std::cos;


ZkChrStg1Wv1::ZkChrStg1Wv1(int init_pos_x, int init_pos_y, double init_arg, double init_speed) :
	Character(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)),
	EnemyCharacter(INITIAL_HP),
	arg(init_arg),
	speed(init_speed),
	kept_clock_generate(DxLib::GetNowCount()),
	already_barrage_performed_flag(false)
{
}


void ZkChrStg1Wv1::update() {
	LONGLONG delta_time = DxLib::GetNowHiPerformanceCount() - kept_clock_for_update;
	double distance = speed * delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	kept_clock_for_update = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	int elapsed_time_since_generated = DxLib::GetNowCount() - kept_clock_for_update;
	if (already_barrage_performed_flag == false && elapsed_time_since_generated > 3000) {

	}

}


void ZkChrStg1Wv1::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.4, 0, ImageHandles::KURAGE, TRUE);
	collidant->draw();
}