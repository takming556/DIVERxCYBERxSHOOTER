#include <string>
#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Character/Character.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/Neon.h"
#include "CollideRealm/CollideCircle.h"
#include "Position/InFieldPosition.h"
#include "FontHandles.h"
#include "Colors.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"
#include "Field.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"

using std::string;
using std::make_unique;
using std::numbers::pi;

const string Neon::NAME("���˂���");
const int Neon::INITIAL_POS_X = 310;
const int Neon::INITIAL_POS_Y = 620;
const unsigned int Neon::INITIAL_COLLIDANT_SIZE = 60;
const double Neon::DRAW_EXTRATE = 0.07;

const double Neon::NM3_SHOT_SPEED = 300;
const unsigned int Neon::NM3_COLLIDANT_SIZE = 10;
const unsigned int Neon::NM3_INTERVAL = 120;

const unsigned int Neon::INITIAL_HP = 1000;

// 100% -  90% NORMAL1
//  90% -  75% SP1
//  75% -  65% NORMAL2
//  65% -  50% SP2
//  50% -  40% NORMAL3
//  40% -  25% SP3
//  25% -  15% NORMAL4
//  15% -   0% SP4

const double Neon::SP1_ACTIVATE_HP_RATIO = 90.0 / 100.0;
const double Neon::SP1_TERMINATE_HP_RATIO = 75.0 / 100.0;
const double Neon::SP2_ACTIVATE_HP_RATIO = 65.0 / 100.0;
const double Neon::SP2_TERMINATE_HP_RATIO = 50.0 / 100.0;
const double Neon::SP3_ACTIVATE_HP_RATIO = 40.0 / 100.0;
const double Neon::SP3_TERMINATE_HP_RATIO = 25.0 / 100.0;
const double Neon::SP4_ACTIVATE_HP_RATIO = 15.0 / 100.0;


const unsigned int Neon::SP1_ACCOMPLISH_BONUS = 150000;
const unsigned int Neon::SP2_ACCOMPLISH_BONUS = 200000;
const unsigned int Neon::SP3_ACCOMPLISH_BONUS = 350000;
const unsigned int Neon::SP4_ACCOMPLISH_BONUS = 500000;

Neon::Neon() :
	Character(
		INITIAL_POS_X,
		INITIAL_POS_Y,
		make_unique<CollideCircle>(INITIAL_POS_X, INITIAL_POS_Y, INITIAL_COLLIDANT_SIZE)
	),
	EnemyCharacter(INITIAL_HP),
	BossCharacter(NAME),
	status(NeonStatus::NORMAL3),
	nm3_shot_arg(0.0),
	nm3_last_generated_clock(DxLib::GetNowCount())
{
}

void Neon::update() {
	switch (status) {
	case NeonStatus::NORMAL1:
		nm1();
		break;

	case NeonStatus::SP1:		// �u������~�v
		sp1();
		break;

	case NeonStatus::NORMAL2:
		nm2();
		break;

	case NeonStatus::SP2:		// �u�V�_���܂��M��v
		sp2();
		break;

	case NeonStatus::NORMAL3:
		nm3();
		break;

	case NeonStatus::SP3:		// �u���C��тт郉�C�f���X�p�[�N�v
		sp3();
		break;

	case NeonStatus::NORMAL4:
		nm4();
		break;

	case NeonStatus::SP4:		// �u�V���b�t���g���C���v
		sp4();
		break;
	}
	collidant->update(position);
	last_updated_clock = DxLib::GetNowHiPerformanceCount();
}

void Neon::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_NEON, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}

void Neon::nm1() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP1_ACTIVATE_HP_RATIO) {
	}
	else {
		status = NeonStatus::SP1;
	}
}

void Neon::nm2() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP2_ACTIVATE_HP_RATIO) {
	}
	else {
		status = NeonStatus::SP2;
	}
}

void Neon::nm3() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP3_ACTIVATE_HP_RATIO) {
		int nm3_generated_delta_time = DxLib::GetNowCount() - nm3_last_generated_clock;
		if (nm3_generated_delta_time > NM3_INTERVAL){
			for (int i = 0; i < 9; ++i) {
				SkinID oval_handles = Neon::get_nm3_oval_image_handles(i+1);
				double arg = nm3_shot_arg + 2.0 / 9.0 * pi * i;
				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					position->x,
					position->y,
					arg,
					NM3_SHOT_SPEED,
					NM3_COLLIDANT_SIZE,
					1,
					oval_handles)
				);
			}
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			nm3_shot_arg += 1.0 / 10.0 * pi;
			nm3_last_generated_clock = DxLib::GetNowCount();
		}
	}
	else {
		status = NeonStatus::SP3;
	}
}

void Neon::nm4() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP4_ACTIVATE_HP_RATIO) {
	}
	else {
		status = NeonStatus::SP4;
	}
}

void Neon::sp1() {		// �u������~�v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP1_TERMINATE_HP_RATIO) {
	}
	else {
		status = NeonStatus::NORMAL2;
	}
}

void Neon::sp2() {		// �u�V�_���܂��M��v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP2_TERMINATE_HP_RATIO) {
	}
	else {
		status = NeonStatus::NORMAL3;
	}
}

void Neon::sp3() {		// �u���C��тт郉�C�f���X�p�[�N�v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP3_TERMINATE_HP_RATIO) {
	}
	else {
		status = NeonStatus::NORMAL4;
	}
}

void Neon::sp4() {		// �u�V���b�t���g���C���v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > 0) {
	}
	else {

	}
}

enum SkinID Neon::get_nm3_oval_image_handles(int count) {
	SkinID OvalHandles = SkinID::NEON_NM3_RED;
	
	switch (count) {
	case 1:
		OvalHandles = SkinID::NEON_NM3_RED;
		++count;
		break;
	case 2:
		OvalHandles = SkinID::NEON_NM3_ORANGE;
		++count;
		break;
	case 3:
		OvalHandles = SkinID::NEON_NM3_YELLOW;
		++count;
		break;
	case 4:
		OvalHandles = SkinID::NEON_NM3_GREEN;
		++count;
		break;
	case 5:
		OvalHandles = SkinID::NEON_NM3_TEAL;
		++count;
		break;
	case 6:
		OvalHandles = SkinID::NEON_NM3_AQUA;
		++count;
		break;
	case 7:
		OvalHandles = SkinID::NEON_NM3_BLUE;
		++count;
		break;
	case 8:
		OvalHandles = SkinID::NEON_NM3_PURPLE;
		++count;
		break;
	case 9:
		OvalHandles = SkinID::NEON_NM3_FUCHSIA;
		++count;
		break;
	}
	return OvalHandles;
}