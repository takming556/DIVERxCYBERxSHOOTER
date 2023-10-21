#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv4LR.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/Bullet.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;

const unsigned int ZkChrStg3Wv4LR::INIT_POS_X_L = Field::PIXEL_SIZE_X / 2 - 150;
const unsigned int ZkChrStg3Wv4LR::INIT_POS_X_R = Field::PIXEL_SIZE_X / 2 + 150;
const int ZkChrStg3Wv4LR::INIT_POS_Y = InFieldPosition::MIN_MOVABLE_BOUNDARY_Y - 100;
const double ZkChrStg3Wv4LR::INIT_ARG = 1.0 / 2.0 * pi;
const double ZkChrStg3Wv4LR::INIT_SPEED = 150;
const unsigned int ZkChrStg3Wv4LR::INIT_HP = 8;
const unsigned int ZkChrStg3Wv4LR::COLLIDANT_SIZE = 10;
const double ZkChrStg3Wv4LR::SHOT_SPEED = 200;
const unsigned int ZkChrStg3Wv4LR::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv4LR::TICK_INTERVAL = 1500;

const double ZkChrStg3Wv4LR::DRAW_EXTRATE = 0.05;

int ZkChrStg3Wv4LR::INIT_POS_X(Stg3WAVE4LR given_lr) {
	if (given_lr == Stg3WAVE4LR::LEFT) {
		return INIT_POS_X_L;
	}
	else if (given_lr == Stg3WAVE4LR::RIGHT) {
		return INIT_POS_X_R;
	}
}

ZkChrStg3Wv4LR::ZkChrStg3Wv4LR(CharacterID given_id, Stg3WAVE4LR lr) :
	Character(
		given_id,
		INIT_POS_X(lr),
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X(lr), INIT_POS_Y, COLLIDANT_SIZE)
	),
	arg(INIT_ARG),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_tick_generated_clock(DxLib::GetNowCount()),
	mode(Stg3WAVE4LRMode::ENTER),
	lr_flag(lr)
{
}

void ZkChrStg3Wv4LR::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;

	switch (mode)
	{
	case Stg3WAVE4LRMode::ENTER:
		if (position->y > Field::PIXEL_SIZE_Y / 2.0 + 50) {
			mode = Stg3WAVE4LRMode::ROLL;
		}
		break;
	case Stg3WAVE4LRMode::ROLL:
		if (lr_flag == Stg3WAVE4LR::LEFT) {
			arg += -1.0 / 3.0 * pi * update_delta_time / 1000 / 1000;
			if (arg < 1.0 / 2.0 * pi + -2.0 * pi * 1 + -1.0 * pi) {
				mode = Stg3WAVE4LRMode::EXIT;
			}
		}
		else if (lr_flag == Stg3WAVE4LR::RIGHT) {
			arg += 1.0 / 3.0 * pi * update_delta_time / 1000 / 1000;
			if (arg > 1.0 / 2.0 * pi + 2.0 * pi * 1 + 1.0 * pi) {
				mode = Stg3WAVE4LRMode::EXIT;
			}
		}
		break;
	case Stg3WAVE4LRMode::EXIT:
		arg = 3.0 / 2.0 * pi;
		break;
	}

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
			SkinID::STG3_WAVE4_LR
		);
		DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

		last_tick_generated_clock = DxLib::GetNowCount();
	}

	double distance = INIT_SPEED * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);

	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}

void ZkChrStg3Wv4LR::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_MEZDOROGON, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}