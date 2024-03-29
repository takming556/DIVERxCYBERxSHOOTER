﻿#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv6LR.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg3Wv6LR::L_INIT_POS_X = -100;
const double ZkChrStg3Wv6LR::R_INIT_POS_X = 720;
const double ZkChrStg3Wv6LR::INIT_POS_Y = 600;
const double ZkChrStg3Wv6LR::L_INIT_ARG = 0.0 * pi;
const double ZkChrStg3Wv6LR::R_INIT_ARG = 1.0 * pi;
const double ZkChrStg3Wv6LR::INIT_SPEED = 50;
const unsigned int ZkChrStg3Wv6LR::INIT_HP = 30;
const unsigned int ZkChrStg3Wv6LR::COLLIDANT_SIZE = 20;
const double ZkChrStg3Wv6LR::SHOT_SPEED = 300;
const unsigned int ZkChrStg3Wv6LR::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv6LR::SHOTS = 100;
const unsigned int ZkChrStg3Wv6LR::TICKS = 3;
const unsigned int ZkChrStg3Wv6LR::SHOT_INTERVAL = 1000;
const unsigned int ZkChrStg3Wv6LR::TICK_INTERVAL = 100;

const double ZkChrStg3Wv6LR::DRAW_EXTRATE = 0.05;


int ZkChrStg3Wv6LR::INIT_POS_X(enum CharacterID given_id) {
	if (given_id == CharacterID::ZKCHRSTG3WV6_L) {
		return L_INIT_POS_X;
	}
	else if (given_id == CharacterID::ZKCHRSTG3WV6_R) {
		return R_INIT_POS_X;
	}
}

double ZkChrStg3Wv6LR::INIT_ARG(enum CharacterID given_id) {
	if (given_id == CharacterID::ZKCHRSTG3WV6_L) {
		return L_INIT_ARG;
	}
	else if (given_id == CharacterID::ZKCHRSTG3WV6_R) {
		return R_INIT_ARG;
	}
}

ZkChrStg3Wv6LR::ZkChrStg3Wv6LR(enum CharacterID given_id) :
	Character(
		given_id,
		INIT_POS_X(given_id),
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X(given_id), INIT_POS_Y, COLLIDANT_SIZE)
	),
	arg(INIT_ARG(given_id)),
	speed(INIT_SPEED),
	last_tick_generated_clock(DxLib::GetNowCount()),
	last_shot_completed_clock(DxLib::GetNowCount()),
	shot_count(0),
	tick_count(0)
{
}

void ZkChrStg3Wv6LR::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (id == CharacterID::ZKCHRSTG3WV6_L) {
		arg -= 1.0 / 16.0 * pi * update_delta_time / 1000 / 1000;
	}
	else if (id == CharacterID::ZKCHRSTG3WV6_R) {
		arg += 1.0 / 16.0 * pi * update_delta_time / 1000 / 1000;
	}
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	if (shot_count < SHOTS) {
		if (tick_count < TICKS) {
			int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;
			if (tick_generated_delta_time > TICK_INTERVAL) {

				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double delta_x_mychr = my_chr_pos.x - position->x;
				double delta_y_mychr = my_chr_pos.y - position->y;
				double arg_toword_mychr = atan2(delta_y_mychr, delta_x_mychr);

				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toword_mychr,
					SHOT_SPEED,
					SHOT_COLLIDANT_SIZE,
					1,
					SkinID::STG3_WAVE6_LR_GHOST
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				++tick_count;
				last_tick_generated_clock = DxLib::GetNowCount();
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

void ZkChrStg3Wv6LR::draw() {
	Position draw_pos = position->get_draw_position();
	if (id == CharacterID::ZKCHRSTG3WV6_L) {
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_MEZDOROGON, TRUE, TRUE);
	}
	else if (id == CharacterID::ZKCHRSTG3WV6_R) {
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_MEZDOROGON, TRUE, FALSE);
	}
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}