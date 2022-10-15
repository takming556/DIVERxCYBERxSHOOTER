#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;

Stage1::Stage1() :
	stage1_progress(Stage1Progress::START)
{
}


void Stage1::update() {

	elapsed_time = DxLib::GetNowCount() - kept_clock;

	switch (stage1_progress) {
	case Stage1Progress::START:
		if (elapsed_time > 5000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_LEFT_1;
		}
		break;

	case Stage1Progress::A_LEFT_1:
		if (elapsed_time > 2000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_LEFT_2;
		}
		break;

	case Stage1Progress::A_LEFT_2:
		if (elapsed_time > 2000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_LEFT_3;
		}
		break;

	case Stage1Progress::A_LEFT_3:
		if (elapsed_time > 4000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_RIGHT_1;
		}
		break;

	case Stage1Progress::A_RIGHT_1:
		if (elapsed_time > 2000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_RIGHT_2;
		}
		break;

	case Stage1Progress::A_RIGHT_2:
		if (elapsed_time > 2000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_RIGHT_3;
		}
		break;

	case Stage1Progress::A_RIGHT_3:
		if (elapsed_time > 5000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(-10, 650, 0, 65, -(1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(630, 400, pi, 65, 1.0 / 6.0 * pi));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::B1;
		}
		break;

	case Stage1Progress::B1:
		if (elapsed_time > 8000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(-10, 650, 0, 65, -(1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(630, 400, pi, 65, 1.0 / 6.0 * pi));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::B2;
		}
		break;

	case Stage1Progress::B2:
		if (elapsed_time > 10000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(80, 540));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(230, 610));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(390, 610));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(540, 540));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3L>(155, 575, (1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3L>(465, 575, -(1.0 / 6.0) * pi));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::C;
		}
		break;

	case Stage1Progress::C:
		if (elapsed_time > 11000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(80, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D1;
		}
		break;

	case Stage1Progress::D1:
		if (elapsed_time > 2000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(230, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D2;
		}
		break;

	case Stage1Progress::D2:
		if (elapsed_time > 2000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(390, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D3;
		}
		break;

	case Stage1Progress::D3:
		if (elapsed_time > 2000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(540, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D4;
		}
		break;

	}


}