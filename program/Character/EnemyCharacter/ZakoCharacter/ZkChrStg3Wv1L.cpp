#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv1L.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double ZkChrStg3Wv1L::INIT_POS_X = 100;
const double ZkChrStg3Wv1L::INIT_POS_Y = 800;
const double ZkChrStg3Wv1L::INIT_SPEED = 150;
const double ZkChrStg3Wv1L::INIT_ARG = 3.0 / 2.0 * pi;
const unsigned int ZkChrStg3Wv1L::COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv1L::INIT_HP = 6;
const double ZkChrStg3Wv1L::SHOT_SPEED = 100;
const unsigned int ZkChrStg3Wv1L::SHOT_COLLIDANT_SIZE = 10;
const double ZkChrStg3Wv1L::DRAW_EXTRATE = 0.07;
const unsigned int ZkChrStg3Wv1L::TICK_INTERVAL = 900;


ZkChrStg3Wv1L::ZkChrStg3Wv1L(CharacterID given_id) :
	Character(
		given_id,
		INIT_POS_X,
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)),
	speed(INIT_SPEED),
	arg(INIT_ARG),
	last_tick_generated_clock(DxLib::GetNowCount()),
	mode(Stg3WAVE1Mode::DOWN),
	shotcount(1)
{
}


void ZkChrStg3Wv1L::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	switch (mode) {
	case Stg3WAVE1Mode::DOWN:
		if (position->y > 550) {
			arg = -1.0 / 2.0 * pi;

		}
		else {
			mode = Stg3WAVE1Mode::CURVE;
		}
		break;

	case Stg3WAVE1Mode::CURVE:
		if (arg<-1.0/4.0*pi){
			arg += 1.0 / 6.0 * pi * update_delta_time / 1000 / 1000;
		}
		else {
		mode = Stg3WAVE1Mode::CIRCLE;
		}
		break;

	case Stg3WAVE1Mode::CIRCLE:
		if (arg < 2.0 * pi) {
			arg += 1.0 / 4.0 * pi * update_delta_time / 1000 / 1000;
			int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;
			if (tick_generated_delta_time > TICK_INTERVAL) {
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
					SkinID::STG3_WAVE1_R
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
				last_tick_generated_clock = DxLib::GetNowCount();
			}
		}
		else {
			mode = Stg3WAVE1Mode::EXIT;
		}
		break;
	
	case Stg3WAVE1Mode::EXIT:
		arg == 0.0;
		break;
	}
	double distance = INIT_SPEED * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();
	collidant->update(position);

}


void ZkChrStg3Wv1L::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_GOZGOK, TRUE);
}