#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv5BL.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;

const double ZkChrStg3Wv5BL::INIT_POS_X = InFieldPosition::MIN_MOVABLE_BOUNDARY_X - 100;
const double ZkChrStg3Wv5BL::INIT_POS_Y = InFieldPosition::MIN_MOVABLE_BOUNDARY_Y + 50;
const double ZkChrStg3Wv5BL::INIT_SPEED = 100;
const double ZkChrStg3Wv5BL::INIT_ARG = 0.0 * pi;
const unsigned int ZkChrStg3Wv5BL::COLLIDANT_SIZE = 15;
const unsigned int ZkChrStg3Wv5BL::INIT_HP = 10;
const double ZkChrStg3Wv5BL::SHOT_SPEED = 250;
const unsigned int ZkChrStg3Wv5BL::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv5BL::TICK_INTERVAL = 1000;

const double ZkChrStg3Wv5BL::DRAW_EXTRATE = 0.05;

ZkChrStg3Wv5BL::ZkChrStg3Wv5BL(CharacterID given_id, Stg3WAVE5BLR lr) :
	Character(
		given_id,
		INIT_POS_X,
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)
	),
	speed(INIT_SPEED),
	arg(INIT_ARG),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_tick_generated_clock(DxLib::GetNowCount()),
	mode(Stg3WAVE5BMode::ENTER),
	l(lr)
{
}

void ZkChrStg3Wv5BL::update() {
	int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	switch (mode)
	{
	case Stg3WAVE5BMode::ENTER:
		arg += 1.0 / 12.0 * pi * update_delta_time / 1000 / 1000;	// Žã‚ß‰~‹O“¹‚ÉÝ’è
		if (arg >= 1.0 / 3.0 * pi) {
			mode = Stg3WAVE5BMode::ROLL;
		}
		break;
	case Stg3WAVE5BMode::ROLL:
		arg += 4.0 / 5.0 * pi * update_delta_time / 1000 / 1000;		// ‹­‚ß‰~‹O“¹‚ÉÝ’è
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

		if (arg >= 1.0 * pi + 2.0 * 4.0 * pi) {
			mode = Stg3WAVE5BMode::EXIT;
		}
		break;
	case Stg3WAVE5BMode::EXIT:
		arg = 1.0 * pi;
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

void ZkChrStg3Wv5BL::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_GOZGOK, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}