#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "Scenario/Stage3.h"
#include "Field.h"
#include "Character/EnemyCharacter/BossCharacter/Toroi.h"

using std::make_unique;


Stage3::Stage3() :
	progress(Stage3Progress::WAVE1)
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
		break;

	case Stage3Progress::BOSS:
		(*Field::IDENTIFIABLE_ENEMY_CHARACTERS)[CharacterID::TOROI] = make_unique<Toroi>();
		break;
	}
}