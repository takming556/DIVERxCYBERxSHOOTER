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
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv7.h"

using std::make_unique;
using std::numbers::pi;



Stage2::Stage2() :
	progress(Stage2Progress::WAVE7),
	wave6count(1),
	wave7count(1)
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
		if (elapsed_time > 1200 && elapsed_time <= 2400 && wave7count == 1) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7>(CharacterID::ZKCHRSTG2WV7_L1));
			++wave7count;
		}
		else if (elapsed_time > 2400 && elapsed_time <= 3600 && wave7count == 2) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7>(CharacterID::ZKCHRSTG2WV7_L2));
			++wave7count;
		}
		else if (elapsed_time > 3600 && elapsed_time <= 4800 && wave7count == 3) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7>(CharacterID::ZKCHRSTG2WV7_L3));
			++wave7count;
		}
		else if (elapsed_time > 4800 && elapsed_time <= 6000 && wave7count == 4) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7>(CharacterID::ZKCHRSTG2WV7_L4));
			++wave7count;
		}
		else if (elapsed_time > 6000 && elapsed_time <= 7200 && wave7count == 5) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7>(CharacterID::ZKCHRSTG2WV7_L5));
			kept_clock = DxLib::GetNowCount();
			progress = Stage2Progress::WAVE1;	// 後で修正する
		}
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