#include <memory>
#include <numbers>
#include <cmath>
#include "DxLib.h"
#include "enum.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv4.h"
#include "CollideRealm/CollideCircle.h"
#include "Field.h"
#include "Offensive/Bullet/GravityShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::sin;
using std::cos;
using std::tan;
using std::atan;
using std::numbers::pi;

const double ZkChrStg2Wv4::DRAW_EXTRATE = 0.05;
const unsigned int ZkChrStg2Wv4::SHOTS = 50;
const unsigned int ZkChrStg2Wv4::SHOT_INTERVAL = 200;

ZkChrStg2Wv4::ZkChrStg2Wv4(double init_pos_x, double init_pos_y, double init_speed, double init_arg, unsigned int init_hp, unsigned int collidant_size) :
	Character(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, collidant_size)),
	EnemyCharacter(init_hp),
	last_shot_clock(DxLib::GetNowCount()),
	shot_count(0),
	speed(init_speed),
	arg(init_arg),
	reflection_flag(false)
{
}


void ZkChrStg2Wv4::update() {
	if (reflection_flag == false) {
		if (position->x < 0.0 || position->x > 620.0) {
			reflection_flag = true;
			arg = -(arg + 1.0 / 2.0 * pi) - 1.0 / 2.0 * pi; // •ÎŠp‚ðyŽ²‘ÎÌ‚É”½“]
		}
	}
	if (reflection_flag == true) {
		if (position->x > 0.0 && position->x < 620.0) {
			reflection_flag = false;
		}
	}

	double update_delta_time = (double)(DxLib::GetNowHiPerformanceCount() - last_updated_clock) / 1000 / 1000;
	double delta_x = speed * update_delta_time * cos(arg);
	double delta_y = speed * update_delta_time * sin(arg);
	position->x += delta_x;
	position->y += delta_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	if (shot_count < SHOTS) {
		int shot_delta_time = DxLib::GetNowCount() - last_shot_clock;
		if (shot_delta_time > SHOT_INTERVAL) {
			Field::ENEMY_OFFENSIVES->push_back(make_unique<GravityShot>(
				position->x,
				position->y,
				1.0 / 2.0 * pi,
				20,
				2000000,
				15,
				1,
				SkinID::MAGNETIC_ARROW)
			);
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			++shot_count;
			last_shot_clock = DxLib::GetNowCount();
		}
	}
	collidant->update(position);
}


void ZkChrStg2Wv4::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_LIGHT_ELE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}