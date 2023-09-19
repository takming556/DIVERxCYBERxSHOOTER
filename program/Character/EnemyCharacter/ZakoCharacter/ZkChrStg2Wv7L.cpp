#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv7L.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg2Wv7L::INIT_POS_X = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2 - 100;
const double ZkChrStg2Wv7L::INIT_POS_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y + 50;
const double ZkChrStg2Wv7L::INIT_SPEED = 200;
const double ZkChrStg2Wv7L::INIT_ARG = 7.0 / 4.0 * pi;
const unsigned int ZkChrStg2Wv7L::COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg2Wv7L::INIT_HP = 15;
const unsigned int ZkChrStg2Wv7L::SHOT_SPEED = 300;
const unsigned int ZkChrStg2Wv7L::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg2Wv7L::SHOT_INTERVAL = 3000;
const unsigned int ZkChrStg2Wv7L::TURN_INTERVAL = 300;

const double ZkChrStg2Wv7L::DRAW_EXTRATE = 0.05;


ZkChrStg2Wv7L::ZkChrStg2Wv7L(enum CharacterID given_id) :
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
	last_generated_clock(DxLib::GetNowCount()),
	turn_clock(DxLib::GetNowCount()),
	turn_status(Stg2WAVE7TurnFlag::RIGHT),
	lap_count(0)
{
}

void ZkChrStg2Wv7L::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	int elapsed_time = DxLib::GetNowCount() - turn_clock;
	// •ûŒü“]Š·
	if (elapsed_time >= TURN_INTERVAL) {
		if (turn_status == Stg2WAVE7TurnFlag::RIGHT) {
			arg = 5.0 / 4.0 * pi;
			turn_status = Stg2WAVE7TurnFlag::LEFT;
		}
		else if (turn_status == Stg2WAVE7TurnFlag::LEFT) {
			arg = 7.0 / 4.0 * pi;
			turn_status = Stg2WAVE7TurnFlag::RIGHT;
		}
		else if (turn_status == Stg2WAVE7TurnFlag::UP) {
			arg = 7.0 / 4.0 * pi;
			turn_status = Stg2WAVE7TurnFlag::DOWN;
		}
		else if (turn_status == Stg2WAVE7TurnFlag::DOWN) {
			arg = 1.0 / 4.0 * pi;
			turn_status = Stg2WAVE7TurnFlag::UP;
		}

		turn_clock = DxLib::GetNowCount();
	}
	// ‰æ–ÊŠOƒ[ƒv
	if (position->y < InFieldPosition::MIN_MOVABLE_BOUNDARY_Y - 50) {
		position->x = InFieldPosition::MIN_MOVABLE_BOUNDARY_X - 50;
		position->y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y / 2 + 100;
		arg = 1.0 / 4.0 * pi;
		turn_status = Stg2WAVE7TurnFlag::UP;
	}
	else if (position->x > InFieldPosition::MAX_MOVABLE_BOUNDARY_X + 50) {
		position->x = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2 - 100;
		position->y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y + 50;
		arg = 7.0 / 4.0 * pi;
		turn_status = Stg2WAVE7TurnFlag::RIGHT;
		++lap_count;
	}

	// ‘Þêˆ—
	if (lap_count >= 3) {
		arg = 1.0 / 2.0 * pi;
		turn_status = Stg2WAVE7TurnFlag::EXIT;
	}

	// Ž©‹@‘_‚¢’e
	if (turn_status != Stg2WAVE7TurnFlag::EXIT) {
		int generated_delta_time = DxLib::GetNowCount() - last_generated_clock;
		if (generated_delta_time > SHOT_INTERVAL) {
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
				SkinID::STG2_WAVE7_L
			);
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			last_generated_clock = GetNowCount();
		}
	}
}

void ZkChrStg2Wv7L::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_LIGHT_ELE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}