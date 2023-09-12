#include <memory>
#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Barrage/Emission/StraightShotEmission/SimpleStraightShotEmission.h"
#include "CollideRealm/CollideCircle.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv4.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::unique_ptr;
using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;

const unsigned int ZkChrStg1Wv4::INITIAL_HP = 12;
const unsigned int ZkChrStg1Wv4::COLLIDANT_SIZE = 20;
const double ZkChrStg1Wv4::DRAW_EXTRATE = 0.085;

const unsigned int ZkChrStg1Wv4::LINES_TICKS = 3;
const unsigned int ZkChrStg1Wv4::LINES_SHOTS = 5;
const unsigned int ZkChrStg1Wv4::LINES_TICK_INTERVAL = 125;
const unsigned int ZkChrStg1Wv4::LINES_SHOT_INTERVAL = 1500;
const double ZkChrStg1Wv4::LINES_SHOT_SPEED = 200.0;
const unsigned int ZkChrStg1Wv4::LINES_SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv4::LINES_SHOT_DURABILITY = 1;

const unsigned int ZkChrStg1Wv4::BARRAGE_EMIT_NOZZLES = 5;
const unsigned int ZkChrStg1Wv4::BARRAGE_EMITS = 5;
const unsigned int ZkChrStg1Wv4::BARRAGE_EMIT_INTERVAL = 2000;
const double ZkChrStg1Wv4::BARRAGE_INIT_ARG = 0.0;
const double ZkChrStg1Wv4::BARRAGE_SHOT_SPEED = 150.0;
const unsigned int ZkChrStg1Wv4::BARRAGE_SHOT_COLLIDANT_SIZE = 20;
const unsigned int ZkChrStg1Wv4::BARRAGE_SHOT_DURABILITY = 1;



ZkChrStg1Wv4::ZkChrStg1Wv4(
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
	shot_count(0),
	last_lines_tick_fired_clock(DxLib::GetNowCount()),
	last_lines_shot_completed_clock(DxLib::GetNowCount()),
	barrage(make_unique<SimpleStraightShotEmission>(
		init_pos_x,
		init_pos_y,
		BARRAGE_INIT_ARG,
		false,
		BARRAGE_EMITS,
		BARRAGE_EMIT_NOZZLES,
		BARRAGE_EMIT_INTERVAL,
		BARRAGE_SHOT_SPEED,
		BARRAGE_SHOT_COLLIDANT_SIZE,
		BARRAGE_SHOT_DURABILITY,
		TeamID::ENEMY,
		SkinID::BUBBLE_GENERIC
		)
	)
{
}


void ZkChrStg1Wv4::update() {

	collidant->update(position);
	barrage->update(position->x, position->y);

	if (shot_count < LINES_SHOTS) {
		if (tick_count < LINES_TICKS) {
			int tick_fire_delta_time = DxLib::GetNowCount() - last_lines_tick_fired_clock;
			if (tick_fire_delta_time > LINES_TICK_INTERVAL) {

				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double delta_x_mychr = my_chr_pos.x - position->x;
				double delta_y_mychr = my_chr_pos.y - position->y;
				double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);

				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr + (1.0 / 12.0) * pi,
					LINES_SHOT_SPEED,
					LINES_SHOT_COLLIDANT_SIZE,
					LINES_SHOT_DURABILITY,
					SkinID::BUBBLE_GENERIC
					)
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr,
					LINES_SHOT_SPEED,
					LINES_SHOT_COLLIDANT_SIZE,
					LINES_SHOT_DURABILITY,
					SkinID::BUBBLE_GENERIC
					)
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr - (1.0 / 12.0) * pi,
					LINES_SHOT_SPEED,
					LINES_SHOT_COLLIDANT_SIZE,
					LINES_SHOT_DURABILITY,
					SkinID::BUBBLE_GENERIC
					)
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);


				++tick_count;
				last_lines_tick_fired_clock = DxLib::GetNowCount();
			}
		}
		else {
			int shot_complete_delta_time = DxLib::GetNowCount() - last_lines_shot_completed_clock;
			if (shot_complete_delta_time > LINES_SHOT_INTERVAL) {
				++shot_count;
				tick_count = 0;
				last_lines_shot_completed_clock = DxLib::GetNowCount();
			}
		}
	}

}


void ZkChrStg1Wv4::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KUJIRA, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}