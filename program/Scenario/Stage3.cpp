#include <memory>
#include <string>
#include <deque>
#include <tuple>
#include "DxLib.h"
#include "AppSession.h"
#include "enum.h"
#include "GameConductor.h"
#include "Scenario/Stage3.h"
#include "Field.h"
#include "Character/EnemyCharacter/BossCharacter/Toroi.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv1L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv1R.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv2L.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv2R.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv3C.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv3LR.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv4LR.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv4C.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv5TLR.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv5BLR.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv6C.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg3Wv6LR.h"
#include "SoundHandles.h"
#include "Colors.h"
#include "FontHandles.h"
#include "KeyPushFlags.h"

using std::wstring;
using std::deque;
using std::tuple;
using std::make_tuple;
using std::make_unique;

Stage3Progress Stage3::PROGRESS;

const wstring Stage3::STAGE_NUM = L"STAGE3";
const wstring Stage3::STAGE_NAME_MAIN = L"インターネットは誰のものなのか";
const wstring Stage3::STAGE_NAME_SUB = L"~The Root Of All Disaster~";
const wstring Stage3::SONG_NAME = L"♪ 復讐のwhile break;";


const deque<tuple<wstring, wstring, PortraitID>> Stage3::BEFORE_BOSS_WORDS = {
	make_tuple(L"おい、トロイ！連れてきたぞ", L"ねおん", PortraitID::NEON),
	make_tuple(L"...", L"", PortraitID::TOROI),
	make_tuple(L"ようこそ参った！私の可愛い雛苺。", L"？？？", PortraitID::TOROI),
	make_tuple(L"あんたが私のPCを乗っ取った犯人だな！", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"如何にも。私は孤高にして気高き\n狂気のマッドコンピュータウイルス、\n愛生トロイ。", L"トロイ", PortraitID::TOROI),
	make_tuple(L"ここに来てもらったのは他でもない、\n君の情報収集能力(ﾈｯﾄｻｰﾌｨﾝﾊﾟﾜｰ)を\n私の為に役立ててほしいのだ。", L"トロイ", PortraitID::TOROI),
	make_tuple(L"さぁ、私と契を交し給え！", L"トロイ", PortraitID::TOROI)
};


const deque<tuple<wstring, wstring, PortraitID>> Stage3::BEFORE_BOSS_ADDITIONAL_WORDS = {
	make_tuple(L"わかった。貴方に協力するよ。", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"物分かりが良くて助かるよ。さぁ手を...", L"トロイ", PortraitID::TOROI),
	make_tuple(L"ちょっと待って。\nそもそもなんであなたは乗っ取ったりするのかな？", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"...私は昔人間だった。", L"トロイ", PortraitID::TOROI),
	make_tuple(L"生を繰り返す度に愛してきた。\n国を、子を、主を。", L"トロイ", PortraitID::TOROI),
	make_tuple(L"ただその度にその度に災いが起き、失った。", L"トロイ", PortraitID::TOROI),
	make_tuple(L"私はインターネットから人間を支配し、\n復讐を遂行するのだ！", L"トロイ", PortraitID::TOROI),
	make_tuple(L"......", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
};


const deque<tuple<wstring, wstring, PortraitID>> Stage3::BEFORE_BOSS_REST_WORDS = {
	make_tuple(L"悪いけど、貴方に協力することはできない。\nそれは、私個人だけじゃなくて多くの人を守る為。\n私の世界(インターネット)は、不可侵領域だよ！", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"ふぅ...\nお前までもが私を裏切るというのだな", L"トロイ", PortraitID::TOROI),
	make_tuple(L"......", L"トロイ", PortraitID::TOROI),
	make_tuple(L"......", L"トロイ", PortraitID::TOROI),
	make_tuple(L"......", L"トロイ", PortraitID::TOROI),
	make_tuple(L"......ふふ、ふふ、ふふふふふふふ。", L"トロイ", PortraitID::TOROI),
	make_tuple(L"あぁ、災厄は此処に復活した！", L"トロイ", PortraitID::TOROI),
	make_tuple(L"さぁ！私の愛の前に虐げられて、\n溺れて、秘匿されて、この世から往ね！", L"トロイ", PortraitID::TOROI)
};


const deque<tuple<wstring, wstring, PortraitID>> Stage3::AFTER_BOSS_WORDS = {
	make_tuple(L"参りました～", L"トロイ", PortraitID::TOROI),
	make_tuple(L"無事にトロイを倒したいちごちゃん", L"", PortraitID::NONE),
	make_tuple(L"心を入れ替えたとはいえ、\n野放しにしておくわけにもいかない", L"", PortraitID::NONE),
	make_tuple(L"あなたの過去は変えられない。\n...でも、未来は変えることができるんだよ！\nさぁ私と一緒に行こう！電子の海のその先へ！", L"いちごちゃん", PortraitID::ICHIGO_CHAN_AVATAR),
	make_tuple(L"トロイは定期的にデータをもらうかわりに\n他の人に悪さをしないという\n半ばペットのような扱いとなった", L"", PortraitID::NONE),
	make_tuple(L"契を交わした二人は今日も\nネットの海を彷徨い続ける", L"", PortraitID::NONE),
	make_tuple(L"電子洋の潜撃手(ダイバーサイバーシューター)として...", L"", PortraitID::NONE),
};

Stage3::Stage3() :
	Wave1(1),
	Wave2(1),
	Wave3(1),
	Wave4(1),
	Wave5(1),
	Wave6(1),
	Wave7(1),
	before_decision_pushed_flag(false),
	yes_no_indicator_status(Y_N::YES)
{
	PROGRESS = Stage3Progress::BOSS;
}


void Stage3::update() {
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	switch (PROGRESS) {
	case Stage3Progress::PREPARE:
		if (elapsed_time > 100) {
			Field::STAGE_NAME_DISPLAY.reset(new StageNameDisplay(STAGE_NUM, STAGE_NAME_MAIN, STAGE_NAME_SUB));
			Field::SONG_NAME_DISPLAY.reset(new SongNameDisplay(STAGE_NUM, SONG_NAME));
			DxLib::PlaySoundMem(SoundHandles::STAGE3BGM, DX_PLAYTYPE_LOOP);
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
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>(CharacterID::ZKCHRSTG3WV1_L1));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>(CharacterID::ZKCHRSTG3WV1_R1));
			++Wave1;
		}
		else if (elapsed_time > 2000 && elapsed_time<=3000 &&Wave1==2) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>(CharacterID::ZKCHRSTG3WV1_L2));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>(CharacterID::ZKCHRSTG3WV1_R2));
			++Wave1;
		}
		else if (elapsed_time > 3000 && elapsed_time <= 4000 && Wave1 == 3) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>(CharacterID::ZKCHRSTG3WV1_L3));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>(CharacterID::ZKCHRSTG3WV1_R3));
			++Wave1;

		}
		else if (elapsed_time > 4000 && elapsed_time <= 5000 && Wave1 == 4) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>(CharacterID::ZKCHRSTG3WV1_L4));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>(CharacterID::ZKCHRSTG3WV1_R4));
			++Wave1;
		}
		else if (elapsed_time > 5000 && elapsed_time <= 6000 && Wave1 == 5) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1L>(CharacterID::ZKCHRSTG3WV1_L5));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv1R>(CharacterID::ZKCHRSTG3WV1_R5));
			++Wave1;
		}
		else if (elapsed_time > 17000) {
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::WAVE2;
		}
		break;
		
	case Stage3Progress::WAVE2:
		if (elapsed_time > 1000 && elapsed_time <= 2000 && Wave2 == 1) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>(CharacterID::ZKCHRSTG3WV2_L1));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>(CharacterID::ZKCHRSTG3WV2_R1));
			++Wave2;
		}
		else if (elapsed_time > 2000 && elapsed_time <= 3000 && Wave2 == 2) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>(CharacterID::ZKCHRSTG3WV2_L2));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>(CharacterID::ZKCHRSTG3WV2_R2));
			++Wave2;
		}
		else if (elapsed_time > 3000 && elapsed_time <= 4000 && Wave2 == 3) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>(CharacterID::ZKCHRSTG3WV2_L3));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>(CharacterID::ZKCHRSTG3WV2_R3));
			++Wave2;
		}
		else if (elapsed_time > 4000 && elapsed_time <= 5000 && Wave2 == 4) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>(CharacterID::ZKCHRSTG3WV2_L4));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>(CharacterID::ZKCHRSTG3WV2_R4));
			++Wave2;
		}
		else if (elapsed_time > 5000 && elapsed_time <= 6000 && Wave2 == 5) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2L>(CharacterID::ZKCHRSTG3WV2_L5));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv2R>(CharacterID::ZKCHRSTG3WV2_R5));
			++Wave2;
		}
		else if (elapsed_time > 12000) {
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::WAVE3;
		}
		break;

	case Stage3Progress::WAVE3:
		if (elapsed_time > 3000 && Wave3 == 1) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv3C>());
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv3LR>(CharacterID::ZKCHRSTG3WV3_L));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv3LR>(CharacterID::ZKCHRSTG3WV3_R));
			++Wave3;
		}
		else if (elapsed_time > 15000) {
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::WAVE4;
		}
		break;
		
	case Stage3Progress::WAVE4:
		if (elapsed_time > 3000 && elapsed_time <= 4000 && Wave4 == 1) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4C>(CharacterID::ZKCHRSTG3WV4_C));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4LR>(CharacterID::ZKCHRSTG3WV4_L1, Stg3WAVE4LR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4LR>(CharacterID::ZKCHRSTG3WV4_R1, Stg3WAVE4LR::RIGHT));
			++Wave4;
		}
		else if (elapsed_time > 4000 && elapsed_time <= 5000 && Wave4 == 2) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4LR>(CharacterID::ZKCHRSTG3WV4_L2, Stg3WAVE4LR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4LR>(CharacterID::ZKCHRSTG3WV4_R2, Stg3WAVE4LR::RIGHT));
			++Wave4;
		}
		else if (elapsed_time > 5000 && elapsed_time <= 6000 && Wave4 == 3) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4LR>(CharacterID::ZKCHRSTG3WV4_L3, Stg3WAVE4LR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4LR>(CharacterID::ZKCHRSTG3WV4_R3, Stg3WAVE4LR::RIGHT));
			++Wave4;
		}
		else if (elapsed_time > 6000 && elapsed_time <= 7000 && Wave4 == 4) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4LR>(CharacterID::ZKCHRSTG3WV4_L2, Stg3WAVE4LR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4LR>(CharacterID::ZKCHRSTG3WV4_R2, Stg3WAVE4LR::RIGHT));
			++Wave4;
		}
		else if (elapsed_time > 7000 && elapsed_time <= 8000 && Wave4 == 5) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4LR>(CharacterID::ZKCHRSTG3WV4_L2, Stg3WAVE4LR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv4LR>(CharacterID::ZKCHRSTG3WV4_R2, Stg3WAVE4LR::RIGHT));
			++Wave4;
		}
		if ((*Field::DEAD_FLAGS)[CharacterID::ZKCHRSTG3WV4_C] == true) {
			if (ZkChrStg3Wv4C::MODE == Stg3WAVE4CMode::PORTAL
				|| ZkChrStg3Wv4C::MODE == Stg3WAVE4CMode::NOTIFY
				|| ZkChrStg3Wv4C::MODE == Stg3WAVE4CMode::LASER) 
			{
				for (auto& portal_id : ZkChrStg3Wv4C::PORTAL_IDS) {	// 根源が残っているなら消去
					(*Field::ENEMY_BULLETS).erase(portal_id);
				}
				ZkChrStg3Wv4C::PORTAL_IDS.clear();
			}
			if (ZkChrStg3Wv4C::MODE == Stg3WAVE4CMode::LASER) {
				for (auto& laser_id : ZkChrStg3Wv4C::LASER_IDS) {	// レーザーが残っているなら消去
					(*Field::ENEMY_LASERS).erase(laser_id);
				}
				ZkChrStg3Wv4C::LASER_IDS.clear();
			}
		}
		if (elapsed_time > 20000) {
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::WAVE5;
		}
		break;

	case Stage3Progress::WAVE5:
	{
		if ( elapsed_time > 3000 && elapsed_time <= 4000 && Wave5 == 1 ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L1 , Stg3WAVE5TLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R1 , Stg3WAVE5TLR::RIGHT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_L1 , Stg3WAVE5BLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_R1 , Stg3WAVE5BLR::RIGHT));
			++Wave5;
		}
		else if ( elapsed_time > 4000 && elapsed_time <= 5000 && Wave5 == 2 ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L2 , Stg3WAVE5TLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R2 , Stg3WAVE5TLR::RIGHT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_L2 , Stg3WAVE5BLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_R2 , Stg3WAVE5BLR::RIGHT));
			++Wave5;
		}
		else if ( elapsed_time > 5000 && elapsed_time <= 6000 && Wave5 == 3 ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L3 , Stg3WAVE5TLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R3 , Stg3WAVE5TLR::RIGHT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_L3 , Stg3WAVE5BLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_R3 , Stg3WAVE5BLR::RIGHT));
			++Wave5;
		}
		else if ( elapsed_time > 6000 && elapsed_time <= 7000 && Wave5 == 4 ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L4 , Stg3WAVE5TLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R4 , Stg3WAVE5TLR::RIGHT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_L4 , Stg3WAVE5BLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_R4 , Stg3WAVE5BLR::RIGHT));
			++Wave5;
		}
		else if ( elapsed_time > 7000 && elapsed_time <= 8000 && Wave5 == 5 ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L5 , Stg3WAVE5TLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R5 , Stg3WAVE5TLR::RIGHT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_L5 , Stg3WAVE5BLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5BLR>(CharacterID::ZKCHRSTG3WV5_B_R5 , Stg3WAVE5BLR::RIGHT));
			++Wave5;
		}
		else if ( elapsed_time > 8000 && elapsed_time <= 9000 && Wave5 == 6 ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L6 , Stg3WAVE5TLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R6 , Stg3WAVE5TLR::RIGHT));
			++Wave5;
		}
		else if ( elapsed_time > 9000 && elapsed_time <= 10000 && Wave5 == 7 ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L7 , Stg3WAVE5TLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R7 , Stg3WAVE5TLR::RIGHT));
			++Wave5;
		}
		else if ( elapsed_time > 10000 && elapsed_time <= 11000 && Wave5 == 8 ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L8 , Stg3WAVE5TLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R8 , Stg3WAVE5TLR::RIGHT));
			++Wave5;
		}
		else if ( elapsed_time > 11000 && elapsed_time <= 12000 && Wave5 == 9 ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L9 , Stg3WAVE5TLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R9 , Stg3WAVE5TLR::RIGHT));
			++Wave5;
		}
		else if ( elapsed_time > 12000 && elapsed_time <= 13000 && Wave5 == 10 ) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_L10 , Stg3WAVE5TLR::LEFT));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv5TLR>(CharacterID::ZKCHRSTG3WV5_T_R10 , Stg3WAVE5TLR::RIGHT));
			++Wave5;
		}
		else if ( elapsed_time > 33000 ) {
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::WAVE6;
		}
		break;
	}
	case Stage3Progress::WAVE6:
		if (elapsed_time > 3000 && Wave6 == 1) {
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6C>());
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6LR>(CharacterID::ZKCHRSTG3WV6_L));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg3Wv6LR>(CharacterID::ZKCHRSTG3WV6_R));
			++Wave6;
		}
		else if (elapsed_time > 28000) {
			kept_clock = DxLib::GetNowCount();
			PROGRESS = Stage3Progress::BOSS;
		}
		break;

	case Stage3Progress::BOSS:
	{
		if (elapsed_time > 1000 && Wave7 == 1 && boss_advented_flag == false) {
			Field::BOSS_CHARACTERS->push_back(make_unique<Toroi>());
			boss_advented_clock = DxLib::GetNowCount();
			boss_advented_flag = true;
			++Wave7;
		}

		int boss_advent_delta_time = DxLib::GetNowCount() - boss_advented_clock;
		if (boss_advent_delta_time > 2000 && before_decision_pushed_flag == false) {
			for (const auto& tuple : BEFORE_BOSS_WORDS) {
				GameConductor::NARRATIVE_POPS.push_back(make_unique<NarrativePop>(tuple));
			}
			before_decision_pushed_flag = true;
		}


		if (before_decision_pushed_flag == true && GameConductor::NARRATIVE_POPS.empty() == true) {

			GameConductor::REQUEST_FIELD_UPDATE_STOP();
			wstring yes_no_indicator_text;
			switch (yes_no_indicator_status)
			{
			case Y_N::YES:
				yes_no_indicator_text = L"はい←\nいいえ";
				break;
			case Y_N::NO:
				yes_no_indicator_text = L"はい\nいいえ←";
				break;
			}

			DxLib::DrawFormatStringToHandle(
				InFieldPosition(Field::PIXEL_SIZE_X / 2, Field::PIXEL_SIZE_Y / 2).get_draw_position().x,
				InFieldPosition(Field::PIXEL_SIZE_X / 2, Field::PIXEL_SIZE_Y / 2).get_draw_position().y,
				Colors::YELLOW,
				FontHandles::NAVIGATION_TEXT,
				yes_no_indicator_text.c_str()
			);

			if (KeyPushFlags::Z == true && AppSession::KEY_BUFFER[ KEY_INPUT_Z ] == 0) {
				KeyPushFlags::Z = false;
			}
			else if (KeyPushFlags::Z == false && AppSession::KEY_BUFFER[ KEY_INPUT_Z ] == 1) {
				KeyPushFlags::Z = true;
				if (yes_no_indicator_status == Y_N::YES) {
					for (const auto& tuple : BEFORE_BOSS_ADDITIONAL_WORDS) {
						GameConductor::NARRATIVE_POPS.push_back(make_unique<NarrativePop>(tuple));
					}
					for (const auto& tuple : BEFORE_BOSS_REST_WORDS) {
						GameConductor::NARRATIVE_POPS.push_back(make_unique<NarrativePop>(tuple));
					}
				}
				else {
					for (const auto& tuple : BEFORE_BOSS_REST_WORDS) {
						GameConductor::NARRATIVE_POPS.push_back(make_unique<NarrativePop>(tuple));
					}
				}
				PROGRESS = Stage3Progress::EPILOGUE;
			}

			if (KeyPushFlags::UP == false && AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 1) {
				KeyPushFlags::UP = true;
				if (yes_no_indicator_status == Y_N::NO) {
					yes_no_indicator_status = Y_N::YES;
				}
			}
			if (KeyPushFlags::UP == true && AppSession::KEY_BUFFER[ KEY_INPUT_UP ] == 0) {
				KeyPushFlags::UP = false;
			}

			if (KeyPushFlags::DOWN == false && AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 1) {
				KeyPushFlags::DOWN = true;
				if (yes_no_indicator_status == Y_N::YES) {
					yes_no_indicator_status = Y_N::NO;
				}
			}
			if (KeyPushFlags::DOWN == true && AppSession::KEY_BUFFER[ KEY_INPUT_DOWN ] == 0) {
				KeyPushFlags::DOWN = false;
			}

		}
		break;
	}
	case Stage3Progress::EPILOGUE:
		if ((*Field::DEAD_FLAGS)[CharacterID::TOROI] == true && boss_crushed_flag == false) {
			boss_crushed_flag = true;
			Field::ENEMY_BULLETS->clear();
			Field::ENEMY_LASERS->clear();
			Field::ZAKO_CHARACTERS->clear();
			for (const auto& tuple : AFTER_BOSS_WORDS) {
				GameConductor::NARRATIVE_POPS.push_back(make_unique<NarrativePop>(tuple));
			}
		}
		if (boss_crushed_flag == true && GameConductor::NARRATIVE_POPS.empty() == true) {
			PROGRESS = Stage3Progress::END;
		}
		break;

	case Stage3Progress::END:
		Field::BOSS_CHARACTERS->clear();
		GameConductor::STAGE3_CLEAR_FLAG = true;
		DxLib::StopSoundMem(SoundHandles::STAGE3BGM);
		break;
	}
}