#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv4C.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/Bullet.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;

const unsigned int ZkChrStg3Wv4C::INIT_POS_X = Field::PIXEL_SIZE_X / 2;
const unsigned int ZkChrStg3Wv4C::INIT_POS_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y + 100;
const double ZkChrStg3Wv4C::INIT_ARG = 3.0 / 2.0 * pi;
const double ZkChrStg3Wv4C::INIT_SPEED = 100;
const unsigned int ZkChrStg3Wv4C::INIT_HP = 30;
const unsigned int ZkChrStg3Wv4C::COLLIDANT_SIZE = 20;
const double ZkChrStg3Wv4C::SHOT_INIT_ARG = 0.0 * pi;	// �֐���
const double ZkChrStg3Wv4C::SHOT_INIT_SPEED = 100;
const unsigned int ZkChrStg3Wv4C::SHOT_COLLIDANT_SIZE = 10;

const double ZkChrStg3Wv4C::DRAW_EXTRATE = 0.07;

ZkChrStg3Wv4C::ZkChrStg3Wv4C(CharacterID given_id) :
	Character(
		given_id,
		INIT_POS_X,
		INIT_POS_Y,
		INIT_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)
	),
	arg(INIT_ARG),
	speed(INIT_SPEED),
	shot_arg(SHOT_INIT_ARG),
	shot_speed(SHOT_INIT_SPEED),
	shot_id_count(0),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	kept_clock(DxLib::GetNowCount()),
	mode(Stg3WAVE4CMode::ENTER)
{
	for (int i = 0; i < 6; ++i) {
		shot_id[i] = 0;
	}
}

void ZkChrStg3Wv4C::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	int tick_generated_delta_time = DxLib::GetNowCount() - last_tick_generated_clock;

	switch (mode)
	{
	case Stg3WAVE4CMode::ENTER:
		if (elapsed_time > 3000) {
			speed = 0;
			mode = Stg3WAVE4CMode::SHOT;
			kept_clock = DxLib::GetNowCount();
		}
		break;
	case Stg3WAVE4CMode::SHOT:
		if (tick_generated_delta_time > 1000 && shot_id_count < 6) {
			shot_arg = 0.0 * pi;
			shot_id[shot_id_count] = Bullet::GENERATE_ID();
			(*Field::ENEMY_BULLETS)[shot_id[shot_id_count]] = make_unique<StraightShot>(
				position->x,
				position->y,
				shot_arg,
				shot_speed,
				SHOT_COLLIDANT_SIZE,
				1,
				SkinID::STG3_WAVE4_C
			);
			++shot_id_count;
			
			shot_arg = 1.0 * pi;
			shot_id[shot_id_count] = Bullet::GENERATE_ID();
			(*Field::ENEMY_BULLETS)[shot_id[shot_id_count]] = make_unique<StraightShot>(
				position->x,
				position->y,
				shot_arg,
				shot_speed,
				SHOT_COLLIDANT_SIZE,
				1,
				SkinID::STG3_WAVE4_C
			);
			++shot_id_count;

			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

			last_tick_generated_clock = DxLib::GetNowCount();
		}
		if (elapsed_time > 5000 && shot_id_count >= 6) {
			shot_speed = 0;
			// ���O���������@
			mode = Stg3WAVE4CMode::NOTIFY;
			kept_clock = DxLib::GetNowCount();
		}
		break;
	case Stg3WAVE4CMode::NOTIFY:
		if (elapsed_time > 2000) {
			mode = Stg3WAVE4CMode::NOTIFY;
			kept_clock = DxLib::GetNowCount();
		}
		break;
	case Stg3WAVE4CMode::LASER:
		if (elapsed_time > 3000) {
			mode = Stg3WAVE4CMode::LASER;
			kept_clock = DxLib::GetNowCount();
		}
		break;
	case Stg3WAVE4CMode::EXIT:
		arg = 1.0 / 2.0 * pi;
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

void ZkChrStg3Wv4C::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_GOZGOK, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}