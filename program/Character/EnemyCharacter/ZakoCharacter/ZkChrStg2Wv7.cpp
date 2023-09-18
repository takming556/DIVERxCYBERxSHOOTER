#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv7.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg2Wv7::INIT_POS_X = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2 - 100;
const double ZkChrStg2Wv7::INIT_POS_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y + 50;
const double ZkChrStg2Wv7::INIT_SPEED = 100;
const double ZkChrStg2Wv7::INIT_ARG = 7.0 / 4.0 * pi;
const unsigned int ZkChrStg2Wv7::COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg2Wv7::INIT_HP = 5;
const unsigned int ZkChrStg2Wv7::GENERATED_INTERVAL = 1000;
const unsigned int ZkChrStg2Wv7::SHOT_SPEED = 100;
const unsigned int ZkChrStg2Wv7::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg2Wv7::TURN_INTERVAL = 300;

const double ZkChrStg2Wv7::DRAW_EXTRATE = 0.05;


ZkChrStg2Wv7::ZkChrStg2Wv7(enum CharacterID given_id) :
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
	turn_status(Stg2WAVE7TurnFlag::RIGHT)
{
}

void ZkChrStg2Wv7::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	int elapsed_time = DxLib::GetNowCount() - turn_clock;
	if (elapsed_time >= TURN_INTERVAL) {
		if (turn_status == Stg2WAVE7TurnFlag::RIGHT) {
			arg = 5.0 / 4.0 * pi;
			turn_status = Stg2WAVE7TurnFlag::LEFT;
		}
		else if (turn_status == Stg2WAVE7TurnFlag::LEFT) {
			arg = 7.0 / 4.0 * pi;
			turn_status = Stg2WAVE7TurnFlag::RIGHT;
		}

		turn_clock = DxLib::GetNowCount();
	}

}

void ZkChrStg2Wv7::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_LIGHT_ELE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}