#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv5L.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg2Wv5L::INIT_POS_X = 150;
const double ZkChrStg2Wv5L::INIT_POS_Y = Field::PIXEL_SIZE_Y + 100;
const double ZkChrStg2Wv5L::INIT_SPEED = 200;
const double ZkChrStg2Wv5L::INIT_ARG = 3.0 / 2.0 * pi;
const unsigned int ZkChrStg2Wv5L::INIT_HP = 60;
const unsigned int ZkChrStg2Wv5L::COLLIDANT_SIZE = 25;
const double ZkChrStg2Wv5L::SHOT_SPEED = 300;
const unsigned int ZkChrStg2Wv5L::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg2Wv5L::TICK_INTERVAL = 200;
const unsigned int ZkChrStg2Wv5L::ENTER_TIME = 1000;
const unsigned int ZkChrStg2Wv5L::STAY_TIME = 15000;

const double ZkChrStg2Wv5L::DRAW_EXTRATE = 0.07;

ZkChrStg2Wv5L::ZkChrStg2Wv5L() :
	Character(INIT_POS_X, INIT_POS_Y, make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)),
	EnemyCharacter(INIT_HP),
	arg(INIT_ARG),
	speed(INIT_SPEED),
	shot_arg(0.0 * pi),
	last_tick_generated_clock(DxLib::GetNowCount()),
	move_clock(DxLib::GetNowCount()),
	move_status(Stg2WAVE5MoveFlag::ENTER)
{
}

void ZkChrStg2Wv5L::update() {
	int elapsed_time = DxLib::GetNowCount() - move_clock;

	if (move_status == Stg2WAVE5MoveFlag::ENTER) {
		if (elapsed_time > ENTER_TIME) {
			speed = 0;
			move_status = Stg2WAVE5MoveFlag::STAY;
		}
	}
	else if (move_status == Stg2WAVE5MoveFlag::STAY) {
		if (elapsed_time > ENTER_TIME + STAY_TIME) {
			arg = 1.0 / 2.0 * pi;
			speed = 100;
			move_status = Stg2WAVE5MoveFlag::EXIT;
		}
		int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;
		if (tick_generated_delta_time > TICK_INTERVAL) {

			for (int i = 0; i < 4; ++i) {
				Field::ENEMY_BULLETS->push_back(make_unique<StraightShot>(
					position->x,
					position->y,
					shot_arg,
					SHOT_SPEED,
					SHOT_COLLIDANT_SIZE,
					1,
					SkinID::STG2_WAVE5_L
					));
				shot_arg += 1.0 / 2.0 * pi;
			}
			shot_arg += -1.0 / 16.0 * pi;
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

			last_tick_generated_clock = DxLib::GetNowCount();
		}
	}
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}


void ZkChrStg2Wv5L::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KNIGHT_RAY, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}
