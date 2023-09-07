#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Scenario/Stage2.h"
#include "Field.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv4.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv6L.h"

using std::make_unique;
using std::numbers::pi;



Stage2::Stage2() :
	progress(Stage2Progress::WAVE6),
	wave6count(1)
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
		break;

	case Stage2Progress::WAVE6:
		if (elapsed_time > 3000 && elapsed_time <= 5000 && wave6count == 1) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>());
			++wave6count;
		}
		else if (elapsed_time > 5000 && elapsed_time <= 7000 && wave6count == 2) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>());
			++wave6count;
		}
		else if (elapsed_time > 7000 && elapsed_time <= 9000 && wave6count == 3) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>());
			++wave6count;
		}
		else if (elapsed_time > 9000 && elapsed_time <= 11000 && wave6count == 4) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>());
			++wave6count;
		}
		else if (elapsed_time > 11000 && elapsed_time <= 13000 && wave6count == 5) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>());
			kept_clock = DxLib::GetNowCount();
			progress = Stage2Progress::WAVE7;
		}
		break;
		

	case Stage2Progress::WAVE7:
		break;

	case Stage2Progress::WAVE8:
		break;

	}
}