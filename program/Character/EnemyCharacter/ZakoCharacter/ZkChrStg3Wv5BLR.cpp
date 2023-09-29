#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv5BLR.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;

const double ZkChrStg3Wv5BLR::INIT_POS_X_L = InFieldPosition::MIN_MOVABLE_BOUNDARY_X - 100;
const double ZkChrStg3Wv5BLR::INIT_POS_X_R = InFieldPosition::MAX_MOVABLE_BOUNDARY_X + 100;
const double ZkChrStg3Wv5BLR::INIT_POS_Y = InFieldPosition::MIN_MOVABLE_BOUNDARY_Y + 200;
const double ZkChrStg3Wv5BLR::INIT_SPEED = 100;
const double ZkChrStg3Wv5BLR::INIT_ARG_L = 0.0 * pi;
const double ZkChrStg3Wv5BLR::INIT_ARG_R = 1.0 * pi;
const unsigned int ZkChrStg3Wv5BLR::COLLIDANT_SIZE = 15;
const unsigned int ZkChrStg3Wv5BLR::INIT_HP = 8;
const double ZkChrStg3Wv5BLR::SHOT_SPEED = 250;
const unsigned int ZkChrStg3Wv5BLR::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv5BLR::TICK_INTERVAL = 3000;

const double ZkChrStg3Wv5BLR::DRAW_EXTRATE = 0.05;

int ZkChrStg3Wv5BLR::INIT_POS_X(Stg3WAVE5BLR given_lr) {
	if (given_lr == Stg3WAVE5BLR::LEFT) {
		return INIT_POS_X_L;
	}
	else if (given_lr == Stg3WAVE5BLR::RIGHT) {
		return INIT_POS_X_R;
	}
}

int ZkChrStg3Wv5BLR::INIT_ARG(Stg3WAVE5BLR given_lr) {
	if (given_lr == Stg3WAVE5BLR::LEFT) {
		return INIT_ARG_L;
	}
	else if (given_lr == Stg3WAVE5BLR::RIGHT) {
		return INIT_ARG_R;
	}
}


ZkChrStg3Wv5BLR::ZkChrStg3Wv5BLR(CharacterID given_id, Stg3WAVE5BLR lr) :
	Character(
		given_id,
		INIT_POS_X(lr),
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X(lr), INIT_POS_Y, COLLIDANT_SIZE)
	),
	speed(INIT_SPEED),
	arg(INIT_ARG(lr)),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_tick_generated_clock(DxLib::GetNowCount()),
	mode(Stg3WAVE5BMode::ENTER),
	lr_flag(lr)
{
}

void ZkChrStg3Wv5BLR::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;
	switch (mode)
	{
	case Stg3WAVE5BMode::ENTER:
		if (lr_flag == Stg3WAVE5BLR::LEFT) {
			arg += 1.0 / 12.0 * pi * update_delta_time / 1000 / 1000;	// Žã‚ß‰~‹O“¹‚ÉÝ’è
		}
		else if (lr_flag == Stg3WAVE5BLR::RIGHT) {
			arg -= 1.0 / 12.0 * pi * update_delta_time / 1000 / 1000;
		}

		if (position->y >= 350) {		// arg >= 1.0 / 3.0 * pi && arg <= 2.0 / 3.0 * pi
			mode = Stg3WAVE5BMode::ROLL;
		}

		break;

	case Stg3WAVE5BMode::ROLL:
		if (lr_flag == Stg3WAVE5BLR::LEFT) {
			arg += 4.0 / 5.0 * pi * update_delta_time / 1000 / 1000;		// ‹­‚ß‰~‹O“¹‚ÉÝ’è
		}
		else if (lr_flag == Stg3WAVE5BLR::RIGHT) {
			arg -= 4.0 / 5.0 * pi * update_delta_time / 1000 / 1000;		// ‹­‚ß‰~‹O“¹‚ÉÝ’è
		}

		speed = 200;

		// int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;
		if (tick_generated_delta_time > TICK_INTERVAL) {
			InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
			double delta_x_mychr = my_chr_pos.x - position->x;
			double delta_y_mychr = my_chr_pos.y - position->y;
			double arg_toword_mychr = atan2(delta_y_mychr, delta_x_mychr);

			(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
				position->x,
				position->y,
				arg_toword_mychr,
				SHOT_SPEED,
				SHOT_COLLIDANT_SIZE,
				1,
				SkinID::STG3_WAVE5_B
				);
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

			last_tick_generated_clock = DxLib::GetNowCount();
		}

		if (arg >= 1.0 * pi + 2.0 * 8.0 * pi || arg <= 0.0 * pi + (-2.0 * 8.0 * pi)) {
			mode = Stg3WAVE5BMode::EXIT;
		}
		break;

	case Stg3WAVE5BMode::EXIT:
		if (lr_flag == Stg3WAVE5BLR::LEFT) {
			arg = 1.0 * pi;
		}
		else if (lr_flag == Stg3WAVE5BLR::RIGHT) {
			arg = 0.0 * pi;
		}

		speed = 100;
		break;
	}

	//LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);

	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}

void ZkChrStg3Wv5BLR::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_GOZGOK, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}