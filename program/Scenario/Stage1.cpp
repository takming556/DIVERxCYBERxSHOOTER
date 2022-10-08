#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;

Stage1::Stage1() :
	stage1_progress(Stage1Progress::A)
{
}


void Stage1::update() {
	elapsed_time = DxLib::GetNowCount() - kept_clock;

	if (stage1_progress == Stage1Progress::A && elapsed_time > 5000) {
		stage1_progress=Stage1Progress::B;
		kept_clock = DxLib::GetNowCount();
	}
	else if (stage1_progress == Stage1Progress::B && elapsed_time > 1000) {
		stage1_progress = Stage1Progress::B_LEFT_1;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(0, 620, 0, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_LEFT_1 && elapsed_time > 700) {
		stage1_progress = Stage1Progress::B_LEFT_2;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(0, 620, 0, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_LEFT_2 && elapsed_time > 700) {
		stage1_progress = Stage1Progress::B_LEFT_3;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(0, 620, 0, 100.0));
	}

}