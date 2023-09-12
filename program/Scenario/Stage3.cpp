#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "Scenario/Stage3.h"
#include "Field.h"
#include "Character/EnemyCharacter/BossCharacter/Toroi.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv6C.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv6LR.h"

using std::make_unique;


Stage3::Stage3() :
	progress(Stage3Progress::WAVE6)
{
}


void Stage3::update() {
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	switch (progress) {
	case Stage3Progress::WAVE1:
		break;
		
	case Stage3Progress::WAVE2:
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
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6LR>(CharacterID::ZKCHRSTG3WV4_L));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6LR>(CharacterID::ZKCHRSTG3WV4_R));
				kept_clock = DxLib::GetNowCount();
				progress = Stage3Progress::BOSS;
			}
		}
		else {
			Field::ENEMY_CHARACTERS->push_back(make_unique<Toroi>());
			progress = Stage3Progress::BOSS;
		}
		break;

	case Stage3Progress::BOSS:
		//kept_clock = DxLib::GetNowCount();
		break;
	}
}