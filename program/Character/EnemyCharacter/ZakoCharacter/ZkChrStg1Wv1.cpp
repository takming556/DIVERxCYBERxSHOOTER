#include <memory>
#include <cmath>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv1.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::unique_ptr;
using std::make_unique;
using std::sin;
using std::cos;


const unsigned int ZkChrStg1Wv1::TICKS = 3;
const unsigned int ZkChrStg1Wv1::SHOTS = 4;
const unsigned int ZkChrStg1Wv1::TICK_INTERVAL = 125;
const unsigned int ZkChrStg1Wv1::SHOT_INTERVAL = 2000;
const unsigned int ZkChrStg1Wv1::INITIAL_HP = 5;
const unsigned int ZkChrStg1Wv1::COLLIDANT_SIZE = 20;
const double ZkChrStg1Wv1::DRAW_EXTRATE = 0.07;

const double ZkChrStg1Wv1::SHOT_SPEED = 200;
const unsigned int ZkChrStg1Wv1::SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv1::SHOT_DURABILITY = 1;



ZkChrStg1Wv1::ZkChrStg1Wv1(
	enum CharacterID given_id,
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed
) :
	Character(
		given_id,
		init_pos_x,
		init_pos_y,
		INITIAL_HP,
		make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)
	),
	speed(init_speed),
	arg(init_arg),
	tick_count(0),
	shot_count(0),
	last_shot_completed_clock(DxLib::GetNowCount()),
	last_tick_fired_clock(DxLib::GetNowCount())
{
}


void ZkChrStg1Wv1::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	if (shot_count < SHOTS) {
		if (tick_count < TICKS) {
			int tick_fire_delta_time = DxLib::GetNowCount() - last_tick_fired_clock;
			if (tick_fire_delta_time > TICK_INTERVAL) {

				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double delta_x_mychr = my_chr_pos.x - position->x;
				double delta_y_mychr = my_chr_pos.y - position->y;
				double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
				(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
					position->x, 
					position->y, 
					arg_toward_mychr, 
					SHOT_SPEED, 
					SHOT_COLLIDANT_SIZE, 
					SHOT_DURABILITY, 
					SkinID::BUBBLE_GENERIC
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				++tick_count;
				last_tick_fired_clock = DxLib::GetNowCount();
			}
		}
		else {
			int shot_complete_delta_time = DxLib::GetNowCount() - last_shot_completed_clock;
			if (shot_complete_delta_time > SHOT_INTERVAL) {
				++shot_count;
				tick_count = 0;
				last_shot_completed_clock = DxLib::GetNowCount();
			}
		}
	}

}


void ZkChrStg1Wv1::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KUJIRA, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}