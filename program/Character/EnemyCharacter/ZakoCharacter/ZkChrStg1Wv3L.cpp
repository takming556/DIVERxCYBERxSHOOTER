#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Barrage/Emission/StraightShotEmission/RotatingStraightShotEmission.h"
#include "CollideRealm/CollideCircle.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv3L.h"
#include "ImageHandles.h"
#include "DebugParams.h"

using std::unique_ptr;
using std::make_unique;
using std::numbers::pi;

const unsigned int ZkChrStg1Wv3L::INITIAL_HP = 25;
const unsigned int ZkChrStg1Wv3L::COLLIDANT_SIZE = 20;
const double ZkChrStg1Wv3L::DRAW_EXTRATE = 0.07;

const unsigned int ZkChrStg1Wv3L::BARRAGE_EMIT_NOZZLES = 5;
const unsigned int ZkChrStg1Wv3L::BARRAGE_EMIT_INTERVAL = 2000;
const double ZkChrStg1Wv3L::BARRAGE_INIT_ARG = -(1.0 / 2.0) * pi;
const double ZkChrStg1Wv3L::BARRAGE_SHOT_SPEED = 150.0;
const unsigned int ZkChrStg1Wv3L::BARRAGE_SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv3L::BARRAGE_SHOT_DURABILITY = 1;



ZkChrStg1Wv3L::ZkChrStg1Wv3L(
	enum CharacterID given_id,
	double init_pos_x,
	double init_pos_y,
	double barrage_rotate_speed
):
	Character(
		given_id,
		init_pos_x,
		init_pos_y,
		INITIAL_HP,
		make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)
	),
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
	collidant->update(position);
	barrage->update(position->x, position->y);
}


void ZkChrStg1Wv3L::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KURAGE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}