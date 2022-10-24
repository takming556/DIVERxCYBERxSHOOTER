#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


const unsigned int ZkChrStg1BsSp3::INITIAL_HP = 30;
const unsigned int ZkChrStg1BsSp3::COLLIDANT_SIZE = 30;
const double ZkChrStg1BsSp3::DRAW_EXTRATE = 0.15;
const unsigned int ZkChrStg1BsSp3::NOZZLES = 20;
const unsigned int ZkChrStg1BsSp3::INTERVAL = 8000;


ZkChrStg1BsSp3::ZkChrStg1BsSp3(double init_pos_x, double init_pos_y) :
	Character(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)),
	EnemyCharacter(INITIAL_HP),
	last_barraged_clock(0)
{
}


void ZkChrStg1BsSp3::update() {
	int elapsed_time_since_last_barraged = DxLib::GetNowCount() - last_barraged_clock;
	if (elapsed_time_since_last_barraged > INTERVAL) {
		InFieldPosition pos = *position;
		for (int i = 0; i < NOZZLES; i++) {
			Field::ENEMY_OFFENSIVES->push_back(make_unique<KurageAmeShot>(pos.x, pos.y));
		}
		last_barraged_clock = DxLib::GetNowCount();
	}
}


void ZkChrStg1BsSp3::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KURAGE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}