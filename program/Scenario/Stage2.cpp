﻿#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Scenario/Stage2.h"
#include "Field.h"
#include "Character/EnemyCharacter/BossCharacter/Neon.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv4.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv5L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv5R.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv6L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv6R.h"

#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Character/EnemyCharacter/BossCharacter/Toroi.h"

using std::make_unique;
using std::numbers::pi;



Stage2::Stage2() :
	progress(Stage2Progress::WAVE1),
	wave6count(1)
{
}

void Stage2::update() {
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	switch (progress) {
	case Stage2Progress::WAVE1:
		(*Field::ENEMY_BULLETS)[Offensive::GENERATE_ID()] = make_unique<StraightShot>(
			Field::PIXEL_SIZE_X / 2,
			Field::PIXEL_SIZE_Y / 2,
			0,
			0,
			10,
			10000,
			SkinID::BUBBLE_GENERIC
		);
		Field::ENEMY_CHARACTERS->push_back(make_unique<Toroi>());
		kept_clock = DxLib::GetNowCount();
		progress = Stage2Progress::WAVE2;
		break;

	case Stage2Progress::WAVE2:
		break;

	case Stage2Progress::WAVE3:
		break;

	case Stage2Progress::WAVE4:
		if (elapsed_time > 3000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv4>(
				CharacterID::ZKCHRSTG2WV4_L,
				0.0,
				742.0,
				250,
				-1.0 / 12.0 * pi,
				15,
				10)
			);
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv4>(
				CharacterID::ZKCHRSTG2WV4_R,
				620.0,
				742.0,
				250,
				13.0 / 12.0 * pi,
				15,
				10)
			);
			kept_clock = DxLib::GetNowCount();
			progress = Stage2Progress::WAVE5;
		}
		break;

	case Stage2Progress::WAVE5:
		if (elapsed_time > 3000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv5L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv5R>());
			kept_clock = DxLib::GetNowCount();
			progress = Stage2Progress::WAVE6;
		}
		break;

	case Stage2Progress::WAVE6:
		if (elapsed_time > 20000 && elapsed_time <= 22000 && wave6count == 1) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L1));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R1));
			++wave6count;
		}
		else if (elapsed_time > 22000 && elapsed_time <= 24000 && wave6count == 2) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L2));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R2));
			++wave6count;
		}
		else if (elapsed_time > 24000 && elapsed_time <= 26000 && wave6count == 3) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L3));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R3));
			++wave6count;
		}
		else if (elapsed_time > 26000 && elapsed_time <= 28000 && wave6count == 4) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L4));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R4));
			++wave6count;
		}
		else if (elapsed_time > 28000 && elapsed_time <= 30000 && wave6count == 5) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L5));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R5));
			kept_clock = DxLib::GetNowCount();
			progress = Stage2Progress::WAVE7;
		}
		break;
		

	case Stage2Progress::WAVE7:
		break;

	case Stage2Progress::WAVE8:
		if (false) {

		}
		if (true) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<Neon>());
			progress = Stage2Progress::BOSS;
		}
		break;

	case Stage2Progress::BOSS:
		//kept_clock = DxLib::GetNowCount();
		break;

	}
}