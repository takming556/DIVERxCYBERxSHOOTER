﻿#include <string>
#include <memory>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "GameConductor.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg1BsSp3.h"
#include "Character/EnemyCharacter/BossCharacter/Mofu.h"
#include "CollideRealm/CollideCircle.h"
#include "Barrage/Emission/StraightShotEmission/SimpleStraightShotEmission.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Offensive/Bullet/StraightShot/FloatingTerrorShot.h"
#include "Offensive/Bullet/CurvingShot.h"
#include "Offensive/Bullet/SwayingShot.h"
#include "SpNameDisplay.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"


using std::wstring;
using std::move;
using std::make_unique;
using std::numbers::pi;

const wstring Mofu::CHARACTER_NAME(L"海月もふ");
const wstring Mofu::SP1_NAME(L"「Floating Terror」");
const wstring Mofu::SP2_NAME(L"「痺れる触手」");
const wstring Mofu::SP3_NAME(L"「海月雨」");
MofuStatus Mofu::STATUS;

const int Mofu::INITIAL_POS_X = 310;
const int Mofu::INITIAL_POS_Y = 620;
const unsigned int Mofu::COLLIDANT_SIZE = 60;
const double Mofu::DRAW_EXTRATE = 0.07;

const unsigned int Mofu::INITIAL_HP = 1000;

const double Mofu::NM1_ACTIVATE_HP_RATIO = 100.0 / 100.0;
const double Mofu::SP1_ACTIVATE_HP_RATIO = 85.0 / 100.0;
const double Mofu::NM2_ACTIVATE_HP_RATIO = 65.0 / 100.0;
const double Mofu::SP2_ACTIVATE_HP_RATIO = 50.0 / 100.0;
const double Mofu::NM3_ACTIVATE_HP_RATIO = 30.0 / 100.0;
const double Mofu::SP3_ACTIVATE_HP_RATIO = 20.0 / 100.0;

const unsigned int Mofu::SP1_ACCOMPLISH_BONUS = 100000;
const unsigned int Mofu::SP2_ACCOMPLISH_BONUS = 85000;
const unsigned int Mofu::SP3_ACCOMPLISH_BONUS = 70000;

const unsigned int Mofu::CRUSH_BONUS = 500000;

const unsigned int Mofu::NORMAL1_AMOUNT = 12;
const unsigned int Mofu::NORMAL1_INTERVAL = 1000;
const unsigned int Mofu::NORMAL1_SCATTERING_Y = 100;
const double Mofu::NORMAL1_SHOT_SPEED = 200;
const unsigned int Mofu::NORMAL1_SHOT_COLLIDANT_SIZE = 20;
const unsigned int Mofu::NORMAL1_SHOT_DURABILITY = 1;

const unsigned int Mofu::SP1_AMOUNT = 20;
const unsigned int Mofu::SP1_INTERVAL = 2000;
const unsigned int Mofu::SP1_SCATTERING_Y = 30;

const unsigned int Mofu::NORMAL2_BARRAGE_NOZZLES = 12;;
const unsigned int Mofu::NORMAL2_BARRAGE_INTERVAL = 2000;
const double Mofu::NORMAL2_BARRAGE_SPEED = 220;
const unsigned int Mofu::NORMAL2_BARRAGE_COLLIDANT_SIZE = 20;
const unsigned int Mofu::NORMAL2_BARRAGE_DURABILITY = 1;
//const double Mofu::NORMAL2_BARRAGE_DRAW_EXTRATE = ;
const unsigned int Mofu::NORMAL2_LINES_INTERVAL = 1000 / 4;
const double Mofu::NORMAL2_LINES_SPEED = 250;
const unsigned int Mofu::NORMAL2_LINES_COLLIDANT_SIZE = 10;
const unsigned int Mofu::NORMAL2_LINES_DURABILITY = 1;
//const double Mofu::NORMAL2_LINES_DRAW_EXTRATE = ;

const unsigned int Mofu::SP2_SWAYING_INTERVAL = 5000;
const unsigned int Mofu::SP2_SWAYING_TICK_INTERVAL = 40;
const unsigned int Mofu::SP2_SWAYING_TICKS = 30;
const double Mofu::SP2_SWAYING_MOVESPEED = 400;
const unsigned int Mofu::SP2_SWAYING_COLLIDANT_SIZE = 20;
const unsigned int Mofu::SP2_SWAYING_DURABILITY = 1;
const double Mofu::SP2_SWAYING_INTENSITY = 0.3;
const double Mofu::SP2_SWAYING_FREQUENCY = 1.0;
const unsigned int Mofu::SP2_STRAIGHT_INTERVAL = 1000 / 2;
const double Mofu::SP2_STRAIGHT_MOVESPEED = 200;
const unsigned int Mofu::SP2_STRAIGHT_COLLIDANT_SIZE = 10;
const unsigned int Mofu::SP2_STRAIGHT_DURABILITY = 1;

const unsigned int Mofu::NORMAL3_RIGHTROLL_NOZZLES = 24;
const unsigned int Mofu::NORMAL3_LEFTROLL_NOZZLES = 24;
const double Mofu::NORMAL3_RIGHTROLL_MOVESPEED = 300;
const double Mofu::NORMAL3_LEFTROLL_MOVESPEED = 300;
const double Mofu::NORMAL3_RIGHTROLL_CURVESPEED = -(1.0 / 6.0) * pi;
const double Mofu::NORMAL3_LEFTROLL_CURVESPEED = 1.0 / 6.0 * pi;
const unsigned int Mofu::NORMAL3_RIGHTROLL_COLLIDANT_SIZE = 20;
const unsigned int Mofu::NORMAL3_LEFTROLL_COLLIDANT_SIZE = 20;
const unsigned int Mofu::NORMAL3_RIGHTROLL_DURABILITY = 1;
const unsigned int Mofu::NORMAL3_LEFTROLL_DURABILITY = 1;
const unsigned int Mofu::NORMAL3_BARRAGE_INTERVAL = 0;
const unsigned int Mofu::NORMAL3_TICK_INTERVAL = 500;
const unsigned int Mofu::NORMAL3_TICKS = 10;

const unsigned int Mofu::SP3_MOFU_TICKS = 5;
const unsigned int Mofu::SP3_MOFU_TICK_INTERVAL = 125;
const unsigned int Mofu::SP3_MOFU_SHOT_INTERVAL = 3000;
const double Mofu::SP3_MOFU_SHOT_SPEED = 200;
const unsigned int Mofu::SP3_MOFU_SHOT_COLLIDANT_SIZE = 20;
const unsigned int Mofu::SP3_MOFU_SHOT_DURABILITY = 1;
const unsigned int Mofu::SP3_ZK_CRASH_DAMAGE = 40;




Mofu::Mofu() :
	Character(
		CharacterID::MOFU,
		INITIAL_POS_X,
		INITIAL_POS_Y,
		INITIAL_HP,
		make_unique<CollideCircle>(INITIAL_POS_X, INITIAL_POS_Y, COLLIDANT_SIZE)
	),
	BossCharacter(CHARACTER_NAME, INITIAL_HP, CRUSH_BONUS),
	generated_clock(DxLib::GetNowCount()),
	last_status_changed_clock(DxLib::GetNowCount()),
	last_normal1_performed_clock(0),
	last_sp1_performed_clock(0),
	last_normal2_lines_performed_clock(0),
	last_sp2_swaying_performed_clock(0),
	last_sp2_swaying_tick_fired_clock(0),
	last_sp2_straight_performed_clock(0),
	last_normal3_tickked_clock(0),
	last_normal3_barraged_clock(0),
	normal2_barrage(make_unique<SimpleStraightShotEmission>(
		INITIAL_POS_X,
		INITIAL_POS_Y,
		0,
		true,
		114514,
		NORMAL2_BARRAGE_NOZZLES,
		NORMAL2_BARRAGE_INTERVAL,
		NORMAL2_BARRAGE_SPEED,
		NORMAL2_BARRAGE_COLLIDANT_SIZE,
		NORMAL2_BARRAGE_DURABILITY,
		TeamID::ENEMY,
		SkinID::BUBBLE_GENERIC
		)
	),
	sp2_swaying_tick_count(0),
	sp2_swaying_tick_firing_flag(false),
	arg_sp2_swaying_toward_mychr(0.0),
	normal3_mode(MofuNormal3Mode::LEFTROLL),
	normal3_tick_count(0),
	sp3_mofu_start_nozzles(0),
	sp3_mofu_end_nozzles(0),
	sp3_zk_crash_1_first_flag(true),
	sp3_zk_crash_2_first_flag(true),
	sp3_zk_crash_3_first_flag(true),
	sp3_zk_crash_4_first_flag(true)
{
	STATUS = MofuStatus::STANDBY;

	switch (STATUS)
	{
	case MofuStatus::NORMAL1:
		hp = INITIAL_HP * NM1_ACTIVATE_HP_RATIO;
		break;
	case MofuStatus::SP1:
		hp = INITIAL_HP * SP1_ACTIVATE_HP_RATIO;
		break;
	case MofuStatus::NORMAL2:
		hp = INITIAL_HP * NM2_ACTIVATE_HP_RATIO;
		break;
	case MofuStatus::SP2:
		hp = INITIAL_HP * SP2_ACTIVATE_HP_RATIO;
		break;
	case MofuStatus::NORMAL3:
		hp = INITIAL_HP * NM3_ACTIVATE_HP_RATIO;
		break;
	case MofuStatus::SP3:
		hp = INITIAL_HP * SP3_ACTIVATE_HP_RATIO;
		break;
	default:
		break;
	}
}


void Mofu::update() {
	switch (STATUS) {
	case MofuStatus::STANDBY:
	{
		int generate_delta_time = DxLib::GetNowCount() - generated_clock;
		if (generate_delta_time > 5000) {
			STATUS = MofuStatus::NORMAL1;
		}
		break;
	}
	case MofuStatus::NORMAL1:
	{
		if (hp > INITIAL_HP * SP1_ACTIVATE_HP_RATIO) {
			int normal1_perform_delta_time = DxLib::GetNowCount() - last_normal1_performed_clock;
			if (normal1_perform_delta_time > NORMAL1_INTERVAL) {
				for (int i = 0; i < NORMAL1_AMOUNT; i++) {
					int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);
					int random_y = DxLib::GetRand(NORMAL1_SCATTERING_Y) + 600;

					(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
						random_x,
						random_y,
						-(1.0 / 2.0) * pi,
						NORMAL1_SHOT_SPEED,
						NORMAL1_SHOT_COLLIDANT_SIZE,
						NORMAL1_SHOT_DURABILITY,
						SkinID::BUBBLE_GENERIC
					);
					DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				}
				last_normal1_performed_clock = DxLib::GetNowCount();
			}
		}
		else {
			Field::ENEMY_BULLETS->clear();
			STATUS = MofuStatus::SP1;
			last_status_changed_clock = DxLib::GetNowCount();
			Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP1_NAME));
		}
		break;
	}

	case MofuStatus::SP1:
		if (hp > INITIAL_HP * NM2_ACTIVATE_HP_RATIO) {
			int sp1_perform_delta_time = DxLib::GetNowCount() - last_sp1_performed_clock;
			if (sp1_perform_delta_time > SP1_INTERVAL) {
				for (int i = 0; i < SP1_AMOUNT; i++) {
					int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);
					int random_y = DxLib::GetRand(SP1_SCATTERING_Y) - SP1_SCATTERING_Y;

					(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<FloatingTerrorShot>(random_x, random_y);

					last_sp1_performed_clock = DxLib::GetNowCount();
				}
			}
		}
		else {
			Field::ENEMY_BULLETS->clear();
			GameConductor::TECHNICAL_SCORE += SP1_ACCOMPLISH_BONUS;
			STATUS = MofuStatus::NORMAL2;
			last_status_changed_clock = DxLib::GetNowCount();
		}
		break;

	case MofuStatus::NORMAL2:
		if (hp > INITIAL_HP * SP2_ACTIVATE_HP_RATIO) {
			normal2_barrage->update(position->x, position->y);
			int normal2_lines_perform_delta_time = DxLib::GetNowCount() - last_normal2_lines_performed_clock;
			if (normal2_lines_perform_delta_time > NORMAL2_LINES_INTERVAL) {

				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double delta_x_mychr = my_chr_pos.x - position->x;
				double delta_y_mychr = my_chr_pos.y - position->y;
				double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr + (1.0 / 12.0) * pi,
					NORMAL2_LINES_SPEED,
					NORMAL2_LINES_COLLIDANT_SIZE,
					NORMAL2_LINES_DURABILITY,
					SkinID::BUBBLE_GENERIC_10
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr,
					NORMAL2_LINES_SPEED,
					NORMAL2_LINES_COLLIDANT_SIZE,
					NORMAL2_LINES_DURABILITY,
					SkinID::BUBBLE_GENERIC_10
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr - (1.0 / 12.0) * pi,
					NORMAL2_LINES_SPEED,
					NORMAL2_LINES_COLLIDANT_SIZE,
					NORMAL2_LINES_DURABILITY,
					SkinID::BUBBLE_GENERIC_10
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				last_normal2_lines_performed_clock = DxLib::GetNowCount();
			}
		}
		else {
			Field::ENEMY_BULLETS->clear();
			STATUS = MofuStatus::SP2;
			last_status_changed_clock = DxLib::GetNowCount();
			Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP2_NAME));
		}
		break;

	case MofuStatus::SP2:
		if (hp > INITIAL_HP * NM3_ACTIVATE_HP_RATIO) {

			int elapsed_time_sp2_swaying_last_performed = DxLib::GetNowCount() - last_sp2_swaying_performed_clock;
			if (elapsed_time_sp2_swaying_last_performed > SP2_SWAYING_INTERVAL) {
				if (sp2_swaying_tick_count < SP2_SWAYING_TICKS) {

					if (sp2_swaying_tick_firing_flag == false) {
						InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
						double delta_x_mychr = my_chr_pos.x - position->x;
						double delta_y_mychr = my_chr_pos.y - position->y;
						arg_sp2_swaying_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
						sp2_swaying_tick_firing_flag = true;
					}

					int elapsed_time_sp2_swaying_tick_last_fired = DxLib::GetNowCount() - last_sp2_swaying_tick_fired_clock;
					if (elapsed_time_sp2_swaying_tick_last_fired > SP2_SWAYING_TICK_INTERVAL) {

						(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<SwayingShot>(
							position->x,
							position->y,
							arg_sp2_swaying_toward_mychr - (1.0 / 4.0) * pi,
							SP2_SWAYING_MOVESPEED,
							SP2_SWAYING_INTENSITY,
							SP2_SWAYING_FREQUENCY,
							SP2_SWAYING_COLLIDANT_SIZE,
							SP2_SWAYING_DURABILITY,
							SkinID::BUBBLE_GENERIC
						);
						DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

						(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<SwayingShot>(
							position->x,
							position->y,
							arg_sp2_swaying_toward_mychr,
							SP2_SWAYING_MOVESPEED,
							SP2_SWAYING_INTENSITY,
							SP2_SWAYING_FREQUENCY,
							SP2_SWAYING_COLLIDANT_SIZE,
							SP2_SWAYING_DURABILITY,
							SkinID::BUBBLE_GENERIC
						);
						DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

						(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<SwayingShot>(
							position->x,
							position->y,
							arg_sp2_swaying_toward_mychr + (1.0 / 4.0) * pi,
							SP2_SWAYING_MOVESPEED,
							SP2_SWAYING_INTENSITY,
							SP2_SWAYING_FREQUENCY,
							SP2_SWAYING_COLLIDANT_SIZE,
							SP2_SWAYING_DURABILITY,
							SkinID::BUBBLE_GENERIC
						);
						DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

						++sp2_swaying_tick_count;
						last_sp2_swaying_tick_fired_clock = DxLib::GetNowCount();
					}
				}
				else {
					last_sp2_swaying_performed_clock = DxLib::GetNowCount();
					sp2_swaying_tick_count = 0;
					sp2_swaying_tick_firing_flag = false;
				}
			}

			int elapsed_time_last_sp2_straight_performed = DxLib::GetNowCount() - last_sp2_straight_performed_clock;
			if (elapsed_time_last_sp2_straight_performed > SP2_STRAIGHT_INTERVAL) {
				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double delta_x_mychr = my_chr_pos.x - position->x;
				double delta_y_mychr = my_chr_pos.y - position->y;
				double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);

				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr - (1.0 / 10.0) * pi,
					SP2_STRAIGHT_MOVESPEED,
					SP2_STRAIGHT_COLLIDANT_SIZE,
					SP2_STRAIGHT_DURABILITY,
					SkinID::BUBBLE_GENERIC_10
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr,
					SP2_STRAIGHT_MOVESPEED,
					SP2_STRAIGHT_COLLIDANT_SIZE,
					SP2_STRAIGHT_DURABILITY,
						SkinID::BUBBLE_GENERIC_10
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					position->x,
					position->y,
					arg_toward_mychr + (1.0 / 10.0) * pi,
					SP2_STRAIGHT_MOVESPEED,
					SP2_STRAIGHT_COLLIDANT_SIZE,
					SP2_STRAIGHT_DURABILITY,
					SkinID::BUBBLE_GENERIC_10
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

				last_sp2_straight_performed_clock = DxLib::GetNowCount();
			}
		}
		else {
			Field::ENEMY_BULLETS->clear();
			GameConductor::TECHNICAL_SCORE += SP2_ACCOMPLISH_BONUS;
			STATUS = MofuStatus::NORMAL3;
			last_status_changed_clock = DxLib::GetNowCount();
		}
		break;

	case MofuStatus::NORMAL3:
		if (hp > INITIAL_HP * SP3_ACTIVATE_HP_RATIO) {
			int elapsed_time_since_last_barraged = DxLib::GetNowCount() - last_normal3_barraged_clock;
			if (elapsed_time_since_last_barraged > NORMAL3_BARRAGE_INTERVAL) {
				if (normal3_tick_count < NORMAL3_TICKS) {
					int elapsed_time_since_last_tickked = DxLib::GetNowCount() - last_normal3_tickked_clock;
					if (elapsed_time_since_last_tickked > NORMAL3_TICK_INTERVAL) {
						switch (normal3_mode) {
						case MofuNormal3Mode::LEFTROLL:
							for (int i = 0; i < NORMAL3_LEFTROLL_NOZZLES; i++) {
								double i_arg = 2 * pi / NORMAL3_LEFTROLL_NOZZLES * i;

								(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<CurvingShot>(
									position->x,
									position->y,
									i_arg,
									NORMAL3_LEFTROLL_MOVESPEED,
									NORMAL3_LEFTROLL_CURVESPEED,
									NORMAL3_LEFTROLL_COLLIDANT_SIZE,
									NORMAL3_LEFTROLL_DURABILITY,
									SkinID::BUBBLE_GENERIC
								);
								DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

							}
							normal3_mode = MofuNormal3Mode::RIGHTROLL;
							break;

						case MofuNormal3Mode::RIGHTROLL:
							for (int i = 0; i < NORMAL3_RIGHTROLL_NOZZLES; i++) {
								double i_arg = 2 * pi / NORMAL3_RIGHTROLL_NOZZLES * i;

								(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<CurvingShot>(
									position->x,
									position->y,
									i_arg,
									NORMAL3_RIGHTROLL_MOVESPEED,
									NORMAL3_RIGHTROLL_CURVESPEED,
									NORMAL3_RIGHTROLL_COLLIDANT_SIZE,
									NORMAL3_RIGHTROLL_DURABILITY,
									SkinID::BUBBLE_GENERIC
								);
								DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);

							}
							normal3_mode = MofuNormal3Mode::LEFTROLL;
							break;
						}
						++normal3_tick_count;
						last_normal3_tickked_clock = DxLib::GetNowCount();
					}
				}
				else {
					last_normal3_barraged_clock = DxLib::GetNowCount();
					normal3_tick_count = 0;
				}
			}
		}
		else {
			Field::ENEMY_BULLETS->clear();
			STATUS = MofuStatus::SP3;
			last_status_changed_clock = DxLib::GetNowCount();
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1BsSp3>(CharacterID::ZKCHRSTG1BSSP3_A, 62, 560));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1BsSp3>(CharacterID::ZKCHRSTG1BSSP3_B, 186, 590));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1BsSp3>(CharacterID::ZKCHRSTG1BSSP3_C, 434, 590));
			Field::ZAKO_CHARACTERS->push_back(make_unique<ZkChrStg1BsSp3>(CharacterID::ZKCHRSTG1BSSP3_D, 558, 560));
			Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP3_NAME));
		}
		break;

	case MofuStatus::SP3:
	{
		int zk_crash_count = 0;
		if ((*Field::DEAD_FLAGS)[ CharacterID::ZKCHRSTG1BSSP3_A ] == true) {
			zk_crash_count++;
		}
		if ((*Field::DEAD_FLAGS)[ CharacterID::ZKCHRSTG1BSSP3_B ] == true) {
			zk_crash_count++;
		}
		if ((*Field::DEAD_FLAGS)[ CharacterID::ZKCHRSTG1BSSP3_C ] == true) {
			zk_crash_count++;
		}
		if ((*Field::DEAD_FLAGS)[ CharacterID::ZKCHRSTG1BSSP3_D ] == true) {
			zk_crash_count++;
		}

		switch (zk_crash_count) {
		case 0:
			sp3_mofu_start_nozzles = 0;
			sp3_mofu_end_nozzles = 0;
			break;
		case 1:
			if (sp3_zk_crash_1_first_flag == true) {
				hp -= SP3_ZK_CRASH_DAMAGE;
				sp3_zk_crash_1_first_flag = false;
			}
			sp3_mofu_start_nozzles = 0;
			sp3_mofu_end_nozzles = 1;
			break;
		case 2:
			if (sp3_zk_crash_2_first_flag == true) {
				hp -= SP3_ZK_CRASH_DAMAGE;
				sp3_zk_crash_2_first_flag = false;
			}
			sp3_mofu_start_nozzles = 23;	// マイナスだと弾が出ないので
			sp3_mofu_end_nozzles = 26;
			break;
		case 3:
			if (sp3_zk_crash_3_first_flag == true) {
				hp -= SP3_ZK_CRASH_DAMAGE;
				sp3_zk_crash_3_first_flag = false;
			}
			sp3_mofu_start_nozzles = 22;	// マイナスだと弾がでないので
			sp3_mofu_end_nozzles = 27;
			break;
		case 4:
			if (sp3_zk_crash_4_first_flag == true){
				hp -= SP3_ZK_CRASH_DAMAGE;
				GameConductor::TECHNICAL_SCORE += Mofu::SP3_ACCOMPLISH_BONUS;
				sp3_zk_crash_4_first_flag = false;
			}
			sp3_mofu_start_nozzles = 0;
			sp3_mofu_end_nozzles = 24;
			
			break;
		}

		if (sp3_mofu_tick_count < SP3_MOFU_TICKS) {
			int tick_fire_delta_time = DxLib::GetNowCount() - last_sp3_mofu_tickked_clock;
			if (tick_fire_delta_time > SP3_MOFU_TICK_INTERVAL) {

				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double delta_x_mychr = my_chr_pos.x - position->x;
				double delta_y_mychr = my_chr_pos.y - position->y;
				double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);

				for (int i = sp3_mofu_start_nozzles; i < sp3_mofu_end_nozzles; ++i) {
					(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
						position->x,
						position->y,
						arg_toward_mychr + (1.0 / 12.0) * i * pi,
						SP3_MOFU_SHOT_SPEED,
						SP3_MOFU_SHOT_COLLIDANT_SIZE,
						SP3_MOFU_SHOT_DURABILITY,
						SkinID::BUBBLE_GENERIC
					);

				}
				if (zk_crash_count >= 1) {
					DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK); //0のときも音なりそう
				}
				++sp3_mofu_tick_count;
				last_sp3_mofu_tickked_clock = DxLib::GetNowCount();
			}
		}
		else {
			int shot_complete_delta_time = DxLib::GetNowCount() - last_sp3_mofu_shot_completed_clock;
			if (shot_complete_delta_time > SP3_MOFU_SHOT_INTERVAL) {
				sp3_mofu_tick_count = 0;
				last_sp3_mofu_shot_completed_clock = DxLib::GetNowCount();
			}
		}
		break;
	}
	collidant->update(position);
	}
}


void Mofu::draw() {
	draw_hp_donut();
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_MOFU, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}


void Mofu::funeral() {
	if (funeral_held_flag == false) {

		DxLib::PlaySoundMem(SoundHandles::BOSSCRASH, DX_PLAYTYPE_BACK);
		GameConductor::TECHNICAL_SCORE += crush_bonus;

		if ((*Field::DEAD_FLAGS)[ CharacterID::ZKCHRSTG1BSSP3_A ] == false) {
			Field::ERASE_ZAKO_CHARACTER(CharacterID::ZKCHRSTG1BSSP3_A);
		}
		if ((*Field::DEAD_FLAGS)[ CharacterID::ZKCHRSTG1BSSP3_B ] == false) {
			Field::ERASE_ZAKO_CHARACTER(CharacterID::ZKCHRSTG1BSSP3_B);
		}
		if ((*Field::DEAD_FLAGS)[ CharacterID::ZKCHRSTG1BSSP3_C ] == false) {
			Field::ERASE_ZAKO_CHARACTER(CharacterID::ZKCHRSTG1BSSP3_C);
		}
		if ((*Field::DEAD_FLAGS)[ CharacterID::ZKCHRSTG1BSSP3_D ] == false) {
			Field::ERASE_ZAKO_CHARACTER(CharacterID::ZKCHRSTG1BSSP3_D);
		}

		funeral_held_flag = true;

	}
}