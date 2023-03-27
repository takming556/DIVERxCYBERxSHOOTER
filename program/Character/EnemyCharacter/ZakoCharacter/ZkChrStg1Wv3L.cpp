#include <memory>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;

const unsigned int ZkChrStg1Wv3L::INITIAL_HP = 25;
const unsigned int ZkChrStg1Wv3L::COLLIDANT_SIZE = 20;
const double ZkChrStg1Wv3L::DRAW_EXTRATE = 0.07;

const unsigned int ZkChrStg1Wv3L::BARRAGE_EMIT_NOZZLES = 5;
//const unsigned int ZkChrStg1Wv3L::BARRAGE_EMITS = 3;
const unsigned int ZkChrStg1Wv3L::BARRAGE_EMIT_INTERVAL = 2000;
const double ZkChrStg1Wv3L::BARRAGE_INIT_ARG = -(1.0 / 2.0) * pi;
const double ZkChrStg1Wv3L::BARRAGE_SHOT_SPEED = 150.0;
const unsigned int ZkChrStg1Wv3L::BARRAGE_SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv3L::BARRAGE_SHOT_DURABILITY = 1;
//const double ZkChrStg1Wv3L::BARRAGE_SHOT_DRAW_EXTRATE = ;



ZkChrStg1Wv3L::ZkChrStg1Wv3L(double init_pos_x, double init_pos_y, double barrage_rotate_speed) :
	Character(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)),
	EnemyCharacter(INITIAL_HP),
	//speed(init_speed),
	//arg(init_arg),
	//last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	barrage(make_unique<RotatingStraightShotEmission>(
		init_pos_x,
		init_pos_y,
		BARRAGE_INIT_ARG,
		barrage_rotate_speed,
		true,
		114514,
		BARRAGE_EMIT_NOZZLES,
		BARRAGE_EMIT_INTERVAL,
		BARRAGE_SHOT_SPEED,
		BARRAGE_SHOT_COLLIDANT_SIZE,
		BARRAGE_SHOT_DURABILITY,
		TeamID::ENEMY,
		SkinID::BUBBLE_GENERIC
		)
	)
{
}


void ZkChrStg1Wv3L::update() {
	//LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	//double distance = speed * update_delta_time / 1000 / 1000;
	//double distance_x = distance * cos(arg);
	//double distance_y = distance * sin(arg);
	//position->x += distance_x;
	//position->y += distance_y;
	//last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
	barrage->update(position->x, position->y);
}


void ZkChrStg1Wv3L::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KURAGE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}