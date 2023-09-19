#include <memory>
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
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv7L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv7R.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv8L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv8R.h"


using std::make_unique;
using std::numbers::pi;

const double Stage2::WAVE8_LINE_UP_X_L1 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 1.0;
const double Stage2::WAVE8_LINE_UP_X_L2 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 2.0;
const double Stage2::WAVE8_LINE_UP_X_L3 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 3.0;
const double Stage2::WAVE8_LINE_UP_X_L4 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 4.0;
const double Stage2::WAVE8_LINE_UP_X_L5 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 5.0;
const double Stage2::WAVE8_LINE_UP_X_L6 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 6.0;
const double Stage2::WAVE8_LINE_UP_X_L7 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 7.0;
const double Stage2::WAVE8_LINE_UP_X_L8 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 8.0;
const double Stage2::WAVE8_LINE_UP_X_R1 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 8.0;
const double Stage2::WAVE8_LINE_UP_X_R2 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 7.0;
const double Stage2::WAVE8_LINE_UP_X_R3 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 6.0;
const double Stage2::WAVE8_LINE_UP_X_R4 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 5.0;
const double Stage2::WAVE8_LINE_UP_X_R5 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 4.0;
const double Stage2::WAVE8_LINE_UP_X_R6 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 3.0;
const double Stage2::WAVE8_LINE_UP_X_R7 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 2.0;
const double Stage2::WAVE8_LINE_UP_X_R8 = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 9.0 * 1.0;

Stage2::Stage2() :
	progress(Stage2Progress::WAVE8),
	wave6count(1),
	wave7count(1),
	wave8count(1)
{
}

void Stage2::update() {
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	switch (progress) {
	case Stage2Progress::WAVE1:
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
		if (elapsed_time > 2000 && elapsed_time <= 4000 && wave6count == 1) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L1));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R1));
			++wave6count;
		}
		else if (elapsed_time > 4000 && elapsed_time <= 6000 && wave6count == 2) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L2));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R2));
			++wave6count;
		}
		else if (elapsed_time > 6000 && elapsed_time <= 8000 && wave6count == 3) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L3));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R3));
			++wave6count;
		}
		else if (elapsed_time > 8000 && elapsed_time <= 10000 && wave6count == 4) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L4));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R4));
			++wave6count;
		}
		else if (elapsed_time > 10000 && elapsed_time <= 12000 && wave6count == 5) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L5));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R5));
			kept_clock = DxLib::GetNowCount();
			progress = Stage2Progress::WAVE7;
		}
		break;
		

	case Stage2Progress::WAVE7:
		if (elapsed_time > 600 && elapsed_time <= 1200 && wave7count == 1) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7L>(CharacterID::ZKCHRSTG2WV7_L1));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7R>(CharacterID::ZKCHRSTG2WV7_R1));
			++wave7count;
		}
		else if (elapsed_time > 1200 && elapsed_time <= 1800 && wave7count == 2) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7L>(CharacterID::ZKCHRSTG2WV7_L2));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7R>(CharacterID::ZKCHRSTG2WV7_R2));
			++wave7count;
		}
		else if (elapsed_time > 1800 && elapsed_time <= 2400 && wave7count == 3) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7L>(CharacterID::ZKCHRSTG2WV7_L3));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7R>(CharacterID::ZKCHRSTG2WV7_R3));
			++wave7count;
		}
		else if (elapsed_time > 2400 && elapsed_time <= 3000 && wave7count == 4) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7L>(CharacterID::ZKCHRSTG2WV7_L4));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7R>(CharacterID::ZKCHRSTG2WV7_R4));
			++wave7count;
		}
		else if (elapsed_time > 3000 && elapsed_time <= 3600 && wave7count == 5) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7L>(CharacterID::ZKCHRSTG2WV7_L5));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7R>(CharacterID::ZKCHRSTG2WV7_R5));
			kept_clock = DxLib::GetNowCount();
			progress = Stage2Progress::BOSS;	// 後で修正する
		}
		break;

	case Stage2Progress::WAVE8:
		if (true) {
			if (elapsed_time > 600 && elapsed_time <= 1200 && wave8count == 1) {
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L1, WAVE8_LINE_UP_X_L1, 250));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R1, WAVE8_LINE_UP_X_R1, 250));
				++wave8count;
			}
			else if (elapsed_time > 1200 && elapsed_time <= 1800 && wave8count == 2) {
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L2, WAVE8_LINE_UP_X_L2, 200));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R2, WAVE8_LINE_UP_X_R2, 200));
				++wave8count;
			}
			else if (elapsed_time > 1800 && elapsed_time <= 2400 && wave8count == 3) {
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L3, WAVE8_LINE_UP_X_L3, 150));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R3, WAVE8_LINE_UP_X_R3, 150));
				++wave8count;
			}
			else if (elapsed_time > 2400 && elapsed_time <= 3000 && wave8count == 4) {
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L4, WAVE8_LINE_UP_X_L4, 100));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R4, WAVE8_LINE_UP_X_R4, 100));
				++wave8count;
			}
			else if (elapsed_time > 3000 && elapsed_time <= 3600 && wave8count == 5) {
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L5, WAVE8_LINE_UP_X_L5, 100));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R5, WAVE8_LINE_UP_X_R5, 100));
				++wave8count;
			}
			else if (elapsed_time > 3600 && elapsed_time <= 4200 && wave8count == 6) {
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L6, WAVE8_LINE_UP_X_L6, 150));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R6, WAVE8_LINE_UP_X_R6, 150));
				++wave8count;
			}
			else if (elapsed_time > 4200 && elapsed_time <= 4800 && wave8count == 7) {
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L7, WAVE8_LINE_UP_X_L7, 200));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R7, WAVE8_LINE_UP_X_R7, 200));
				++wave8count;
			}
			else if (elapsed_time > 4800 && elapsed_time <= 5400 && wave8count == 8) {
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L8, WAVE8_LINE_UP_X_L8, 250));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R8, WAVE8_LINE_UP_X_R8, 250)); 
				++wave8count;
			}

			if (elapsed_time > 16000) {
				ZkChrStg2Wv8L::WAIT_FLAG_L = Stg2WAVE8WaitFlag::GO;
				ZkChrStg2Wv8R::WAIT_FLAG_R = Stg2WAVE8WaitFlag::GO;
				kept_clock = DxLib::GetNowCount();
				progress = Stage2Progress::BOSS;	// 後で修正する
			}
		}
		if (false) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<Neon>());
			progress = Stage2Progress::BOSS;
		}
		break;

	case Stage2Progress::BOSS:
		//kept_clock = DxLib::GetNowCount();
		break;

	}
}