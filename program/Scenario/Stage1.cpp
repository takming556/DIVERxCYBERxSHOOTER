#include <memory>
#include <numbers>
#include <cmath>
#include "DxLib.h"
#include "enum.h"
#include "GameConductor.h"
#include "Scenario/Stage1.h"
#include "Field.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv1.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv2.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv3S.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv3L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv4.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv5S.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1Wv5L.h"
#include "Character/EnemyCharacter/BossCharacter/Mofu.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "SoundHandles.h"
#include "Offensive/Bullet/HomingShot/HomingShot.h"
#include "Offensive/Bullet/GravityShot.h"

using std::make_unique;
using std::numbers::pi;
using std::atan2;


Stage1::Stage1() :
	stage1_progress(Stage1Progress::START)
{
}


void Stage1::update() {

	int elapsed_time = DxLib::GetNowCount() - kept_clock;

	switch (stage1_progress) {
	//case Stage1Progress::TEST:
	//	if (elapsed_time > 1000) {
	//		for (int i = 0; i < 16; i++) {
	//			for (int j = 0; j < 20; j++) {
	//				Field::ENEMY_OFFENSIVES->push_back(make_unique<GravityShot>(i * 40, j * 40, 1.0 / 2.0 * pi, 50, 1000000, 10, 10000, SkinID::GRAVITYSHOTTEST));
	//				double arg = atan2(Field::MY_CHARACTER->position->y, Field::MY_CHARACTER->position->x);
	//				//Field::ENEMY_OFFENSIVES->push_back(make_unique<HomingShot>(i * 80, j * 80, 1 / 2 * pi, 10, 20, 1, SkinID::HOMINGSHOTTEST));
	//			}
	//		}
	//		kept_clock = DxLib::GetNowCount();
	//		stage1_progress = Stage1Progress::DONOTHING;
	//	}
	//	break;
	//case Stage1Progress::DONOTHING:
	//	break;
	case Stage1Progress::START:
		if (elapsed_time > 5000) {//5
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_LEFT_1;
		}
		break;

	case Stage1Progress::A_LEFT_1:
		if (elapsed_time > 2000) {//7
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_LEFT_2;
		}
		break;

	case Stage1Progress::A_LEFT_2:
		if (elapsed_time > 2000) {//9
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_LEFT_3;
		}
		break;

	case Stage1Progress::A_LEFT_3:
		if (elapsed_time > 4000) {//13
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_RIGHT_1;
		}
		break;

	case Stage1Progress::A_RIGHT_1:
		if (elapsed_time > 2000) {//15
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_RIGHT_2;
		}
		break;

	case Stage1Progress::A_RIGHT_2:
		if (elapsed_time > 2000) {//17
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_RIGHT_3;
		}
		break;

	case Stage1Progress::A_RIGHT_3:
		if (elapsed_time > 5000) {//22
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(-10, 650, 0, 65, -(1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(630, 400, pi, 65, 1.0 / 6.0 * pi));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::B1;
		}
		break;

	case Stage1Progress::B1:
		if (elapsed_time > 8000) {//30
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(-10, 650, 0, 65, -(1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(630, 400, pi, 65, 1.0 / 6.0 * pi));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::B2;
		}
		break;

	case Stage1Progress::B2:
		if (elapsed_time > 10000) {//40
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
		if (elapsed_time > 20000) {//60
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(80, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D1;
		}
		break;

	case Stage1Progress::D1:
		if (elapsed_time > 2000) {//62
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(230, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D2;
		}
		break;

	case Stage1Progress::D2:
		if (elapsed_time > 2000) {//64
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(390, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D3;
		}
		break;

	case Stage1Progress::D3:
		if (elapsed_time > 2000) {//66
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(540, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D4;
		}
		break;

	case Stage1Progress::D4:
		if (elapsed_time > 8000) {//74
			(*Field::IDENTIFIABLE_ENEMY_CHARACTERS)[CharacterID::ZKCHRSTG1WV5S_L] = make_unique<ZkChrStg1Wv5S>(135, 480, 1.0 / 8.0 * pi);
			(*Field::IDENTIFIABLE_ENEMY_CHARACTERS)[CharacterID::ZKCHRSTG1WV5S_R] = make_unique<ZkChrStg1Wv5S>(485, 480, -(1.0 / 8.0) * pi);
			(*Field::IDENTIFIABLE_ENEMY_CHARACTERS)[CharacterID::ZKCHRSTG1WV5L] = make_unique<ZkChrStg1Wv5L>(310, 550);
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::E;
		}
		break;

	case Stage1Progress::E:
	{
		bool mofu_advent_ready_flag =
			(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_L] == true &&
			(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_R] == true &&
			(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5L] == true;
		if (mofu_advent_ready_flag == true) {
			(*Field::IDENTIFIABLE_ENEMY_CHARACTERS)[CharacterID::MOFU] = make_unique<Mofu>();
			stage1_progress = Stage1Progress::MOFU;
		}
	}
		if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_L] == false) {
			if ((*Field::IDENTIFIABLE_ENEMY_CHARACTERS)[CharacterID::ZKCHRSTG1WV5S_L]->is_dead() == true) {
				(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_L] = true;
				Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::ZKCHRSTG1WV5S_L);
				DxLib::PlaySoundMem(SoundHandles::ZAKOCRASH, DX_PLAYTYPE_BACK);
			}
		}
		if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_R] == false) {
			if ((*Field::IDENTIFIABLE_ENEMY_CHARACTERS)[CharacterID::ZKCHRSTG1WV5S_R]->is_dead() == true) {
				(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_R] = true;
				Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::ZKCHRSTG1WV5S_R);
				DxLib::PlaySoundMem(SoundHandles::ZAKOCRASH, DX_PLAYTYPE_BACK);
			}
		}
		if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5L] == false) {
			if ((*Field::IDENTIFIABLE_ENEMY_CHARACTERS)[CharacterID::ZKCHRSTG1WV5L]->is_dead() == true) {
				(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5L] = true;
				Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::ZKCHRSTG1WV5L);
				DxLib::PlaySoundMem(SoundHandles::ZAKOCRASH, DX_PLAYTYPE_BACK);
			}
		}
		break;

	case Stage1Progress::MOFU:
		if ((*Field::DEAD_FLAGS)[CharacterID::MOFU] == false) {
			if ((*Field::IDENTIFIABLE_ENEMY_CHARACTERS)[CharacterID::MOFU]->is_dead() == true) {
				(*Field::DEAD_FLAGS)[CharacterID::MOFU] = true;
				Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::MOFU);
				DxLib::PlaySoundMem(SoundHandles::BOSSCRASH, DX_PLAYTYPE_BACK);
				GameConductor::SCORE += Mofu::CRUSH_BONUS;

				if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1BSSP3_A] == false) {
					Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::ZKCHRSTG1BSSP3_A);
				}
				if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1BSSP3_B] == false) {
					Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::ZKCHRSTG1BSSP3_B);
				}
				if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1BSSP3_C] == false) {
					Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::ZKCHRSTG1BSSP3_C);
				}
				if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1BSSP3_D] == false) {
					Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::ZKCHRSTG1BSSP3_D);
				}

				stage1_progress = Stage1Progress::FINISH;
				kept_clock = DxLib::GetNowCount();
			}
		}
		break;

	case Stage1Progress::FINISH:
		break;
	}


}