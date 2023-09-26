#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv5TLR.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const unsigned int ZkChrStg3Wv5TLR::INIT_POS_X_L = InFieldPosition::MIN_MOVABLE_BOUNDARY_X - 50;
const unsigned int ZkChrStg3Wv5TLR::INIT_POS_X_R = InFieldPosition::MAX_MOVABLE_BOUNDARY_X + 50;
const unsigned int ZkChrStg3Wv5TLR::INIT_POS_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y - 100;
const double ZkChrStg3Wv5TLR::INIT_SPEED = 50;
const double ZkChrStg3Wv5TLR::INIT_ARG_L = 0.0 * pi;
const double ZkChrStg3Wv5TLR::INIT_ARG_R = 1.0 * pi;
const unsigned int ZkChrStg3Wv5TLR::COLLIDANT_SIZE = 15;
const unsigned int ZkChrStg3Wv5TLR::INIT_HP = 10;
const double ZkChrStg3Wv5TLR::SHOT_SPEED = 80;
const double ZkChrStg3Wv5TLR::SHOT_ARG = 3.0 / 2.0 * pi ;
const unsigned int ZkChrStg3Wv5TLR::SHOT_COLLIDANT_SIZE = 5;
const unsigned int ZkChrStg3Wv5TLR::TICK_INTERVAL = 500;

const double ZkChrStg3Wv5TLR::DRAW_EXTRATE = 0.05;

int ZkChrStg3Wv5TLR::INIT_POS_X(Stg3WAVE5TLR given_lr) {
	if (given_lr == Stg3WAVE5TLR::LEFT) {
		return INIT_POS_X_L;
	}
	else if (given_lr == Stg3WAVE5TLR::RIGHT) {
		return INIT_POS_X_R;
	}
}

int ZkChrStg3Wv5TLR::INIT_ARG(Stg3WAVE5TLR given_lr) {
	if (given_lr == Stg3WAVE5TLR::LEFT) {
		return INIT_ARG_L;
	}
	else if (given_lr == Stg3WAVE5TLR::RIGHT) {
		return INIT_ARG_R;
	}
}

ZkChrStg3Wv5TLR::ZkChrStg3Wv5TLR(CharacterID given_id, Stg3WAVE5TLR lr) :
	Character(
		given_id,
		INIT_POS_X(lr),
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X(lr), INIT_POS_Y, COLLIDANT_SIZE)
	),
	arg(INIT_ARG(lr)),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_tick_generated_clock(DxLib::GetNowCount()),
	lr_flag(lr),
	init_move_flag(true)
{
}

void ZkChrStg3Wv5TLR::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (position->x >= InFieldPosition::MIN_MOVABLE_BOUNDARY_X && position->x <= InFieldPosition::MAX_MOVABLE_BOUNDARY_X) {
		init_move_flag = false;
	}
	if ((position->x <= InFieldPosition::MIN_MOVABLE_BOUNDARY_X || position->x >= InFieldPosition::MAX_MOVABLE_BOUNDARY_X)
		 && init_move_flag == false) {
		arg += 1.0 * pi;
	}
	double distance = INIT_SPEED * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);

	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;
	if (tick_generated_delta_time > TICK_INTERVAL) {
		InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
		double delta_x_mychr = my_chr_pos.x - position->x;
		double delta_y_mychr = my_chr_pos.y - position->y;

		(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
			position->x,
			position->y,
			SHOT_ARG,
			SHOT_SPEED,
			SHOT_COLLIDANT_SIZE,
			1,
			SkinID::STG3_WAVE5_T
		);
		DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

		last_tick_generated_clock = DxLib::GetNowCount();
	}
}

void ZkChrStg3Wv5TLR::draw() {
	Position draw_pos = position->get_draw_position();
	if (lr_flag == Stg3WAVE5TLR::LEFT) {
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_MEZDOROGON, TRUE, TRUE, FALSE);
	}
	else if (lr_flag == Stg3WAVE5TLR::RIGHT) {
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_MEZDOROGON, TRUE, FALSE, FALSE);
	}
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}