#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv5TR.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const unsigned int ZkChrStg3Wv5TR::INIT_POS_X = InFieldPosition::MAX_MOVABLE_BOUNDARY_X + 50;;
const unsigned int ZkChrStg3Wv5TR::INIT_POS_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y - 100;
const double ZkChrStg3Wv5TR::INIT_SPEED = 50;
const double ZkChrStg3Wv5TR::INIT_ARG = 1.0 * pi;
const unsigned int ZkChrStg3Wv5TR::COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv5TR::INIT_HP = 10;
const double ZkChrStg3Wv5TR::SHOT_SPEED = 80;
const double ZkChrStg3Wv5TR::SHOT_ARG = 3.0 / 2.0 * pi;
const unsigned int ZkChrStg3Wv5TR::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv5TR::TICK_INTERVAL = 4000;

const double ZkChrStg3Wv5TR::DRAW_EXTRATE = 0.05;

ZkChrStg3Wv5TR::ZkChrStg3Wv5TR(CharacterID given_id) : 
	Character(
		given_id,
		INIT_POS_X,
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)
	),
	arg(INIT_ARG),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	last_tick_generated_clock(DxLib::GetNowCount()),
	reflect_flag(false)
{
}

void ZkChrStg3Wv5TR::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = INIT_SPEED * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);

	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}

void ZkChrStg3Wv5TR::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_MEZDOROGON, TRUE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}

