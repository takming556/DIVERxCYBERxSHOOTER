#include <memory>
#include <cmath>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Position/Position.h"
#include "Position/InFieldPosition.h"
#include "CollideRealm/CollideRealm.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv3S.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::unique_ptr;
using std::make_unique;
using std::sin;
using std::cos;


const unsigned int ZkChrStg1Wv3S::TICKS = 3;
const unsigned int ZkChrStg1Wv3S::TICK_INTERVAL = 125;
const unsigned int ZkChrStg1Wv3S::SHOT_INTERVAL = 2000;
const unsigned int ZkChrStg1Wv3S::INITIAL_HP = 15;
const unsigned int ZkChrStg1Wv3S::COLLIDANT_SIZE = 20;
const double ZkChrStg1Wv3S::DRAW_EXTRATE = 0.07;

const double ZkChrStg1Wv3S::SHOT_SPEED = 200;
const unsigned int ZkChrStg1Wv3S::SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv3S::SHOT_DURABILITY = 1;


ZkChrStg1Wv3S::ZkChrStg1Wv3S(
	enum CharacterID given_id,
	double init_pos_x,
	double init_pos_y
):
	Character(
		given_id,
		init_pos_x,
		init_pos_y,
		make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)
	),
	EnemyCharacter(INITIAL_HP),
	tick_count(0),
	last_shot_completed_clock(DxLib::GetNowCount()),
	last_tick_fired_clock(DxLib::GetNowCount())
{
}


void ZkChrStg1Wv3S::update() {

	collidant->update(position);

	if (tick_count < TICKS) {
		int tick_fire_delta_time = DxLib::GetNowCount() - last_tick_fired_clock;
		if (tick_fire_delta_time > TICK_INTERVAL) {

			InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
			double delta_x_mychr = my_chr_pos.x - position->x;
			double delta_y_mychr = my_chr_pos.y - position->y;
			double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
			Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
				position->x,
				position->y,
				arg_toward_mychr,
				SHOT_SPEED,
				SHOT_COLLIDANT_SIZE,
				SHOT_DURABILITY,
				SkinID::BUBBLE_GENERIC
				)
			);

			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

			++tick_count;
			last_tick_fired_clock = DxLib::GetNowCount();
		}
	}
	else {
		int shot_complete_delta_time = DxLib::GetNowCount() - last_shot_completed_clock;
		if (shot_complete_delta_time > SHOT_INTERVAL) {
			tick_count = 0;
			last_shot_completed_clock = DxLib::GetNowCount();
		}
	}

}


void ZkChrStg1Wv3S::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KUJIRA, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}