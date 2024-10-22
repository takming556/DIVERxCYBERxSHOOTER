#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "CollideRealm/CollideCircle.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1BsSp3.h"
#include "Offensive/Bullet/KurageAmeShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"


using std::make_unique;


const unsigned int ZkChrStg1BsSp3::INITIAL_HP = 30;
const unsigned int ZkChrStg1BsSp3::COLLIDANT_SIZE = 30;
const double ZkChrStg1BsSp3::DRAW_EXTRATE = 0.10;
const unsigned int ZkChrStg1BsSp3::NOZZLES = 15;
const unsigned int ZkChrStg1BsSp3::INTERVAL = 5000;


ZkChrStg1BsSp3::ZkChrStg1BsSp3(
	enum CharacterID given_id,
	double init_pos_x,
	double init_pos_y
):
	Character(
		given_id,	
		init_pos_x,
		init_pos_y,
		INITIAL_HP,
		make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)
	),
	last_barraged_clock(DxLib::GetNowCount() - DxLib::GetRand(INTERVAL))
{
}


void ZkChrStg1BsSp3::update() {
	int elapsed_time_since_last_barraged = DxLib::GetNowCount() - last_barraged_clock;
	if (elapsed_time_since_last_barraged > INTERVAL) {
		InFieldPosition pos = *position;
		for (int i = 0; i < NOZZLES; i++) {
			(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<KurageAmeShot>(pos.x, pos.y);
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
		}
		last_barraged_clock = DxLib::GetNowCount();
	}
}


void ZkChrStg1BsSp3::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_KURAGE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}