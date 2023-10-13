#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv6C.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;

const double ZkChrStg3Wv6C::INIT_POS_X = 310;
const double ZkChrStg3Wv6C::INIT_POS_Y = 800;
const double ZkChrStg3Wv6C::INIT_ARG = 3.0 / 2.0 * pi;
const double ZkChrStg3Wv6C::INIT_SPEED = 200;
const unsigned int ZkChrStg3Wv6C::INITIAL_HP = 100;
const unsigned int ZkChrStg3Wv6C::COLLIDANT_SIZE = 30;
const unsigned int ZkChrStg3Wv6C::GENERATED_INTERVAL = 2000;
const double ZkChrStg3Wv6C::SHOT_RADIANT = 3.0 / 2.0 * pi;
const double ZkChrStg3Wv6C::SHOT_SPEED = 200;
const unsigned int ZkChrStg3Wv6C::SHOT_COLLIDANT_SIZE = 10;
const unsigned int ZkChrStg3Wv6C::ENTER_TIME = 1000;
const unsigned int ZkChrStg3Wv6C::STAY_TIME = 20000;

const double ZkChrStg3Wv6C::DRAW_EXTRATE = 0.10;

ZkChrStg3Wv6C::ZkChrStg3Wv6C() :
	Character(
		CharacterID::ZKCHRSTG3WV6_C,
		INIT_POS_X,
		INIT_POS_Y,
		INITIAL_HP,
		make_unique<CollideCircle>(INIT_POS_X, INIT_POS_Y, COLLIDANT_SIZE)
	),
	arg(INIT_ARG),
	speed(INIT_SPEED),
	last_generated_clock(0),
	move_clock(DxLib::GetNowCount()),
	generated_x(10),
	generated_y(600),
	move_status(Stg3WAVE6CMoveFlag::ENTER),
	status_flag(Stg3WAVE6CGenerateFlag::DOWN)
{
}

void ZkChrStg3Wv6C::update() {
	int elapsed_time = DxLib::GetNowCount() - move_clock;

	if (move_status == Stg3WAVE6CMoveFlag::ENTER) {
		if (elapsed_time > ENTER_TIME) {
			speed = 0;
			move_status = Stg3WAVE6CMoveFlag::STAY;
		}
	}
	else if (move_status == Stg3WAVE6CMoveFlag::STAY) {
		if (elapsed_time > ENTER_TIME + STAY_TIME) {
			arg = 1.0 / 2.0 * pi;
			speed = 100;
			move_status = Stg3WAVE6CMoveFlag::EXIT;
		}
		int generated_delta_time = DxLib::GetNowCount() - last_generated_clock;
		if (generated_delta_time > GENERATED_INTERVAL) {
			generated_x = 10;
			generated_y = 600;
			for (int i = 0; i < 13; ++i) {
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					generated_x,
					generated_y,
					SHOT_RADIANT,
					SHOT_SPEED,
					SHOT_COLLIDANT_SIZE,
					1,
					SkinID::STG3_WAVE6_C_ANCHOR
				);

				generated_x += 50;

				if (status_flag == Stg3WAVE6CGenerateFlag::UP) {
					generated_y += 50;
				}
				else if (status_flag == Stg3WAVE6CGenerateFlag::DOWN) {
					generated_y -= 50;
				}
				if (generated_y == 500) {
					status_flag = Stg3WAVE6CGenerateFlag::UP;
				}
				else if (generated_y == 600) {
					status_flag = Stg3WAVE6CGenerateFlag::DOWN;
				}
			}
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			last_generated_clock = DxLib::GetNowCount();
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

void ZkChrStg3Wv6C::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_GOZGOK, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}