#include <memory>
#include <numbers>
#include <string>
#include <deque>
#include <tuple>
#include "DxLib.h"
#include "enum.h"
#include "GameConductor.h"
#include "Scenario/Stage2.h"
#include "Field.h"
#include "Character/EnemyCharacter/BossCharacter/Neon.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv4.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv5L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv5R.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv6L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv6R.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv7L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv7R.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv8L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2Wv8R.h"
#include "SoundHandles.h"


using std::wstring;
using std::deque;
using std::make_tuple;
using std::make_unique;
using std::numbers::pi;

Stage2Progress Stage2::PROGRESS;

const wstring Stage2::STAGE_NUM = L"STAGE2";
const wstring Stage2::STAGE_NAME_MAIN = L"海底に響く遠雷";
const wstring Stage2::STAGE_NAME_SUB = L"~Zip-Zap~";
const wstring Stage2::SONG_NAME = L"♪ gamic";

const deque<tuple<wstring, wstring, PortraitID>> Stage2::BEFORE_BOSS_WORDS = {
	make_tuple(L"ｶﾁｬｶﾁｬｶﾁｬｶﾁｬ...（コントローラー連打）", L"", PortraitID::NEON),
	make_tuple(L"あの～...こんにちは～", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"あ？誰だぁ？", L"？？？", PortraitID::NEON),
	make_tuple(L"私は“いちご”って言います。", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"俺は雷ねおん。しがないゲーマーさ。", L"ねおん", PortraitID::NEON),
	make_tuple(L"はぁ～あ、今あんたが声かけたからやられたんだけど\nなぁ～", L"ねおん", PortraitID::NEON),
	make_tuple(L"（ただの言い訳じゃない？）", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"あ～腹の虫がおさまらねぇ", L"ねおん", PortraitID::NEON),
	make_tuple(L"勝負しようぜ", L"ねおん", PortraitID::NEON),
	make_tuple(L"（とりあえず倒せばいっか）", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR)
};


const deque<tuple<wstring, wstring, PortraitID>> Stage2::AFTER_BOSS_WORDS = {
	make_tuple(L"あそこをもう少し右にしてれば...", L"ねおん", PortraitID::NEON),
	make_tuple(L"そんなこと言っても力が無きゃ意味ないよ", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"（あれ、もしかしてこいつ...）", L"ねおん", PortraitID::NEON),
	make_tuple(L"そういえば、あんたを連れてくるように言われてた\nな...", L"ねおん", PortraitID::NEON),
	make_tuple(L"え、どうして！？", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"まぁ、大人しくついてきな。", L"ねおん", PortraitID::NEON),
};


const unsigned int Stage2::WAVE4_BASIC_ELAPSED_TIME = 3000;
const unsigned int Stage2::WAVE5_BASIC_ELAPSED_TIME = 2000;
const unsigned int Stage2::WAVE6_BASIC_ELAPSED_TIME = 2000;
const unsigned int Stage2::WAVE7_BASIC_ELAPSED_TIME = 600;
const unsigned int Stage2::WAVE8_GENERATED_BASIC_ELAPSED_TIME = 600;
const unsigned int Stage2::WAVE8_LOWER_BASIC_ELAPSED_TIME = 1000;
const unsigned int Stage2::BOSS_BASIC_ELAPSED_TIME = 5000;

const unsigned int Stage2::WAVE3_GENERATED_TO_ENDED_TIME = 0;
const unsigned int Stage2::WAVE4_GENERATED_TO_ENDED_TIME = 18000;
const unsigned int Stage2::WAVE5_GENERATED_TO_ENDED_TIME = 15000;
const unsigned int Stage2::WAVE6_GENERATED_TO_ENDED_TIME = 7000;
const unsigned int Stage2::WAVE7_GENERATED_TO_ENDED_TIME = 33000;
const unsigned int Stage2::WAVE8_GENERATED_TO_LOWER_TIME = 5000;
const unsigned int Stage2::WAVE8_LOWER_TO_ENDED_TIME = 20000;



Stage2::Stage2() :
	wave6count(1),
	wave7count(1),
	wave8_generated_count(1),
	wave8_go_count(1),
	wave4_elapsed_time(Stage2::WAVE4_BASIC_ELAPSED_TIME + Stage2::WAVE3_GENERATED_TO_ENDED_TIME),
	wave5_elapsed_time(Stage2::WAVE5_BASIC_ELAPSED_TIME + Stage2::WAVE4_GENERATED_TO_ENDED_TIME),
	boss_elapsed_time(Stage2::BOSS_BASIC_ELAPSED_TIME)
{
	PROGRESS = Stage2Progress::PREPARE;
	for (int i = 1; i <= 5 + 1; ++i) {
		wave6_elapsed_time[i] = WAVE5_GENERATED_TO_ENDED_TIME + WAVE6_BASIC_ELAPSED_TIME * i;
	}
	for (int i = 1; i <= 5 + 1; ++i) {
		wave7_elapsed_time[i] = WAVE6_GENERATED_TO_ENDED_TIME + WAVE7_BASIC_ELAPSED_TIME * i;
	}
	for (int i = 1; i <= 8 + 1; ++i) {
		wave8_generated_elapsed_time[i] = WAVE7_GENERATED_TO_ENDED_TIME + WAVE8_GENERATED_BASIC_ELAPSED_TIME * i;
	}
	for (int i = 1; i <= 4 + 1; ++i) {
		wave8_lower_elapsed_time[i] = WAVE7_GENERATED_TO_ENDED_TIME + WAVE8_GENERATED_BASIC_ELAPSED_TIME * 9 + 10000 + WAVE8_LOWER_BASIC_ELAPSED_TIME * i;
	}
	GameConductor::ENABLE_SURVIVAL_BONUS();
}

void Stage2::update() {
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	switch (PROGRESS) {
	case Stage2Progress::PREPARE:
		if (elapsed_time > 100) {
			DxLib::PlaySoundMem(SoundHandles::STAGE2BGM, DX_PLAYTYPE_LOOP);
			Field::STAGE_NAME_DISPLAY.reset(new StageNameDisplay(STAGE_NUM, STAGE_NAME_MAIN, STAGE_NAME_SUB));
			Field::SONG_NAME_DISPLAY.reset(new SongNameDisplay(STAGE_NUM, SONG_NAME));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage2Progress::START;
		}
		break;
	case Stage2Progress::START:
		if (elapsed_time > 3000) {
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage2Progress::WAVE1;
		}
		break;
	case Stage2Progress::WAVE1:
		kept_clock = DxLib::GetNowCount();
		PROGRESS = Stage2Progress::WAVE2;
		break;

	case Stage2Progress::WAVE2:
		kept_clock = DxLib::GetNowCount();
		PROGRESS = Stage2Progress::WAVE3;
		break;

	case Stage2Progress::WAVE3:
		kept_clock = DxLib::GetNowCount();
		PROGRESS = Stage2Progress::WAVE4;
		break;

	case Stage2Progress::WAVE4:
		if (elapsed_time > wave4_elapsed_time) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv4>(
				CharacterID::ZKCHRSTG2WV4_L,
				0.0,
				742.0,
				250,
				-1.0 / 12.0 * pi,
				15,
				20)
			);
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv4>(
				CharacterID::ZKCHRSTG2WV4_R,
				620.0,
				742.0,
				250,
				13.0 / 12.0 * pi,
				15,
				20)
			);
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage2Progress::WAVE5;
		}
		break;

	case Stage2Progress::WAVE5:
		if (elapsed_time > wave5_elapsed_time) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv5L>());
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv5R>());
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage2Progress::WAVE6;
		}
		break;

	case Stage2Progress::WAVE6:
		if (elapsed_time > wave6_elapsed_time[1] && elapsed_time <= wave6_elapsed_time[2] && wave6count == 1) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L1));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R1));
			++wave6count;
		}
		else if (elapsed_time > wave6_elapsed_time[2] && elapsed_time <= wave6_elapsed_time[3] && wave6count == 2) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L2));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R2));
			++wave6count;
		}
		else if (elapsed_time > wave6_elapsed_time[3] && elapsed_time <= wave6_elapsed_time[4] && wave6count == 3) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L3));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R3));
			++wave6count;
		}
		else if (elapsed_time > wave6_elapsed_time[4] && elapsed_time <= wave6_elapsed_time[5] && wave6count == 4) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L4));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R4));
			++wave6count;
		}
		else if (elapsed_time > wave6_elapsed_time[5] && elapsed_time <= wave6_elapsed_time[5+1] && wave6count == 5) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6L>(CharacterID::ZKCHRSTG2WV6_L5));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv6R>(CharacterID::ZKCHRSTG2WV6_R5));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage2Progress::WAVE7;
		}
		break;
		

	case Stage2Progress::WAVE7:
		if (elapsed_time > wave7_elapsed_time[1] && elapsed_time <= wave7_elapsed_time[2] && wave7count == 1) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7L>(CharacterID::ZKCHRSTG2WV7_L1));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7R>(CharacterID::ZKCHRSTG2WV7_R1));
			++wave7count;
		}
		else if (elapsed_time > wave7_elapsed_time[2] && elapsed_time <= wave7_elapsed_time[3] && wave7count == 2) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7L>(CharacterID::ZKCHRSTG2WV7_L2));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7R>(CharacterID::ZKCHRSTG2WV7_R2));
			++wave7count;
		}
		else if (elapsed_time > wave7_elapsed_time[3] && elapsed_time <= wave7_elapsed_time[4] && wave7count == 3) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7L>(CharacterID::ZKCHRSTG2WV7_L3));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7R>(CharacterID::ZKCHRSTG2WV7_R3));
			++wave7count;
		}
		else if (elapsed_time > wave7_elapsed_time[4] && elapsed_time <= wave7_elapsed_time[5] && wave7count == 4) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7L>(CharacterID::ZKCHRSTG2WV7_L4));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7R>(CharacterID::ZKCHRSTG2WV7_R4));
			++wave7count;
		}
		else if (elapsed_time > wave7_elapsed_time[5] && elapsed_time <= wave7_elapsed_time[5+1] && wave7count == 5) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7L>(CharacterID::ZKCHRSTG2WV7_L5));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv7R>(CharacterID::ZKCHRSTG2WV7_R5));
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage2Progress::WAVE8;
		}
		break;

	case Stage2Progress::WAVE8:

		if (elapsed_time > wave8_generated_elapsed_time[1] && elapsed_time <= wave8_generated_elapsed_time[2] && wave8_generated_count == 1) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L1, wave8_generated_count, 200));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R1, wave8_generated_count, 200));
			++wave8_generated_count;
		}
		else if (elapsed_time > wave8_generated_elapsed_time[2] && elapsed_time <= wave8_generated_elapsed_time[3] && wave8_generated_count == 2) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L2, wave8_generated_count, 200));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R2, wave8_generated_count, 200));
			++wave8_generated_count;
		}
		else if (elapsed_time > wave8_generated_elapsed_time[3] && elapsed_time <= wave8_generated_elapsed_time[4] && wave8_generated_count == 3) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L3, wave8_generated_count, 200));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R3, wave8_generated_count, 200));
			++wave8_generated_count;
		}
		else if (elapsed_time > wave8_generated_elapsed_time[4] && elapsed_time <= wave8_generated_elapsed_time[5] && wave8_generated_count == 4) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L4, wave8_generated_count, 200));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R4, wave8_generated_count, 200));
			++wave8_generated_count;
		}
		else if (elapsed_time > wave8_generated_elapsed_time[5] && elapsed_time <= wave8_generated_elapsed_time[6] && wave8_generated_count == 5) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L5, wave8_generated_count, 200));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R5, wave8_generated_count, 200));
			++wave8_generated_count;
		}
		else if (elapsed_time > wave8_generated_elapsed_time[6] && elapsed_time <= wave8_generated_elapsed_time[7] && wave8_generated_count == 6) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L6, wave8_generated_count, 200));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R6, wave8_generated_count, 200));
			++wave8_generated_count;
		}
		else if (elapsed_time > wave8_generated_elapsed_time[7] && elapsed_time <= wave8_generated_elapsed_time[8] && wave8_generated_count == 7) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L7, wave8_generated_count, 200));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R7, wave8_generated_count, 200));
			++wave8_generated_count;
		}
		else if (elapsed_time > wave8_generated_elapsed_time[8] && elapsed_time <= wave8_generated_elapsed_time[8+1] && wave8_generated_count == 8) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8L>(CharacterID::ZKCHRSTG2WV8_L8, wave8_generated_count, 200));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg2Wv8R>(CharacterID::ZKCHRSTG2WV8_R8, wave8_generated_count, 200));
			++wave8_generated_count;
		}

		// 落下のタイミング調整
		if (elapsed_time > wave8_lower_elapsed_time[1] && elapsed_time <= wave8_lower_elapsed_time[2] && wave8_go_count == 1) {
			ZkChrStg2Wv8L::WAIT_FLAG_L18 = Stg2WAVE8WaitFlag::GO;
			ZkChrStg2Wv8R::WAIT_FLAG_R18 = Stg2WAVE8WaitFlag::GO;
			++wave8_go_count;
		}
		else if (elapsed_time > wave8_lower_elapsed_time[2] && elapsed_time <= wave8_lower_elapsed_time[3] && wave8_go_count == 2) {
			ZkChrStg2Wv8L::WAIT_FLAG_L27 = Stg2WAVE8WaitFlag::GO;
			ZkChrStg2Wv8R::WAIT_FLAG_R27 = Stg2WAVE8WaitFlag::GO;
			++wave8_go_count;
		}
		else if (elapsed_time > wave8_lower_elapsed_time[3] && elapsed_time <= wave8_lower_elapsed_time[4] && wave8_go_count == 3) {
			ZkChrStg2Wv8L::WAIT_FLAG_L36 = Stg2WAVE8WaitFlag::GO;
			ZkChrStg2Wv8R::WAIT_FLAG_R36 = Stg2WAVE8WaitFlag::GO;
			++wave8_go_count;
		}
		else if (elapsed_time > wave8_lower_elapsed_time[4] && elapsed_time <= wave8_lower_elapsed_time[4+1] && wave8_go_count == 4) {
			ZkChrStg2Wv8L::WAIT_FLAG_L45 = Stg2WAVE8WaitFlag::GO;
			ZkChrStg2Wv8R::WAIT_FLAG_R45 = Stg2WAVE8WaitFlag::GO;
			++wave8_go_count;
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage2Progress::BOSS;
		}
		break;

	case Stage2Progress::BOSS:
	{
		if (elapsed_time > boss_elapsed_time && boss_advented_flag == false) {
			Field::BOSS_CHARACTERS->push_back(make_unique<Neon>());
			boss_advented_flag = true;
		}

		if (boss_advented_flag == true) {
			for (const auto& tuple : BEFORE_BOSS_WORDS) {
				GameConductor::NARRATIVE_POPS.push_back(make_unique<NarrativePop>(tuple));
			}
			PROGRESS = Stage2Progress::EPILOGUE;
		}
		break;
	}

	case Stage2Progress::EPILOGUE:
		if ((*Field::DEAD_FLAGS)[CharacterID::NEON] == true && boss_crushed_flag == false) {
			boss_crushed_flag = true;
			Field::ENEMY_BULLETS->clear();
			Field::ENEMY_LASERS->clear();
			Field::ZAKO_CHARACTERS->clear();
			for (const auto& tuple : AFTER_BOSS_WORDS) {
				GameConductor::NARRATIVE_POPS.push_back(make_unique<NarrativePop>(tuple));
			}
		}
		if (boss_crushed_flag == true && GameConductor::NARRATIVE_POPS.empty() == true) {
			PROGRESS = Stage2Progress::END;
		}
		break;

	case Stage2Progress::END:
		Field::BOSS_CHARACTERS->clear();
		GameConductor::STAGE2_CLEAR_FLAG = true;
		DxLib::StopSoundMem(SoundHandles::STAGE2BGM);
		break;

	}
}