﻿#include <memory>
#include <numbers>
#include <cmath>
#include <string>
#include <tuple>
#include <deque>
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
#include "Offensive/Laser/CartesianLaser/CartesianLaser.h"
#include "Offensive/Bullet/StraightShot/ReflectShot/ReflectShot.h"
#include "Offensive/Bullet/StraightShot/ReflectShot/DVDShot.h"

using std::wstring;
using std::tuple;
using std::make_tuple;
using std::deque;
using std::make_unique;
using std::unique_ptr;
using std::numbers::pi;
using std::atan2;

Stage1Progress Stage1::PROGRESS;

const wstring Stage1::STAGE_NUM = L"STAGE1";
const wstring Stage1::STAGE_NAME_MAIN = L"煌めく海の月";
const wstring Stage1::STAGE_NAME_SUB = L"~nano data.cpp~";
const wstring Stage1::SONG_NAME = L"♪ Jelly Carnival";


deque<tuple<wstring, wstring, PortraitID>> Stage1::BEFORE_BOSS_WORDS = {
	make_tuple(L"さて、だいぶ進んできたけど...", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"あれ！？お客さんなの！？", L"？？？", PortraitID::MOFU),
	make_tuple(L"私は\"1号\"だよ。\"いちごちゃん\"って呼んでね。", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"私は海月もふ！もふって呼んでなの～", L"もふ", PortraitID::MOFU),
	make_tuple(L"よろしくね。ところでもふは何をしていたの？", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"最近私達の食料(データ)が汚染されちゃって困ってた\nところなの～", L"もふ", PortraitID::MOFU),
	make_tuple(L"ポリエステル破れちゃったのかな？", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"突然、データが毒になっちゃったの...", L"もふ", PortraitID::MOFU),
	make_tuple(L"クラゲに毒が効くとはね…", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"もしかしてあなたが犯人！？許さないの～！！！", L"もふ", PortraitID::MOFU)
};


deque<tuple<wstring, wstring, PortraitID>> Stage1::AFTER_BOSS_WORDS = {
	make_tuple(L"やーらーれーたーなのー", L"もふ", PortraitID::MOFU),
	make_tuple(L"(txtファイルがポップアウトする)", L"", PortraitID::TEXTFILE),
	make_tuple(L"おや、これはログかな？\n…犯人は...例のウイルスじゃないか！", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"え、じゃあ\"いちごちゃん\"は本当に犯人じゃない？\nごめんなさいなの～", L"もふ", PortraitID::MOFU),
	make_tuple(L"これに懲りたら早とちりしちゃダメだよ", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"反省反省なの...", L"もふ", PortraitID::MOFU),
	make_tuple(L"じゃあ私はウイルスを倒してくるね。", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"また来てなの～～！！！！", L"もふ", PortraitID::MOFU),
	make_tuple(L"覚えておくよ、もふ", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR)
};


Stage1::Stage1() :
	test_arg(0),
	test_updated_clock(DxLib::GetNowHiPerformanceCount())
{
	PROGRESS = Stage1Progress::PREPARE;
}


void Stage1::update() {

	int elapsed_time = DxLib::GetNowCount() - kept_clock;

	switch (PROGRESS) {
	case Stage1Progress::NARRATIVE_POP_TEST_BEGIN:
		break;

	case Stage1Progress::NARRATIVE_POP_TEST_END:
		break;

	case Stage1Progress::LASER_TEST_BEGIN:
		if (elapsed_time > 1000) {
			carte_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[carte_id] = make_unique<CartesianLaser>(
				InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_Y / 2.0,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0 + 100,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_Y / 2.0 + 300,
				150.0,
				100,
				true,
				SkinID::LASER_TEST
			);
			polar_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[polar_id] = make_unique<PolarLaser>(
				InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0 - 100,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_Y / 2.0 - 100,
				0.0,
				250,
				10,
				1,
				true,
				SkinID::LASER_TEST
			);
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::LASER_TEST_END;
		}
		break;

	case Stage1Progress::LASER_TEST_END:
	{
		LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - test_updated_clock;
		test_arg += update_delta_time * 2.0 * pi / 1000 / 1000;
		double begin_pos_x = InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0 + 200;
		double begin_pos_y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y / 2.0 + 200;
		double r = 200.0;
		double test_x = begin_pos_x + r * cos(test_arg);
		double test_y = begin_pos_y + r * sin(test_arg);

		dynamic_cast<CartesianLaser*>((*Field::ENEMY_LASERS)[carte_id].get())->set_end_pos(test_x, test_y);
		dynamic_cast<PolarLaser*>((*Field::ENEMY_LASERS)[polar_id].get())->set_arg(test_arg);
		test_updated_clock = DxLib::GetNowHiPerformanceCount();

		break;
	}
	case Stage1Progress::REFLECT_SHOT_TEST_BEGIN:
		if (elapsed_time > 1000) {
			(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<DVDShot>(
				Field::PIXEL_SIZE_X / 2,
				Field::PIXEL_SIZE_Y / 2,
				1.0 / 6.0 * pi
			);
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::REFLECT_SHOT_TEST_END;
		}
		break;
		
	case Stage1Progress::REFLECT_SHOT_TEST_END:
		break;

	case Stage1Progress::PREPARE:
		if (elapsed_time > 100) {
			DxLib::PlaySoundMem(SoundHandles::STAGE1BGM, DX_PLAYTYPE_LOOP);
			Field::STAGE_NAME_DISPLAY.reset(new StageNameDisplay(STAGE_NUM, STAGE_NAME_MAIN, STAGE_NAME_SUB));
			Field::SONG_NAME_DISPLAY.reset(new SongNameDisplay(STAGE_NUM, SONG_NAME));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::START;
		}
		break;
	case Stage1Progress::START:
		if (elapsed_time > 5000) {//5
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_L1, -10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_LEFT_1;
		}
		break;

	case Stage1Progress::A_LEFT_1:
		if (elapsed_time > 2000) {//7
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_L2, -10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_LEFT_2;
		}
		break;

	case Stage1Progress::A_LEFT_2:
		if (elapsed_time > 2000) {//9
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_L3, -10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_LEFT_3;
		}
		break;

	case Stage1Progress::A_LEFT_3:
		if (elapsed_time > 4000) {//13
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_R1, 630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_RIGHT_1;
		}
		break;

	case Stage1Progress::A_RIGHT_1:
		if (elapsed_time > 2000) {//15
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_R2, 630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_RIGHT_2;
		}
		break;

	case Stage1Progress::A_RIGHT_2:
		if (elapsed_time > 2000) {//17
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(CharacterID::ZKCHRSTG1WV1_R3, 630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::A_RIGHT_3;
		}
		break;

	case Stage1Progress::A_RIGHT_3:
		if (elapsed_time > 5000) {//22
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(CharacterID::ZKCHRSTG1WV2_1U, -10, 650, 0, 65, -(1.0 / 6.0) * pi));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(CharacterID::ZKCHRSTG1WV2_1L, 630, 400, pi, 65, 1.0 / 6.0 * pi));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::B1;
		}
		break;

	case Stage1Progress::B1:
		if (elapsed_time > 8000) {//30
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(CharacterID::ZKCHRSTG1WV2_2U, -10, 650, 0, 65, -(1.0 / 6.0) * pi));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(CharacterID::ZKCHRSTG1WV2_2L, 630, 400, pi, 65, 1.0 / 6.0 * pi));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::B2;
		}
		break;

	case Stage1Progress::B2:
		if (elapsed_time > 10000) {//40
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(CharacterID::ZKCHRSTG1WV3S_1, 80, 540 + 250));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(CharacterID::ZKCHRSTG1WV3S_2, 230, 610 + 250));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(CharacterID::ZKCHRSTG1WV3S_3, 390, 610 + 250));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(CharacterID::ZKCHRSTG1WV3S_4, 540, 540 + 250));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3L>(CharacterID::ZKCHRSTG1WV3L_1, 155, 575 + 250, (1.0 / 6.0) * pi));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3L>(CharacterID::ZKCHRSTG1WV3L_2, 465, 575 + 250, -(1.0 / 6.0) * pi));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::C;
		}
		break;

	case Stage1Progress::C:
		if (elapsed_time > 18000) {//58
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(CharacterID::ZKCHRSTG1WV4_A, 80, 640 + 150));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::D1;
		}
		break;

	case Stage1Progress::D1:
		if (elapsed_time > 1000) {//59
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(CharacterID::ZKCHRSTG1WV4_B, 230, 640 + 150));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::D2;
		}
		break;

	case Stage1Progress::D2:
		if (elapsed_time > 1000) {//60
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(CharacterID::ZKCHRSTG1WV4_C, 390, 640 + 150));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::D3;
		}
		break;

	case Stage1Progress::D3:
		if (elapsed_time > 1000) {//61
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(CharacterID::ZKCHRSTG1WV4_D, 540, 640 + 150));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage1Progress::D4;
		}
		break;

	case Stage1Progress::D4:
		if (elapsed_time > 10000) {//71
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv5S>(CharacterID::ZKCHRSTG1WV5S_L, 135, 480 + 150, 1.0 / 8.0 * pi));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv5S>(CharacterID::ZKCHRSTG1WV5S_R, 485, 480 + 150, -(1.0 / 8.0) * pi));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1Wv5L>(CharacterID::ZKCHRSTG1WV5L, 310, 550 + 150));
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
		if (boss_advented_flag == false && mofu_advent_ready_flag == true) {
			Field::BOSS_CHARACTERS->push_back(make_unique<Mofu>());
			boss_advented_clock = DxLib::GetNowCount();
			boss_advented_flag = true;
		}

		int boss_advent_delta_time = DxLib::GetNowCount() - boss_advented_clock;
		if (boss_advented_flag == true && boss_advent_delta_time > 3000) {
			Field::MY_CHARACTER->reset_position();	// 自機位置リセット
			for (const auto& tuple : BEFORE_BOSS_WORDS) {
				GameConductor::NARRATIVE_POPS.push_back(make_unique<NarrativePop>(tuple));
			}
			PROGRESS = Stage1Progress::MOFU;
		}
	}
	break;

	case Stage1Progress::MOFU:
		if ((*Field::DEAD_FLAGS)[CharacterID::MOFU] == true && boss_crushed_flag == false) {
			boss_crushed_flag = true;
			Field::ENEMY_BULLETS->clear();
			Field::ENEMY_LASERS->clear();
			Field::ZAKO_CHARACTERS->clear();
			for (const auto& tuple : AFTER_BOSS_WORDS) {
				GameConductor::NARRATIVE_POPS.push_back(make_unique<NarrativePop>(tuple));
			}
		}
		if (boss_crushed_flag == true && GameConductor::NARRATIVE_POPS.empty() == true) {
			PROGRESS = Stage1Progress::FINISH;
		}
		break;

	case Stage1Progress::FINISH:
		Field::BOSS_CHARACTERS->clear();
		GameConductor::STAGE1_CLEAR_FLAG = true;
		DxLib::StopSoundMem(SoundHandles::STAGE1BGM);
		break;
	}

}