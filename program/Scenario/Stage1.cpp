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
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Offensive/Laser/PolarLaser.h"

using std::make_unique;
using std::numbers::pi;
using std::atan2;

Stage1Progress Stage1::PROGRESS;

Stage1::Stage1()
{
	PROGRESS = Stage1Progress::START;
}


void Stage1::update() {

	int elapsed_time = DxLib::GetNowCount() - kept_clock;

	switch (PROGRESS) {
	case Stage1Progress::TEST:
		if (elapsed_time > 1000) {
			(*Field::ENEMY_LASERS)[Laser::GENERATE_ID()] = make_unique<PolarLaser>(
				InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_Y / 2,
				1.0 / 4.0 * pi,
				150.0,
				100.0,
				10.0,
				true,
				SkinID::LASER_TEST
			);
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::DONOTHING;
		}
		break;
	case Stage1Progress::DONOTHING:
		break;
	case Stage1Progress::START:
		if (elapsed_time > 5000) {//5
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_L1, -10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_LEFT_1;
			Field::MUSIC_NAME_DISPLAY.reset(new Scenario(L"「Jelly Carnival」"));
		}
		break;

	case Stage1Progress::A_LEFT_1:
		if (elapsed_time > 2000) {//7
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_L2, -10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_LEFT_2;
		}
		break;

	case Stage1Progress::A_LEFT_2:
		if (elapsed_time > 2000) {//9
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_L3, -10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_LEFT_3;
		}
		break;

	case Stage1Progress::A_LEFT_3:
		if (elapsed_time > 4000) {//13
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_R1, 630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_RIGHT_1;
		}
		break;

	case Stage1Progress::A_RIGHT_1:
		if (elapsed_time > 2000) {//15
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_R2, 630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_RIGHT_2;
		}
		break;

	case Stage1Progress::A_RIGHT_2:
		if (elapsed_time > 2000) {//17
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_R3, 630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_RIGHT_3;
		}
		break;

	case Stage1Progress::A_RIGHT_3:
		if (elapsed_time > 5000) {//22
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(CharacterID::ZKCHRSTG1WV2_1U, -10, 650, 0, 65, -(1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(CharacterID::ZKCHRSTG1WV2_1L, 630, 400, pi, 65, 1.0 / 6.0 * pi));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::B1;
		}
		break;

	case Stage1Progress::B1:
		if (elapsed_time > 8000) {//30
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(CharacterID::ZKCHRSTG1WV2_2U, -10, 650, 0, 65, -(1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(CharacterID::ZKCHRSTG1WV2_2L, 630, 400, pi, 65, 1.0 / 6.0 * pi));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::B2;
		}
		break;

	case Stage1Progress::B2:
		if (elapsed_time > 10000) {//40
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(CharacterID::ZKCHRSTG1WV3S_1, 80, 540 + 250));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(CharacterID::ZKCHRSTG1WV3S_2, 230, 610 + 250));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(CharacterID::ZKCHRSTG1WV3S_3, 390, 610 + 250));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(CharacterID::ZKCHRSTG1WV3S_4, 540, 540 + 250));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3L>(CharacterID::ZKCHRSTG1WV3L_1, 155, 575 + 250, (1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3L>(CharacterID::ZKCHRSTG1WV3L_2, 465, 575 + 250, -(1.0 / 6.0) * pi));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::C;
		}
		break;

	case Stage1Progress::C:
		if (elapsed_time > 18000) {//58
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(CharacterID::ZKCHRSTG1WV4_A, 80, 640 + 150));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::D1;
		}
		break;

	case Stage1Progress::D1:
		if (elapsed_time > 1000) {//59
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(CharacterID::ZKCHRSTG1WV4_B, 230, 640 + 150));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::D2;
		}
		break;

	case Stage1Progress::D2:
		if (elapsed_time > 1000) {//60
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(CharacterID::ZKCHRSTG1WV4_C, 390, 640 + 150));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::D3;
		}
		break;

	case Stage1Progress::D3:
		if (elapsed_time > 1000) {//61
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(CharacterID::ZKCHRSTG1WV4_D, 540, 640 + 150));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::D4;
		}
		break;

	case Stage1Progress::D4:
		if (elapsed_time > 10000) {//71
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv5S>(CharacterID::ZKCHRSTG1WV5S_L, 135, 480 + 150, 1.0 / 8.0 * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv5S>(CharacterID::ZKCHRSTG1WV5S_R, 485, 480 + 150, -(1.0 / 8.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv5L>(CharacterID::ZKCHRSTG1WV5L, 310, 550 + 150));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::E;
		}
		break;

	case Stage1Progress::E:
	{
		bool mofu_advent_ready_flag = (
			(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_L] == true &&
			(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_R] == true &&
			(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5L] == true ||
			elapsed_time > 15000
		);
		if (mofu_advent_ready_flag == true) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<Mofu>());
			PROGRESS = Stage1Progress::MOFU;
		}
	}
		//if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_L] == false) {
		//	if (Field::GET_ENEMY_CHARACTER(CharacterID::ZKCHRSTG1WV5S_L)->is_dead() == true) {
		//		(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_L] = true;
		//		Field::ERASE_ENEMY_CHARACTER(CharacterID::ZKCHRSTG1WV5S_L);
		//		DxLib::PlaySoundMem(SoundHandles::ZAKOCRASH, DX_PLAYTYPE_BACK);
		//	}
		//}
		//if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_R] == false) {
		//	if (Field::GET_ENEMY_CHARACTER(CharacterID::ZKCHRSTG1WV5S_R)->is_dead() == true) {
		//		(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5S_R] = true;
		//		Field::ERASE_ENEMY_CHARACTER(CharacterID::ZKCHRSTG1WV5S_R);
		//		DxLib::PlaySoundMem(SoundHandles::ZAKOCRASH, DX_PLAYTYPE_BACK);
		//	}
		//}
		//if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5L] == false) {
		//	if (Field::GET_ENEMY_CHARACTER(CharacterID::ZKCHRSTG1WV5L)->is_dead() == true) {
		//		(*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG1WV5L] = true;
		//		Field::ERASE_ENEMY_CHARACTER(CharacterID::ZKCHRSTG1WV5L);
		//		DxLib::PlaySoundMem(SoundHandles::ZAKOCRASH, DX_PLAYTYPE_BACK);
		//	}
		//}
		break;

	case Stage1Progress::MOFU:
		if ((*Field::DEAD_FLAGS)[CharacterID::MOFU] == true) {
				PROGRESS = Stage1Progress::FINISH;
				kept_clock = DxLib::GetNowCount();
		}
		break;

	case Stage1Progress::FINISH:
		break;
	}


}