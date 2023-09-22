#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv2R.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg3Wv2R::INIT_POS_X = 700;
const double ZkChrStg3Wv2R::INIT_POS_Y = 660;
const double ZkChrStg3Wv2R::INIT_SPEED = 130;
const double ZkChrStg3Wv2R::INIT_ARG =  pi;
const unsigned int ZkChrStg3Wv2R::COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv2R::INIT_HP = 4;
const double ZkChrStg3Wv2R::SHOT_SPEED = 150;
const unsigned int ZkChrStg3Wv2R::SHOT_COLLIDANT_SIZE = 10;
const double ZkChrStg3Wv2R::DRAW_EXTRATE = 0.07;
const unsigned int ZkChrStg3Wv2R::TICK_INTERVAL = 800;
const unsigned int ZkChrStg3Wv2R::BALL_NOZZLES = 20;

ZkChrStg3Wv2R::ZkChrStg3Wv2R(CharacterID given_id) :
	Character(
		given_id,
		INIT_POS_X,
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)),
	speed(INIT_SPEED),
	arg(INIT_ARG),
	last_tick_generated_clock(DxLib::GetNowCount()),
	mode(Stg3WAVE2Mode::Straight)
{
}


void ZkChrStg3Wv2R::update() {
	LONGLONG update_delta_time= DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	switch (mode) {
	case Stg3WAVE2Mode::Straight:
		if (position->x > 200) {
			arg =  pi;
		}
		else {
			mode = Stg3WAVE2Mode::CURVE;
		}
		break;
	case Stg3WAVE2Mode::CURVE:
		if (arg < 2.0*pi) {
			arg += 1.0 / 3.0 * pi * update_delta_time / 1000 / 1000;
		}
		else {
			mode = Stg3WAVE2Mode::EXIT;
		}
		break;
	case Stg3WAVE2Mode::EXIT:
		arg = 2.0*pi;
		break;
	}
	double distance = INIT_SPEED * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();
	collidant->update(position);
	if (hp== 0) {
		for (int i = 0; i < BALL_NOZZLES; ++i) {
			double theta = 2 * pi / BALL_NOZZLES * i;
			(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
				position->x,
				position->y,
				theta,
				SHOT_SPEED,
				SHOT_COLLIDANT_SIZE,
				1,
				SkinID::STG3_WAVE2_R
			);
		}
	}
}


void ZkChrStg3Wv2R::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_GOZGOK, TRUE);
}