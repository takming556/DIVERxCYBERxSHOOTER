#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv6R.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg2Wv6R::INIT_POS_X = Field::PIXEL_SIZE_X - 100;
const double ZkChrStg2Wv6R::INIT_POS_Y = Field::PIXEL_SIZE_Y + 100;
const double ZkChrStg2Wv6R::INIT_SPEED = 100;
const double ZkChrStg2Wv6R::INIT_ARG = 3.0 / 2.0 * pi;
const unsigned int ZkChrStg2Wv6R::INIT_HP = 5;
const unsigned int ZkChrStg2Wv6R::COLLIDANT_SIZE = 20;
const double ZkChrStg2Wv6R::SHOT_ARG = 4.0 / 3.0 * pi;
const double ZkChrStg2Wv6R::SHOT_SPEED = 400;
const unsigned int ZkChrStg2Wv6R::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg2Wv6R::TICK_INTERVAL = 500;

const double ZkChrStg2Wv6R::DRAW_EXTRATE = 0.05;

ZkChrStg2Wv6R::ZkChrStg2Wv6R(enum CharacterID given_id) :
	Character(
		given_id,
		INIT_POS_X,
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)
	),
	last_tick_generated_clock(DxLib::GetNowCount())
{
}

void ZkChrStg2Wv6R::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = INIT_SPEED * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(INIT_ARG);
	double distance_y = distance * sin(INIT_ARG);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;
	if (tick_generated_delta_time > TICK_INTERVAL) {

		(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
			position->x,
			position->y,
			SHOT_ARG,
			SHOT_SPEED,
			SHOT_COLLIDANT_SIZE,
			1,
			SkinID::STG2_WAVE6_R
		);
		DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

		last_tick_generated_clock = DxLib::GetNowCount();
	}
}

void ZkChrStg2Wv6R::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KNIGHT_RAY, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}
