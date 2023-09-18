#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "Scenario/Stage3.h"
#include "Field.h"
#include "Character/EnemyCharacter/BossCharacter/Toroi.h"
#include"Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv1L.h"
#include"Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv1R.h"
#include"Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv2R.h"
#include"Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv2L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv6C.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv6LR.h"

using std::make_unique;


Stage3::Stage3() :
	progress(Stage3Progress::WAVE1),
	Wave1(1),
	Wave2(1)
{
}


void Stage3::update() {
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	switch (progress) {
	case Stage3Progress::WAVE1:
		if (elapsed_time > 1000 && elapsed_time<=2000 &&Wave1==1) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>());
			++Wave1;
		}
		else if (elapsed_time > 2000 && elapsed_time<=3000 &&Wave1==2) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>());
			++Wave1;
		}
		else if (elapsed_time > 3000 && elapsed_time <= 4000 && Wave1 == 3) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>());
			++Wave1;

		}
		else if (elapsed_time > 4000 && elapsed_time <= 5000 && Wave1 == 4) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>());
			++Wave1;
		}
		else if (elapsed_time > 5000 && elapsed_time <= 6000 && Wave1 == 5) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>());
			kept_clock = DxLib::GetNowCount();
			progress = Stage3Progress::WAVE2;
		}
		break;
		
	case Stage3Progress::WAVE2:
		if (elapsed_time > 1000 && elapsed_time <= 2000 && Wave2 == 1) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>());
			++Wave2;
		}
		else if (elapsed_time > 2000 && elapsed_time <= 3000 && Wave2 == 2) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>());
			++Wave2;
		}
		else if (elapsed_time > 3000 && elapsed_time <= 4000 && Wave2 == 3) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>());
			++Wave2;

		}
		else if (elapsed_time > 4000 && elapsed_time <= 5000 && Wave2 == 4) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>());
			++Wave2;
		}
		else if (elapsed_time > 5000 && elapsed_time <= 6000 && Wave2 == 5) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>());
			kept_clock = DxLib::GetNowCount();
			progress = Stage3Progress::WAVE3;
		}
		break;

	case Stage3Progress::WAVE3:
		break;
		
	case Stage3Progress::WAVE4:
		break;

	case Stage3Progress::WAVE5:
		break;

	case Stage3Progress::WAVE6:
		if (false) {
			if (elapsed_time > 3000) {
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6C>());
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6LR>(Stg3WAVE6LRType::LEFT));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6LR>(Stg3WAVE6LRType::RIGHT));
				kept_clock = DxLib::GetNowCount();
				progress = Stage3Progress::BOSS;
			}
		}
		else {
			(*Field::IDENTIFIABLE_ENEMY_CHARACTERS)[CharacterID::TOROI] = make_unique<Toroi>();
			progress = Stage3Progress::BOSS;
		}
		break;

	case Stage3Progress::BOSS:
		//kept_clock = DxLib::GetNowCount();
		break;
	}
}