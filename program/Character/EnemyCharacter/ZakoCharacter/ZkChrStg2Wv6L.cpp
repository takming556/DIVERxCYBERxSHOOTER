#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv6L.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg2Wv6L::INIT_POS_X = 100;
const double ZkChrStg2Wv6L::INIT_POS_Y = Field::PIXEL_SIZE_Y + 100;
const double ZkChrStg2Wv6L::INIT_ARG = 3.0 / 2.0 * pi;
const double ZkChrStg2Wv6L::INIT_SPEED = 100;
const unsigned int ZkChrStg2Wv6L::INIT_HP = 5;
const unsigned int ZkChrStg2Wv6L::COLLIDANT_SIZE = 20;
const double ZkChrStg2Wv6L::SHOT_SPEED = 400;
const unsigned int ZkChrStg2Wv6L::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg2Wv6L::TICK_INTERVAL = 1000;

const double ZkChrStg2Wv6L::DRAW_EXTRATE = 0.05;

ZkChrStg2Wv6L::ZkChrStg2Wv6L(enum CharacterID given_id) :
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

void ZkChrStg2Wv6L::update() {
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
			SkinID::STG2_WAVE6_L
		);
		DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

		last_tick_generated_clock = DxLib::GetNowCount();
	}

}

void ZkChrStg2Wv6L::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_LIGHT_ELE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}