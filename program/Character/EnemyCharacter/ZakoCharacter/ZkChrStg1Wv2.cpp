﻿#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Barrage/Emission/StraightShotEmission/RotatingStraightShotEmission.h"
#include "Position/Position.h"
#include "Position/InFieldPosition.h"
#include "CollideRealm/CollideCircle.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv2.h"
#include "ImageHandles.h"
#include "DebugParams.h"

using std::unique_ptr;
using std::make_unique;
using std::numbers::pi;

const unsigned int ZkChrStg1Wv2::INITIAL_HP = 15;
const unsigned int ZkChrStg1Wv2::COLLIDANT_SIZE = 20;
const double ZkChrStg1Wv2::DRAW_EXTRATE = 0.07;

const unsigned int ZkChrStg1Wv2::BARRAGE_EMIT_NOZZLES = 10;
const unsigned int ZkChrStg1Wv2::BARRAGE_EMITS = 5;
const unsigned int ZkChrStg1Wv2::BARRAGE_EMIT_INTERVAL = 1000;
const double ZkChrStg1Wv2::BARRAGE_INIT_ARG = -(1.0 / 2.0) * pi;
const double ZkChrStg1Wv2::BARRAGE_SHOT_SPEED = 150.0;
const unsigned int ZkChrStg1Wv2::BARRAGE_SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv2::BARRAGE_SHOT_DURABILITY = 1;



ZkChrStg1Wv2::ZkChrStg1Wv2(
	enum CharacterID given_id,
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	double barrage_rotate_speed
):
	Character(
		given_id,
		init_pos_x,
		init_pos_y,
		INITIAL_HP,
		make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)
	),
	speed(init_speed),
	arg(init_arg),
	barrage(make_unique<RotatingStraightShotEmission>(
		init_pos_x,
		init_pos_y,
		BARRAGE_INIT_ARG,
		barrage_rotate_speed,
		false,
		BARRAGE_EMITS,
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


void ZkChrStg1Wv2::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
	barrage->update(position->x, position->y);
}


void ZkChrStg1Wv2::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KURAGE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}