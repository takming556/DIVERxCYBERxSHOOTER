#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Scenario/Stage2.h"
#include "Field.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv4.h"

using std::make_unique;
using std::numbers::pi;



Stage2::Stage2() :
	progress(Stage2Progress::A)
{
}

void Stage2::update() {
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	switch (progress) {
	case Stage2Progress::A:
		if (elapsed_time > 3000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv4>(
				0.0,
				742.0,
				250,
				-1.0 / 12.0 * pi,
				15,
				10)
			);
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg2Wv4>(
				620.0,
				742.0,
				250,
				13.0 / 12.0 * pi,
				15,
				10)
			);
			kept_clock = DxLib::GetNowCount();
			progress = Stage2Progress::B;
		}
		break;


	}
}