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
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_LEFT_1 && elapsed_time > 2000) {
		stage1_progress = Stage1Progress::B_LEFT_2;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_LEFT_2 && elapsed_time > 2000) {
		stage1_progress = Stage1Progress::B_LEFT_3;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_LEFT_3 && elapsed_time > 4000) {
		stage1_progress = Stage1Progress::B_RIGHT_1;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_RIGHT_1 && elapsed_time > 2000) {
		stage1_progress = Stage1Progress::B_RIGHT_2;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_RIGHT_2 && elapsed_time > 2000) {
		stage1_progress = Stage1Progress::B_RIGHT_3;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
	}
	else if (stage1_progress == Stage1Progress::B_RIGHT_3 && elapsed_time > 5000) {
		stage1_progress = Stage1Progress::C1;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(-10, 650, 0, 65, -(1.0 / 6.0) * pi));
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(630, 400, pi, 65, 1.0 / 6.0 * pi));
	}
	else if (stage1_progress == Stage1Progress::C1 && elapsed_time > 8000) {
		stage1_progress = Stage1Progress::C2;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(-10, 650, 0, 65, -(1.0 / 6.0) * pi));
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(630, 400, pi, 65, 1.0 / 6.0 * pi));
	}
	else if (stage1_progress == Stage1Progress::C2 && elapsed_time > 10000) {
		stage1_progress = Stage1Progress::D;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(80, 540));
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(230, 610));
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(390, 610));
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(540, 540));

		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3L>(155, 575,  (1.0 / 6.0) * pi));
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3L>(465, 575, -(1.0 / 6.0) * pi));
	}
	else if (stage1_progress == Stage1Progress::D && elapsed_time > 11000) {
		stage1_progress = Stage1Progress::E;
		kept_clock = DxLib::GetNowCount();
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(80, 610));
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(230, 610));
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(390, 610));
		Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(540, 610));
	}



}