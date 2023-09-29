#include <memory>
#include <string>
#include "DxLib.h"
#include "enum.h"
#include "Scenario/Stage3.h"
#include "Field.h"
#include "Character/EnemyCharacter/BossCharacter/Toroi.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv1L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv1R.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv2L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv2R.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv3C.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv3LR.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv5TLR.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv5BLR.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv6C.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv6LR.h"

using std::wstring;
using std::make_unique;

Stage3Progress Stage3::PROGRESS;

const wstring Stage3::STAGE_NUM = L"STAGE3";
const wstring Stage3::STAGE_NAME_MAIN = L"インターネットは誰のものなのか";
const wstring Stage3::STAGE_NAME_SUB = L"～The Root Of All Disaster～";
const wstring Stage3::SONG_NAME = L"♪sumire music";

Stage3::Stage3() :
	Wave1(1),
	Wave2(1),
	Wave5(1)
{
	PROGRESS = Stage3Progress::PREPARE;
}


void Stage3::update() {
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	switch (PROGRESS) {
	case Stage3Progress::PREPARE:
		if (elapsed_time > 100) {
			Field::STAGE_NAME_DISPLAY.reset(new StageNameDisplay(STAGE_NUM, STAGE_NAME_MAIN, STAGE_NAME_SUB));
			Field::SONG_NAME_DISPLAY.reset(new SongNameDisplay(SONG_NAME));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::START;
		}
		break;
	case Stage3Progress::START:
		if (elapsed_time > 3000) {
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::WAVE1;
		}
		break;
	case Stage3Progress::WAVE1:
		if (elapsed_time>1000 && elapsed_time<=2000 && Wave1==1) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>(CharacterID::ZKCHRSTG3WV1_L1));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>(CharacterID::ZKCHRSTG3WV1_R1));
			++Wave1;
		}
		else if (elapsed_time > 2000 && elapsed_time<=3000 &&Wave1==2) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>(CharacterID::ZKCHRSTG3WV1_L2));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>(CharacterID::ZKCHRSTG3WV1_R2));
			++Wave1;
		}
		else if (elapsed_time > 3000 && elapsed_time <= 4000 && Wave1 == 3) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>(CharacterID::ZKCHRSTG3WV1_L3));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>(CharacterID::ZKCHRSTG3WV1_R3));
			++Wave1;

		}
		else if (elapsed_time > 4000 && elapsed_time <= 5000 && Wave1 == 4) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>(CharacterID::ZKCHRSTG3WV1_L4));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>(CharacterID::ZKCHRSTG3WV1_R4));
			++Wave1;
		}
		else if (elapsed_time > 5000 && elapsed_time <= 6000 && Wave1 == 5) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>(CharacterID::ZKCHRSTG3WV1_L5));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>(CharacterID::ZKCHRSTG3WV1_R5));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::WAVE2;
		}
		break;
		
	case Stage3Progress::WAVE2:
		if (elapsed_time > 1000 && elapsed_time <= 2000 && Wave2 == 1) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>(CharacterID::ZKCHRSTG3WV2_L1));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>(CharacterID::ZKCHRSTG3WV2_R1));
			++Wave2;
		}
		else if (elapsed_time > 2000 && elapsed_time <= 3000 && Wave2 == 2) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>(CharacterID::ZKCHRSTG3WV2_L2));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>(CharacterID::ZKCHRSTG3WV2_R2));
			++Wave2;
		}
		else if (elapsed_time > 3000 && elapsed_time <= 4000 && Wave2 == 3) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>(CharacterID::ZKCHRSTG3WV2_L3));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>(CharacterID::ZKCHRSTG3WV2_R3));
			++Wave2;
		}
		else if (elapsed_time > 4000 && elapsed_time <= 5000 && Wave2 == 4) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>(CharacterID::ZKCHRSTG3WV2_L4));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>(CharacterID::ZKCHRSTG3WV2_R4));
			++Wave2;
		}
		else if (elapsed_time > 5000 && elapsed_time <= 6000 && Wave2 == 5) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>(CharacterID::ZKCHRSTG3WV2_L5));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>(CharacterID::ZKCHRSTG3WV2_R5));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::WAVE3;
		}
		break;

	case Stage3Progress::WAVE3:
		if (elapsed_time > 3000) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv3C>());
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv3LR>(CharacterID::ZKCHRSTG3WV3_L));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv3LR>(CharacterID::ZKCHRSTG3WV3_R));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::WAVE4;
		}
		break;
		
	case Stage3Progress::WAVE4:
		PROGRESS = Stage3Progress::WAVE5;
		break;

	case Stage3Progress::WAVE5:
		if(elapsed_time > 3000 && elapsed_time <= 4000 && Wave5 == 1){
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L1, Stg3WAVE5TLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R1, Stg3WAVE5TLR::RIGHT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_L1, Stg3WAVE5BLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_R1, Stg3WAVE5BLR::RIGHT));
			++Wave5;
		}
		else if (elapsed_time > 4000 && elapsed_time <= 5000 && Wave5 == 2) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L2, Stg3WAVE5TLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R2, Stg3WAVE5TLR::RIGHT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_L2, Stg3WAVE5BLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_R2, Stg3WAVE5BLR::RIGHT));
			++Wave5;
		}
		else if (elapsed_time > 5000 && elapsed_time <= 6000 && Wave5 == 3) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L3, Stg3WAVE5TLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R3, Stg3WAVE5TLR::RIGHT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_L3, Stg3WAVE5BLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_R3, Stg3WAVE5BLR::RIGHT));
			++Wave5;
		}
		else if (elapsed_time > 6000 && elapsed_time <= 7000 && Wave5 == 4) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L4, Stg3WAVE5TLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R4, Stg3WAVE5TLR::RIGHT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_L4, Stg3WAVE5BLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_R4, Stg3WAVE5BLR::RIGHT));
			++Wave5;
		}
		else if (elapsed_time > 7000 && elapsed_time <= 8000 && Wave5 == 5) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L5, Stg3WAVE5TLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R5, Stg3WAVE5TLR::RIGHT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_L5, Stg3WAVE5BLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_R5, Stg3WAVE5BLR::RIGHT));
			++Wave5;
		}
		else if (elapsed_time > 8000 && elapsed_time <= 9000 && Wave5 == 6) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L5, Stg3WAVE5TLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R5, Stg3WAVE5TLR::RIGHT));
			++Wave5;
		}
		else if (elapsed_time > 9000 && elapsed_time <= 10000 && Wave5 == 7) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L5, Stg3WAVE5TLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R5, Stg3WAVE5TLR::RIGHT));
			++Wave5;
		}
		else if (elapsed_time > 10000 && elapsed_time <= 11000 && Wave5 == 8) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L5, Stg3WAVE5TLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R5, Stg3WAVE5TLR::RIGHT));
			++Wave5;
		}
		else if (elapsed_time > 11000 && elapsed_time <= 12000 && Wave5 == 9) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L5, Stg3WAVE5TLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R5, Stg3WAVE5TLR::RIGHT));
			++Wave5;
		}
		else if (elapsed_time > 12000 && elapsed_time <= 13000 && Wave5 == 10) {
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L5, Stg3WAVE5TLR::LEFT));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R5, Stg3WAVE5TLR::RIGHT));
			++Wave5;
		}


		else if (elapsed_time > 40000) {
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::WAVE6;
		}
		break;

	case Stage3Progress::WAVE6:
		if (true) {
			if (elapsed_time > 3000) {
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6C>());
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6LR>(CharacterID::ZKCHRSTG3WV6_L));
				Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6LR>(CharacterID::ZKCHRSTG3WV6_R));
				kept_clock = DxLib::GetNowCount();
				PROGRESS = Stage3Progress::BOSS;
			}
		}
		else {
			Field::ENEMY_CHARACTERS->push_back(make_unique<Toroi>());
			PROGRESS = Stage3Progress::BOSS;
		}
		break;

	case Stage3Progress::BOSS:
		//kept_clock = DxLib::GetNowCount();
		break;
	}
}