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
		stage1_progress=Stage1Progress::B_LEFT_1;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 620, 0, 100.0));
	}
	//else if (stage1_progress == Stage1Progress::B && elapsed_time > 1000) {
	//	stage1_progress = Stage1Progress::B_LEFT_1;
	//	kept_clock = DxLib::GetNowCount();
	//	Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 620, 0, 100.0));
	//}
	else if (stage1_progress == Stage1Progress::B_LEFT_1 && elapsed_time > 2000) {
		stage1_progress = Stage1Progress::B_LEFT_2;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 620, 0, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_LEFT_2 && elapsed_time > 2000) {
		stage1_progress = Stage1Progress::B_LEFT_3;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 620, 0, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_LEFT_3 && elapsed_time > 4000) {
		stage1_progress = Stage1Progress::B_RIGHT_1;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, pi, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_RIGHT_1 && elapsed_time > 2000) {
		stage1_progress = Stage1Progress::B_RIGHT_2;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, pi, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_RIGHT_2 && elapsed_time > 2000) {
		stage1_progress = Stage1Progress::B_RIGHT_3;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, pi, 100.0));
	}


}