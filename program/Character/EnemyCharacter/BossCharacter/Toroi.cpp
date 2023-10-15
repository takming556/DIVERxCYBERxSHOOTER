#include <string>
#include <memory>
#include <numbers>
#include <cmath>
#include "DxLib.h"
#include "enum.h"
#include "Character/Character.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/Toroi.h"
#include "CollideRealm/CollideCircle.h"
#include "Position/InFieldPosition.h"
#include "FontHandles.h"
#include "Colors.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"
#include "Field.h"
#include "Offensive/Bullet/CurvingShot.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Offensive/Bullet/ParabolicShot.h"
#include "Offensive/Bullet/StraightShot/ReflectShot/ReflectShot.h"
#include "Offensive/Laser/Laser.h"
#include "Offensive/Laser/PolarLaser.h"
#include "Offensive/Laser/CartesianLaser.h"
#include "Offensive/Bullet/StraightShot/ReflectShot/DVDShot.h"


using std::wstring;
using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;

ToroiStatus Toroi::STATUS;

const wstring Toroi::NAME(L"愛生トロイ");
const wstring Toroi::SP1_NAME(L"「Trick or Treat or Trap?」");
const wstring Toroi::SP2_NAME(L"「慈子欺瞞クリーナー」");
const wstring Toroi::SP3_NAME(L"「赤き怨みは稲穂を揺らす」");
const wstring Toroi::SP4_NAME(L"「咲き誇れ、血染めの梅」");
const wstring Toroi::SP5_NAME(L"「インターネット再興」");
const wstring Toroi::SP6_NAME(L"「Ex-tROiA.ru4(D)」");
const wstring Toroi::SP7_NAME(L"「限りなく降り注ぐ、嬰怨の涙」");
const int Toroi::INITIAL_POS_X = 310;
const int Toroi::INITIAL_POS_Y = 620;
const unsigned int Toroi::INITIAL_COLLIDANT_SIZE = 60;
const double Toroi::DRAW_EXTRATE = 0.07;

const unsigned int Toroi::NM2_LASER_LENGTH = 700;//長さ
const unsigned int Toroi::NM2_LASER_WIDTH = 70;
const unsigned int Toroi::LASERNOZZLES = 42;
const unsigned int Toroi::NM3_PARASOL_RAIN_INTERVAL = 1000;
const unsigned int Toroi::NM3_PARASOL_RAIN_LANE_COUNT = 6;
const unsigned int Toroi::NM3_PARASOL_RAIN_THROW_SPEED = 100;
const double Toroi::NM3_PARASOL_RAIN_GRAVITY_ACCEL = 150.0;
const unsigned int Toroi::NM3_PARASOL_RAIN_COLLIDANT_SIZE = 10;
const unsigned int Toroi::NM3_PARASOL_RAIN_FRAMING_INTERVAL = 300;
const unsigned int Toroi::NM4_BIG_NOZZLES = 30;
const unsigned int Toroi::NM4_INTERVAL = 1000;
const double Toroi::NM4_SPEED = 200;
const unsigned int Toroi::NM4_COLLIDANT_SIZE_BIG = 20;
const unsigned int Toroi::NM4_COLLIDANT_SIZE_SMALL = 10;

const int Toroi::SP1_THINKING_TIME_LENGTH = 5000;						// [ミリ秒]
const unsigned int Toroi::SP1_TRICK_DURATION = 10000;					// [ミリ秒]
const unsigned int Toroi::SP1_TRICK_NOZZLES = 32;						// SP1のTrickのノズル数
const unsigned int Toroi::SP1_TRICK_NOZZLE_RADIUS = 70;					// SP1のTrickの弾の発射点の半径
const double Toroi::SP1_TRICK_NOZZLE_ROTATE_SPEED = (1.0 / 2.0) * pi;	// SP1のTrickのノズル回転速度
const unsigned int Toroi::SP1_TRICK_SHOT_SPEED = 250;					// SP1のTrickの弾の速さ
const unsigned int Toroi::SP1_TRICK_SHOT_INTERVAL = 300;				// SP1のTrickの発射間隔[ミリ秒]
const unsigned int Toroi::SP1_TRICK_SHOT_COLLIDANT_SIZE = 10;			// SP1のTrickの弾の当たり判定サイズ
const unsigned int Toroi::SP1_TREAT_DURATION = 15000;					// [ミリ秒]
const unsigned int Toroi::SP1_TREAT_THROW_AMOUNT = 64;
const unsigned int Toroi::SP1_TREAT_THROW_INTERVAL = 1500;				// [ミリ秒]
const unsigned int Toroi::SP1_TRAP_SHOT_INTERVAL = 33;					// [ミリ秒]
const unsigned int Toroi::SP1_TRAP_SHOT_COLLIDANT_SIZE = 7;
const unsigned int Toroi::SP1_TRAP_ACROSS_SPEED = 250;					// [ピクセル／秒]
const unsigned int Toroi::SP1_TRAP_HORIZONTAL_ACROSS_DURATION = (double)(Field::PIXEL_SIZE_X / Toroi::SP1_TRAP_ACROSS_SPEED) * 1000;	// [ミリ秒]
const unsigned int Toroi::SP1_TRAP_VERTICAL_ACROSS_DURATION = (double)(Field::PIXEL_SIZE_Y / Toroi::SP1_TRAP_ACROSS_SPEED) * 1000;		// [ミリ秒]
const unsigned char Toroi::SP1_TRAP_ACROSS_LANES = 4;

const unsigned int Toroi::SP3_GHOSTS_EMIT_INTERVAL = 3000;

const unsigned int Toroi::SP5_RAIN_INTERVAL = 250;						// SP5の躁鬱雨の発射間隔(共通)[ミリ秒]
const double Toroi::SP5_RAIN_SOU_GENERATED_Y = -100;					// SP5の躁雨が生成されるY座標(画面外下)
const double Toroi::SP5_RAIN_UTU_GENERATED_Y = 842;						// SP5の鬱雨が生成されるY座標(画面外上)
const unsigned int Toroi::SP5_RAIN_SPEED = 300;							// SP5の躁鬱雨の速度(共通)
const unsigned int Toroi::SP5_RAIN_COLLIDANT_SIZE = 10;					// SP5の躁鬱雨の当たり判定サイズ(共通)
const unsigned int Toroi::SP5_HEART_INTERVAL = 3000;					// SP5のハート弾の発射間隔[ミリ秒]
const double Toroi::SP5_HEART_GENERATED_TOP_Y = 842;					// SP5のハート弾が生成されるY座標(画面外上)
const double Toroi::SP5_HEART_GENERATED_BOTTOM_Y = -100;				// SP5のハート弾が生成されるY座標(画面外下)
const double Toroi::SP5_HEART_GENERATED_LEFT_X = -100;					// SP5のハート弾が生成されるY座標(画面外左)
const double Toroi::SP5_HEART_GENERATED_RIGHT_X = 720;					// SP5のハート弾が生成されるY座標(画面外右)
const double Toroi::SP5_HEART_SPEED = 400;								// SP5のハート弾の速度
const unsigned int Toroi::SP5_HEART_COLLIDANT_SIZE = 10;				// SP5のハート弾の当たり判定サイズ

const unsigned int Toroi::SP6_RAN_NOZZLE_INIT_RADIUS = 800;				// SP6のRANの回転ノズルの発射点の初期半径
const unsigned int Toroi::SP6_RAN_MAIN_NOZZLES_AMOUNT = 8;				// SP6のRANのノズル(大)の数
const unsigned int Toroi::SP6_RAN_SUB_NOZZLES_AMOUNT = 4;				// SP6のRANのノズル(小)の数
const double Toroi::SP6_RAN_SUB_NOZZLES_ROTATE_SPEED = 1.0 / 2.0 * pi;	// SP6のRANのノズル(小)の回転速度
const unsigned int Toroi::SP6_RAN_SHOT_INTERVAL = 300;					// SP6のRANのノズル(小)からのショットの発射間隔
const double Toroi::SP6_RAN_SHOT_SPEED = 200;							// SP6のRANのノズル(小)からのショットの速度
const unsigned int Toroi::SP6_RAN_SHOT_COLLIDANT_SIZE = 10;				// SP6のRANのノズル(小)からのショットの当たり判定サイズ
const unsigned int Toroi::SP6_RAN_CONTRACTION_SPEED = 50;				// SP6のRANの円の収縮速度[ピクセル/秒]

const unsigned int Toroi::SP6_RU_INITAL_LIMITED_TIME = 3000;			// SP6のRUの準備の制限時間[ミリ秒]
const unsigned int Toroi::SP6_RU_LIMITED_TIME = 10000;					// SP6のRUの制限時間[ミリ秒]
const unsigned int Toroi::SP6_RU_POTATO_INTERVAL = 40;					// SP6のRUのポテト弾の発射間隔[ミリ秒]
const double Toroi::SP6_RU_POTATO_GENERATED_Y = 842;					// SP6のRUのポテト弾が生成されるY座標(画面外上)
const unsigned int Toroi::SP6_RU_POTATO_SPEED = 600;					// SP6のRUのポテト弾の速度
const unsigned int Toroi::SP6_RU_POTATO_COLLIDANT_SIZE = 10;			// SP6のRUのポテト弾の当たり判定サイズ
const unsigned int Toroi::SP6_RU_TOMATO_TICK_INTERVAL = 100;			// SP6のRUのトマト弾の連射(小)間隔[ミリ秒]
const unsigned int Toroi::SP6_RU_TOMATO_FIRE_INTERVAL = 300;			// SP6のRUのトマト弾の連射(大)間隔[ミリ秒]
const unsigned int Toroi::SP6_RU_TOMATO_SPEED = 400;					// SP6のRUのトマト弾の速度
const unsigned int Toroi::SP6_RU_TOMATO_COLLIDANT_SIZE = 20;			// SP6のRUのトマト弾の当たり判定サイズ
const unsigned int Toroi::SP6_RU_TOMATO_NOZZLES = 16;					// SP6のRUのトマト弾のノズル数
const unsigned int Toroi::SP6_RU_TOMATO_TICK_COUNT_MAX = 3;				// SP6のRUのトマト弾の連射(小)の最大連射回数

const unsigned int Toroi::SP6_POSE_RAN_A_X_LEFT = 350;					// SP6のポーズのラン1回目のX座標(左)
const unsigned int Toroi::SP6_POSE_RAN_A_X_RIGHT = 350;					// SP6のポーズのラン1回目のX座標(右)
const unsigned int Toroi::SP6_POSE_RAN_A_Y = 160;						// SP6のポーズのラン1回目のY座標(共通)
const unsigned int Toroi::SP6_POSE_RAN_A_EXTRATE = 1.0;					// SP6のラン1回目のポーズの拡大率
const double Toroi::SP6_POSE_RAN_A_RADIAN_LEFT = 1.0 / 4.0 * pi;		// SP6のラン1回目のポーズの右の角度
const double Toroi::SP6_POSE_RAN_A_RADIAN_RIGHT = 3.0 / 4.0 * pi;		// SP6のラン1回目のポーズの左の角度
const unsigned int Toroi::SP6_POSE_RAN_B_X_LEFT = 350 + 30;				// SP6のポーズのラン2回目のX座標(左)
const unsigned int Toroi::SP6_POSE_RAN_B_X_RIGHT = 350 - 30;			// SP6のポーズのラン2回目のX座標(右)
const unsigned int Toroi::SP6_POSE_RAN_B_Y = 160;						// SP6のポーズのラン2回目のY座標(共通)
const unsigned int Toroi::SP6_POSE_RAN_B_EXTRATE = 1.0;					// SP6のラン2回目のポーズの拡大率
const double Toroi::SP6_POSE_RAN_B_RADIAN_LEFT = 1.0 / 4.0 * pi;		// SP6のラン2回目のポーズの右の角度
const double Toroi::SP6_POSE_RAN_B_RADIAN_RIGHT = 3.0 / 4.0 * pi;		// SP6のラン2回目のポーズの左の角度
const unsigned int Toroi::SP6_POSE_RU_X_LEFT = 350 - 40;				// SP6のポーズのルーのX座標(左)
const unsigned int Toroi::SP6_POSE_RU_X_RIGHT = 350 + 40;				// SP6のポーズのルーのX座標(右)
const unsigned int Toroi::SP6_POSE_RU_Y = 80;							// SP6のポーズのルーのY座標(共通)
const unsigned int Toroi::SP6_POSE_RU_EXTRATE = 1.0;					// SP6のルーのポーズの拡大率
const double Toroi::SP6_POSE_RU_RADIAN_LEFT = 2.0 / 4.0 * pi;			// SP6のルーのポーズの右の角度
const double Toroi::SP6_POSE_RU_RADIAN_RIGHT = 2.0 / 4.0 * pi;			// SP6のルーのポーズの左の角度



const unsigned int Toroi::INITIAL_HP = 1000;

// 100% -  92% NORMAL1
//  92% -  82% SP1
//  82% -  75% NORMAL2
//  75% -  65% SP2
//  65% -  55% SP3
//  55% -  48% NORMAL3
//  48% -  38% SP4
//  38% -  28% SP5
//  28% -  21% NORMAL4
//  21% -  11% SP6
//  11% -   0% SP7

const double Toroi::NM1_ACTIVATE_HP_RATIO = 100.0 / 100.0;
const double Toroi::SP1_ACTIVATE_HP_RATIO = 92.0 / 100.0;
const double Toroi::NM2_ACTIVATE_HP_RATIO = 82.0 / 100.0;
const double Toroi::SP2_ACTIVATE_HP_RATIO = 75.0 / 100.0;
const double Toroi::SP3_ACTIVATE_HP_RATIO = 65.0 / 100.0;
const double Toroi::NM3_ACTIVATE_HP_RATIO = 55.0 / 100.0;
const double Toroi::SP4_ACTIVATE_HP_RATIO = 48.0 / 100.0;
const double Toroi::SP5_ACTIVATE_HP_RATIO = 38.0 / 100.0;
const double Toroi::NM4_ACTIVATE_HP_RATIO = 28.0 / 100.0;
const double Toroi::SP6_ACTIVATE_HP_RATIO = 21.0 / 100.0;
const double Toroi::SP7_ACTIVATE_HP_RATIO = 11.0 / 100.0;

const unsigned int Toroi::CRUSH_BONUS = 1000000;
const unsigned int Toroi::SP1_ACCOMPLISH_BONUS = 150000;
const unsigned int Toroi::SP2_ACCOMPLISH_BONUS = 200000;
const unsigned int Toroi::SP3_ACCOMPLISH_BONUS = 200000;
const unsigned int Toroi::SP4_ACCOMPLISH_BONUS = 350000;
const unsigned int Toroi::SP5_ACCOMPLISH_BONUS = 350000;
const unsigned int Toroi::SP6_ACCOMPLISH_BONUS = 500000;
const unsigned int Toroi::SP7_ACCOMPLISH_BONUS = 1000000;


Toroi::Toroi() :
	Character(
		CharacterID::TOROI,
		INITIAL_POS_X,
		INITIAL_POS_Y,
		INITIAL_HP,
		make_unique<CollideCircle>(INITIAL_POS_X, INITIAL_POS_Y, INITIAL_COLLIDANT_SIZE)
	),
	BossCharacter(NAME, INITIAL_HP, CRUSH_BONUS),
	nm2_mode(ToroiNM2Mode::WARNING),
	nm2_lasercount(0),
	nm2_laser_shot_count(0),
	nm2_random_num(0),
	nm3_status(ToroiNm3Status::INITIAL),
	nm3_parasol_rain_last_emitted_clock(0),
	nm4_color_flag(ToroiNM4ColorFlag::RED),
	nm4_last_generated_clock(0),
	sp1_mode(ToroiSP1Mode::INITIAL),
	sp1_last_questioned_clock(0),
	sp1_trick_last_started_clock(0),
	sp1_trick_last_emitted_clock(0),
	sp1_trick_nozzle_rotate_arg(0.0),
	sp1_treat_last_started_clock(0),
	sp1_treat_last_threw_clock(0),
	sp1_trap_phase(1),
	sp1_trap_last_across_started_clock(0),
	sp1_trap_last_shot_clock(0),
	sp3_status(ToroiSP3Status::STEP1_INIT),
	sp3_last_step_advanced_clock(0),
	sp3_step1_slash_laser_id(0),
	sp3_step2_last_ghost_emitted_clock(0),
	sp3_step3_slash_laser_id(0),
	sp5_rain_last_generated_clock(0),
	sp5_heart_last_generated_clock(0),
	sp6_mode(ToroiSP6Mode::RAN_A_INITIAL),
	sp6_ran_nozzle_radius(0.0),
	sp6_ran_count(0),
	sp6_ru_inital_started_clock(0),
	sp6_ru_started_clock(0),
	sp6_ru_potato_last_generated_clock(0),
	sp6_ru_tomato_tick_last_generated_clock(0),
	sp6_ru_tomato_fire_last_generated_clock(0),
	sp6_ru_tomato_tick_count(0)
{
	STATUS = ToroiStatus::PREPARE;	// どこを開始地点とするか
	for (int i = 0; i < 44; ++i) {
		nm2_laser_id[i] = 0;
	}
	switch (STATUS) {
	case ToroiStatus::PREPARE:
		hp = INITIAL_HP;
		break;
	case ToroiStatus::NORMAL1:
		hp = INITIAL_HP;
		break;
	case ToroiStatus::SP1:
		hp = INITIAL_HP * SP1_ACTIVATE_HP_RATIO;
		break;
	case ToroiStatus::NORMAL2:
		hp = INITIAL_HP * NM2_ACTIVATE_HP_RATIO;
		break;
	case ToroiStatus::SP2:
		hp = INITIAL_HP * SP2_ACTIVATE_HP_RATIO;
		break;
	case ToroiStatus::SP3:
		hp = INITIAL_HP * SP3_ACTIVATE_HP_RATIO;
		break;
	case ToroiStatus::NORMAL3:
		hp = INITIAL_HP * NM3_ACTIVATE_HP_RATIO;
		break;
	case ToroiStatus::SP4:
		hp = INITIAL_HP * SP4_ACTIVATE_HP_RATIO;
		break;
	case ToroiStatus::SP5:
		hp = INITIAL_HP * SP5_ACTIVATE_HP_RATIO;
		break;
	case ToroiStatus::NORMAL4:
		hp = INITIAL_HP * NM4_ACTIVATE_HP_RATIO;
		break;
	case ToroiStatus::SP6:
		hp = INITIAL_HP * SP6_ACTIVATE_HP_RATIO;
		break;
	case ToroiStatus::SP7:
		hp = INITIAL_HP * SP7_ACTIVATE_HP_RATIO;
		break;
	default:
		break;
	}
}


void Toroi::update() {
	switch (STATUS) {
	case ToroiStatus::PREPARE:
		STATUS = ToroiStatus::NORMAL1;
		break;

	case ToroiStatus::NORMAL1:
		nm1();
		break;

	case ToroiStatus::SP1:		// 「Trick or Treat or Trap?」
		sp1();
		break;

	case ToroiStatus::NORMAL2:
		nm2();
		break;

	case ToroiStatus::SP2:		// 「慈子欺瞞クリーナー」
		sp2();
		break;

	case ToroiStatus::SP3:		// 「赤き怨みは稲穂を揺らす」
		sp3();
		break;

	case ToroiStatus::NORMAL3:
		nm3();
		break;

	case ToroiStatus::SP4:		// 「咲き誇れ、血染めの梅」
		sp4();
		break;

	case ToroiStatus::SP5:		// 「インターネット再興」
		sp5();
		break;

	case ToroiStatus::NORMAL4:
		nm4();
		break;

	case ToroiStatus::SP6:		// 「Ex-tROiA.ru4(D)」
		sp6();
		break;

	case ToroiStatus::SP7:		// 「限りなく降り注ぐ、嬰怨の涙」
		sp7();
		break;
	}
	collidant->update(position);
	last_updated_clock = DxLib::GetNowHiPerformanceCount();
}


void Toroi::draw() {
	draw_hp_donut();
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_TOROI, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}


void Toroi::nm1() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP1_ACTIVATE_HP_RATIO) {

	}
	else {
		STATUS = ToroiStatus::SP1;
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(L"「Trick or Treat or Trap?」"));
	}
}


void Toroi::nm2() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP2_ACTIVATE_HP_RATIO) {
		int nm2_laser_elaspsed_time = DxLib::GetNowCount() - nm2_laser_kept_clock;
		if (nm2_mode == ToroiNM2Mode::WARNING) {//アンチ出すよ
			if (nm2_laser_notify_count == 0) {
				nm2_random_num = DxLib::GetRand(32) + 1;
				nm2_laser_arg = 20.0/24 * pi+1.0 / 24.0 * nm2_random_num * pi;
				nm2_notifyarg1 = nm2_laser_arg + 1.0 / 12 * pi;
				nm2_notifyarg2 = nm2_laser_arg - 1.0 / 12 * pi + 2.0*pi;

			}
			double nm2_laser_notify_end_x1 = position->x + cos(nm2_notifyarg1) * NM2_LASER_LENGTH;	// InFieldPositionで終端座標の算出
			double nm2_laser_notify_end_y1 = position->y + sin(nm2_notifyarg1) * NM2_LASER_LENGTH;
			double nm2_laser_notify_end_x2 = position->x + cos(nm2_notifyarg2) * NM2_LASER_LENGTH;
			double nm2_laser_notify_end_y2 = position->y + sin(nm2_notifyarg2) * NM2_LASER_LENGTH;
			InFieldPosition position_end1(nm2_laser_notify_end_x1, nm2_laser_notify_end_y1);
			InFieldPosition position_end2(nm2_laser_notify_end_x2, nm2_laser_notify_end_y2);

			Position draw_position_begin = position->get_draw_position();				// InFieldPostionからPositionに変換
			Position draw_position_end1 = position_end1.get_draw_position();
			Position draw_position_end2 = position_end2.get_draw_position();

			unsigned int NM2_LASER_NOTIFY_COLOR = (GetColor(255, 0, 255));				// 予告線の色指定

			DxLib::DrawLine(	//　予告線を描画1
				draw_position_begin.x,
				draw_position_begin.y,
				draw_position_end1.x,
				draw_position_end1.y,
				NM2_LASER_NOTIFY_COLOR
			);
			DxLib::DrawLine(	//　予告線を描画2
				draw_position_begin.x,
				draw_position_begin.y,
				draw_position_end2.x,
				draw_position_end2.y,
				NM2_LASER_NOTIFY_COLOR
			);
			++nm2_laser_notify_count;
			if (nm2_laser_elaspsed_time > 1200) {
				nm2_mode = ToroiNM2Mode::NOTIFY;
				nm2_laser_notify_count = 0;
				nm2_laser_kept_clock = DxLib::GetNowCount();
			}
		}
		else if (nm2_mode == ToroiNM2Mode::NOTIFY) {	//予告線出すよ
			if (nm2_laser_notify_count == 0) {
				nm2_laser_arg = 20.0/24*pi+1.0 / 24.0 * nm2_random_num * pi;
				nm2_notifyarg1 = nm2_laser_arg + 1.0 / 12 * pi;
				nm2_notifyarg2 = nm2_laser_arg - 1.0 / 12 * pi + 2.0 * pi;

			}

			nm2_shot_arg_yellow = nm2_notifyarg1 + 1.0 / 24 * pi;
			double nm2_laser_notify_end_x1 = position->x + cos(nm2_notifyarg1) * NM2_LASER_LENGTH;	// InFieldPositionで終端座標の算出
			double nm2_laser_notify_end_y1 = position->y + sin(nm2_notifyarg1) * NM2_LASER_LENGTH;
			double nm2_laser_notify_end_x2 = position->x + cos(nm2_notifyarg2) * NM2_LASER_LENGTH;
			double nm2_laser_notify_end_y2 = position->y + sin(nm2_notifyarg2) * NM2_LASER_LENGTH;
			InFieldPosition position_end1(nm2_laser_notify_end_x1, nm2_laser_notify_end_y1);
			InFieldPosition position_end2(nm2_laser_notify_end_x2, nm2_laser_notify_end_y2);

			Position draw_position_begin = position->get_draw_position();				// InFieldPostionからPositionに変換
			Position draw_position_end1 = position_end1.get_draw_position();
			Position draw_position_end2 = position_end2.get_draw_position();

			unsigned int NM2_LASER_NOTIFY_COLOR = (GetColor(255, 0, 255));				// 予告線の色指定

			DxLib::DrawLine(	//　予告線を描画1
				draw_position_begin.x,
				draw_position_begin.y,
				draw_position_end1.x,
				draw_position_end1.y,
				NM2_LASER_NOTIFY_COLOR
			);
			DxLib::DrawLine(	//　予告線を描画2
				draw_position_begin.x,
				draw_position_begin.y,
				draw_position_end2.x,
				draw_position_end2.y,
				NM2_LASER_NOTIFY_COLOR
			);
			++nm2_laser_notify_count;
			for (int i = 0; i < LASERNOZZLES+1;++i) {
				double nm2_laser_notify_end_x = position->x + cos(nm2_shot_arg_yellow) * NM2_LASER_LENGTH;	// InFieldPositionで終端座標の算出
				double nm2_laser_notify_end_y = position->y + sin(nm2_shot_arg_yellow) * NM2_LASER_LENGTH;
				InFieldPosition position_end(nm2_laser_notify_end_x, nm2_laser_notify_end_y);

				Position draw_position_begin = position->get_draw_position();				// InFieldPostionからPositionに変換
				Position draw_position_end = position_end.get_draw_position();

				unsigned int NM2_LASER_NOTIFY_COLOR = (GetColor(255, 255, 0));

				DxLib::DrawLine(	//　予告線を描画
					draw_position_begin.x,
					draw_position_begin.y,
					draw_position_end.x,
					draw_position_end.y,
					NM2_LASER_NOTIFY_COLOR
				);
				nm2_shot_arg_yellow += 1.0 / 24 * pi;
			}
			if (nm2_laser_elaspsed_time > 2000) {
				nm2_laser_notify_count = 0;
				nm2_mode = ToroiNM2Mode::SHOT;
				nm2_laser_kept_clock = DxLib::GetNowCount();
			}
		}
		else if (nm2_mode == ToroiNM2Mode::SHOT) {
			if (nm2_lasercount == 0) {
				nm2_laser_arg = nm2_notifyarg1+1.0/24*pi;
				for (int i = 0; i < LASERNOZZLES+2; ++i) {
					nm2_laser_id[i] = Laser::GENERATE_ID();
					(*Field::ENEMY_LASERS)[nm2_laser_id[i]] = make_unique<PolarLaser>(
						position->x,
						position->y,
						nm2_laser_arg,
						NM2_LASER_LENGTH,
						NM2_LASER_WIDTH,
						10.0,
						true,
						SkinID::TOROI_NM2LASER_RED
					);
					nm2_laser_arg += 1.0 / 24 * pi;
					++nm2_laser_shot_count;
				}
				nm2_lasercount += 1;
			}
			if (nm2_laser_elaspsed_time > 5000) {
				nm2_lasercount = 0;
				for (int i = 0; i < LASERNOZZLES+2; ++i) {
					(*Field::ENEMY_LASERS).erase(nm2_laser_id[i]);
				}
				nm2_mode = ToroiNM2Mode::WARNING;
				nm2_laser_kept_clock = DxLib::GetNowCount();
			}
		}

	}
	else {
		STATUS = ToroiStatus::SP2;
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP2_NAME));
		for (int i = 0; i < LASERNOZZLES+2; ++i) {
			(*Field::ENEMY_LASERS).erase(nm2_laser_id[i]);
		}
	}
}


void Toroi::nm3() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP4_ACTIVATE_HP_RATIO) {
		switch (nm3_status) {
		case ToroiNm3Status::INITIAL:
		{
			BulletID temp_id = Bullet::GENERATE_ID();
			(*Field::ENEMY_BULLETS)[temp_id] = make_unique<DVDShot>(
				position->x,
				position->y,
				1.0 / 18.0 * pi * DxLib::GetRand(18) + 1.0 / 2.0 * pi
			);
			nm3_dvd_shot_ids.push_back(temp_id);

			temp_id = Bullet::GENERATE_ID();
			(*Field::ENEMY_BULLETS)[temp_id] = make_unique<DVDShot>(
				position->x,
				position->y,
				1.0 / 18.0 * pi * DxLib::GetRand(18) + 1.0 / 2.0 * pi
			);
			nm3_dvd_shot_ids.push_back(temp_id);

			temp_id = Bullet::GENERATE_ID();
			(*Field::ENEMY_BULLETS)[temp_id] = make_unique<DVDShot>(
				position->x,
				position->y,
				1.0 / 18.0 * pi * DxLib::GetRand(18) - 1.0 / 2.0 * pi
			);
			nm3_dvd_shot_ids.push_back(temp_id);

			temp_id = Bullet::GENERATE_ID();
			(*Field::ENEMY_BULLETS)[temp_id] = make_unique<DVDShot>(
				position->x,
				position->y,
				1.0 / 18.0 * pi * DxLib::GetRand(18) - 1.0 / 2.0 * pi
			);
			nm3_dvd_shot_ids.push_back(temp_id);

			nm3_status = ToroiNm3Status::WAIT;
			break;
		}
		case ToroiNm3Status::WAIT:
			int elapsed_time_since_last_emit = DxLib::GetNowCount() - nm3_parasol_rain_last_emitted_clock;
			if (elapsed_time_since_last_emit > NM3_PARASOL_RAIN_INTERVAL) {
				for (int i = 0; i < NM3_PARASOL_RAIN_LANE_COUNT; ++i) {
					(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<ParabolicShot>(
						position->x,
						position->y,
						1.0 / NM3_PARASOL_RAIN_LANE_COUNT * pi * i + pi + 1.0 / NM3_PARASOL_RAIN_LANE_COUNT / 2.0 * pi,
						NM3_PARASOL_RAIN_THROW_SPEED,
						NM3_PARASOL_RAIN_GRAVITY_ACCEL,
						-1.0 / 2.0 * pi,
						NM3_PARASOL_RAIN_COLLIDANT_SIZE,
						1,
						SkinID::TOROI_NM3_PARASOL_RAIN
					);
				}
				nm3_parasol_rain_last_emitted_clock = DxLib::GetNowCount();
			}
			break;
		}
	}
	else {
		for (const auto& nm3_dvd_shot_id : nm3_dvd_shot_ids) {
			Field::ENEMY_BULLETS->erase(nm3_dvd_shot_id);
		}
		STATUS = ToroiStatus::SP4;
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP4_NAME));
	}
}


void Toroi::nm4() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP6_ACTIVATE_HP_RATIO) {
		int nm4_generated_delta_time = DxLib::GetNowCount() - nm4_last_generated_clock;
		if (nm4_generated_delta_time > NM4_INTERVAL) {
			if (nm4_color_flag == ToroiNM4ColorFlag::RED) {
				for (int j = 0; j < 12; ++j) {
					for (int i = 0; i < 5; ++i) {
						double theta = 2.0 * pi / 120 * i + (1.0 / 6.0 * pi * j);
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(	// RED_BIG
							position->x,
							position->y,
							theta,
							NM4_SPEED,
							NM4_COLLIDANT_SIZE_BIG,
							1,
							SkinID::TOROI_NM4_RED_BIG
						);
					}
					for (int i = 0; i < 3; ++i) {
						double theta = 2.0 * pi / 240 * i + (1.0 / 6.0 * pi * j) - 2.0 / 36.0 * pi;
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(	// RED_SMALL
							position->x,
							position->y,
							theta,
							NM4_SPEED,
							NM4_COLLIDANT_SIZE_SMALL,
							1,
							SkinID::TOROI_NM4_RED_SMALL
						);
					}
				}
				nm4_color_flag = ToroiNM4ColorFlag::BLUE;
			}
			else if (nm4_color_flag == ToroiNM4ColorFlag::BLUE) {
				for (int j = 0; j < 12; ++j) {
					for (int i = 0; i < 5; ++i) {
						double theta = 2.0 * pi / 120 * i + (1.0 / 6.0 * pi * j) - 1.0 / 12.0 * pi;
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(	// BLUE_BIG
							position->x,
							position->y,
							theta,
							NM4_SPEED,
							NM4_COLLIDANT_SIZE_BIG,
							1,
							SkinID::TOROI_NM4_BLUE_BIG
						);
					}
					for (int i = 0; i < 3; ++i) {
						double theta = 2.0 * pi / 240 * i + (1.0 / 6.0 * pi * j) - 5.0 / 36.0 * pi;
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(	// BLUE_SMALL
							position->x,
							position->y,
							theta,
							NM4_SPEED,
							NM4_COLLIDANT_SIZE_SMALL,
							1,
							SkinID::TOROI_NM4_BLUE_SMALL
						);
					}
				}
				nm4_color_flag = ToroiNM4ColorFlag::RED;
			}
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			nm4_last_generated_clock = DxLib::GetNowCount();
		}
		if (nm4_generated_delta_time > NM4_INTERVAL) {

		}
	}
	else {
		STATUS = ToroiStatus::SP6;
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP6_NAME));
	}
}


void Toroi::sp1(){		// 「Trick or Treat or Trap?」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * NM2_ACTIVATE_HP_RATIO) {
		switch (sp1_mode) {
		case ToroiSP1Mode::INITIAL: {
			sp1_last_questioned_clock = DxLib::GetNowCount();
			sp1_mode = ToroiSP1Mode::QUESTIONING;
			break;
		}
		case ToroiSP1Mode::QUESTIONING: {
			int elapsed_time = DxLib::GetNowCount() - sp1_last_questioned_clock;
			if (elapsed_time < SP1_THINKING_TIME_LENGTH) {
				InFieldPosition start_pos(
					InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0,
					InFieldPosition::MAX_MOVABLE_BOUNDARY_Y
				);
				InFieldPosition end_pos(
					InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0,
					InFieldPosition::MIN_MOVABLE_BOUNDARY_Y
				);
				DxLib::DrawLine(
					start_pos.get_draw_position().x,
					start_pos.get_draw_position().y,
					end_pos.get_draw_position().x,
					end_pos.get_draw_position().y,
					Colors::RED,
					1
				);
				InFieldPosition t_or_t_pos(
					InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0 - 88.0,
					InFieldPosition::MAX_MOVABLE_BOUNDARY_Y / 2.0 + 150.0
				);
				DxLib::DrawFormatString(
					t_or_t_pos.get_draw_position().x,
					t_or_t_pos.get_draw_position().y,
					Colors::YELLOW,
					L"← Trick or Treat? →"
				);
				double thinking_time_left = (double)(SP1_THINKING_TIME_LENGTH - elapsed_time) / 1000.0;
				InFieldPosition countdown_pos(
					InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0 - 45.0,
					InFieldPosition::MAX_MOVABLE_BOUNDARY_Y / 2.0 + 20.0
				);
				DxLib::DrawFormatStringToHandle(
					countdown_pos.get_draw_position().x,
					countdown_pos.get_draw_position().y,
					Colors::YELLOW,
					FontHandles::DSEG14,
					L"%.1lf",
					thinking_time_left
				);
			}
			else {
				InFieldPosition mychr_pos = *(Field::MY_CHARACTER->position);
				if (mychr_pos.x < InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0) {
					sp1_mode = ToroiSP1Mode::TRICK;
					sp1_trick_last_started_clock = DxLib::GetNowCount();
					sp1_trick_nozzle_rotate_arg = 0.0;
				}
				else {
					sp1_mode = ToroiSP1Mode::TREAT;
					sp1_treat_last_started_clock = DxLib::GetNowCount();
				}
			}
			break;
		}
		case ToroiSP1Mode::TRICK: {
			int elapsed_time_since_last_started = DxLib::GetNowCount() - sp1_trick_last_started_clock;
			sp1_trick_nozzle_rotate_arg += SP1_TRICK_NOZZLE_ROTATE_SPEED * update_delta_time / 1000 / 1000;
			if (elapsed_time_since_last_started < SP1_TRICK_DURATION) {
				int elapsed_time_since_last_emitted = DxLib::GetNowCount() - sp1_trick_last_emitted_clock;
				if (elapsed_time_since_last_emitted > SP1_TRICK_SHOT_INTERVAL) {
					for (int i = 0; i < SP1_TRICK_NOZZLES; ++i) {

						double theta = 2 * pi / SP1_TRICK_NOZZLES * i + sp1_trick_nozzle_rotate_arg;
						double emit_x = position->x + SP1_TRICK_NOZZLE_RADIUS * cos(theta);
						double emit_y = position->y + SP1_TRICK_NOZZLE_RADIUS * sin(theta);
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<CurvingShot>(
							emit_x,
							emit_y,
							theta,
							SP1_TRICK_SHOT_SPEED,
							(1.0 / 12.0) * pi,
							SP1_TRICK_SHOT_COLLIDANT_SIZE,
							1,
							SkinID::TOROI_SP1_TRICK
						);
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<CurvingShot>(
							emit_x,
							emit_y,
							theta,
							SP1_TRICK_SHOT_SPEED,
							-(1.0 / 12.0) * pi,
							SP1_TRICK_SHOT_COLLIDANT_SIZE,
							1,
							SkinID::TOROI_SP1_TRICK
						);
					}
					sp1_trick_last_emitted_clock = DxLib::GetNowCount();
				}
			}
			else
				sp1_mode = ToroiSP1Mode::TRAP_INIT;
			break;
		}
		case ToroiSP1Mode::TREAT: {
			int elapsed_time_since_last_started = DxLib::GetNowCount() - sp1_treat_last_started_clock;
			if (elapsed_time_since_last_started < SP1_TREAT_DURATION) {
				int elapsed_time_since_last_threw = DxLib::GetNowCount() - sp1_treat_last_threw_clock;
				if (elapsed_time_since_last_threw > SP1_TREAT_THROW_INTERVAL) {
					for (int i = 0; i < SP1_TREAT_THROW_AMOUNT; ++i) {
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<ParabolicShot>(
							position->x,
							position->y,
							static_cast<double>(DxLib::GetRand(96)) / 96.0 * pi,
							DxLib::GetRand(300),
							150.0,
							-1.0 / 2.0 * pi,
							10,
							1,
							SkinID::TOROI_SP1_TREAT
						);
					}
					sp1_treat_last_threw_clock = DxLib::GetNowCount();
				}
			}
			else
				sp1_mode = ToroiSP1Mode::TRAP_INIT;
			break;
		}
		case ToroiSP1Mode::TRAP_INIT: {
			sp1_trap_phase = 1;
			sp1_mode = ToroiSP1Mode::TRAP_ACROSS_INIT;
		}
		case ToroiSP1Mode::TRAP_ACROSS_INIT: {
			sp1_trap_last_across_started_clock = DxLib::GetNowCount();
			sp1_mode = ToroiSP1Mode::TRAP;
			break;
		}
		case ToroiSP1Mode::TRAP: {		// (2), (4), (6), (8) 縦によぎる

			int across_delta_time = DxLib::GetNowCount() - sp1_trap_last_across_started_clock;
			int shot_delta_time = DxLib::GetNowCount() - sp1_trap_last_shot_clock;

			if (sp1_trap_phase > SP1_TRAP_ACROSS_LANES * 2) {
				sp1_mode = ToroiSP1Mode::INITIAL;
			}
			else if(sp1_trap_phase % 2 == 0){
				if (across_delta_time < SP1_TRAP_VERTICAL_ACROSS_DURATION) {
					if (shot_delta_time > SP1_TRAP_SHOT_INTERVAL) {
						int left_nozzle_x = (Field::PIXEL_SIZE_X / (SP1_TRAP_ACROSS_LANES * 2 + 1)) * sp1_trap_phase / 2;
						int left_nozzle_y = SP1_TRAP_ACROSS_SPEED * across_delta_time / 1000;
						double left_shot_arg = (double)DxLib::GetRand(72) / 72.0 * 2 * pi;
						double left_shot_speed = DxLib::GetRand(250) + 50;
						int right_nozzle_x = (Field::PIXEL_SIZE_X / (SP1_TRAP_ACROSS_LANES * 2 + 1)) * (SP1_TRAP_ACROSS_LANES * 2 + 1 - sp1_trap_phase / 2);
						int right_nozzle_y = Field::PIXEL_SIZE_Y - SP1_TRAP_ACROSS_SPEED * across_delta_time / 1000;
						double right_shot_arg = (double)DxLib::GetRand(72) / 72.0 * 2 * pi;
						double right_shot_speed = DxLib::GetRand(250) + 50;
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
							left_nozzle_x,
							left_nozzle_y,
							left_shot_arg,
							left_shot_speed,
							SP1_TRAP_SHOT_COLLIDANT_SIZE,
							1,
							SkinID::TOROI_SP1_TRAP
						);
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
							right_nozzle_x,
							right_nozzle_y,
							right_shot_arg,
							right_shot_speed,
							SP1_TRAP_SHOT_COLLIDANT_SIZE,
							1,
							SkinID::TOROI_SP1_TRAP
						);
						sp1_trap_last_shot_clock = DxLib::GetNowCount();
					}
				}
				else {
					++sp1_trap_phase;
					sp1_mode = ToroiSP1Mode::TRAP_ACROSS_INIT;
				}

			}
			else {		// (1), (3), (5), (7) 横によぎる
				if (across_delta_time < SP1_TRAP_HORIZONTAL_ACROSS_DURATION) {
					if (shot_delta_time > SP1_TRAP_SHOT_INTERVAL) {
						int upper_nozzle_x = SP1_TRAP_ACROSS_SPEED * across_delta_time / 1000;
						int upper_nozzle_y = (Field::PIXEL_SIZE_Y / (SP1_TRAP_ACROSS_LANES * 2 + 1)) * (SP1_TRAP_ACROSS_LANES * 2 + 1 - sp1_trap_phase / 2);
						double upper_shot_arg = (double)DxLib::GetRand(72) / 72.0 * pi;
						double upper_shot_speed = DxLib::GetRand(250) + 50;
						int lower_nozzle_x = Field::PIXEL_SIZE_X - SP1_TRAP_ACROSS_SPEED * across_delta_time / 1000;
						int lower_nozzle_y = (Field::PIXEL_SIZE_Y / (SP1_TRAP_ACROSS_LANES * 2 + 1)) * sp1_trap_phase / 2;
						double lower_shot_arg = (double)DxLib::GetRand(72) / 72.0 * pi;
						double lower_shot_speed = DxLib::GetRand(250) + 50;
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
							upper_nozzle_x,
							upper_nozzle_y,
							upper_shot_arg,
							upper_shot_speed,
							SP1_TRAP_SHOT_COLLIDANT_SIZE,
							1,
							SkinID::TOROI_SP1_TRAP
						);
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
							lower_nozzle_x,
							lower_nozzle_y,
							lower_shot_arg,
							lower_shot_speed,
							SP1_TRAP_SHOT_COLLIDANT_SIZE,
							1,
							SkinID::TOROI_SP1_TRAP
						);
						sp1_trap_last_shot_clock = DxLib::GetNowCount();
					}
				}
				else {
					++sp1_trap_phase;
					sp1_mode = ToroiSP1Mode::TRAP_ACROSS_INIT;
				}
			}
			break;
		}
		}
	}
	else {
		STATUS = ToroiStatus::NORMAL2;
	}
}


void Toroi::sp2() {		// 「慈子欺瞞クリーナー」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP3_ACTIVATE_HP_RATIO) {

	}
	else {
		STATUS = ToroiStatus::SP3;
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP3_NAME));
	}
}


void Toroi::sp3() {		// 「赤き怨みは稲穂を揺らす」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * NM3_ACTIVATE_HP_RATIO) {
		int delta_time_step_advance = DxLib::GetNowCount() - sp3_last_step_advanced_clock;
		switch (sp3_status) {
		case ToroiSP3Status::STEP1_INIT:
		{
			sp3_step1_slash_laser_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[sp3_step1_slash_laser_id] = make_unique<CartesianLaser>(
				InFieldPosition::MIN_MOVABLE_BOUNDARY_X,
				450,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_X,
				220,
				10,
				100,
				true,
				SkinID::TOROI_SP3_SLASH
			);

			LaserID temp_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[temp_id] = make_unique<CartesianLaser>(
				InFieldPosition::MIN_MOVABLE_BOUNDARY_X,
				InFieldPosition::MIN_MOVABLE_BOUNDARY_Y,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_X,
				InFieldPosition::MIN_MOVABLE_BOUNDARY_Y,
				20,
				50,
				true,
				SkinID::TOROI_SP3_BESIEGE
			);
			sp3_step1_besiege_laser_ids.push_back(temp_id);

			temp_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[temp_id] = make_unique<CartesianLaser>(
				InFieldPosition::MAX_MOVABLE_BOUNDARY_X,
				InFieldPosition::MIN_MOVABLE_BOUNDARY_Y,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_X,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_Y,
				20,
				50,
				true,
				SkinID::TOROI_SP3_BESIEGE
			);
			sp3_step1_besiege_laser_ids.push_back(temp_id);

			temp_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[temp_id] = make_unique<CartesianLaser>(
				InFieldPosition::MAX_MOVABLE_BOUNDARY_X,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_Y,
				InFieldPosition::MIN_MOVABLE_BOUNDARY_X,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_Y,
				20,
				50,
				true,
				SkinID::TOROI_SP3_BESIEGE
			);
			sp3_step1_besiege_laser_ids.push_back(temp_id);

			temp_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[temp_id] = make_unique<CartesianLaser>(
				InFieldPosition::MIN_MOVABLE_BOUNDARY_X,
				InFieldPosition::MAX_MOVABLE_BOUNDARY_Y,
				InFieldPosition::MIN_MOVABLE_BOUNDARY_X,
				InFieldPosition::MIN_MOVABLE_BOUNDARY_Y,
				20,
				50,
				true,
				SkinID::TOROI_SP3_BESIEGE
			);
			sp3_step1_besiege_laser_ids.push_back(temp_id);

			sp3_status = ToroiSP3Status::STEP1;
			sp3_last_step_advanced_clock = DxLib::GetNowCount();
			break;
		}

		case ToroiSP3Status::STEP1:
			if (delta_time_step_advance < 5000) {

			}
			else {
				Field::ENEMY_LASERS->erase(sp3_step1_slash_laser_id);
				for (const auto& laser_id : sp3_step1_besiege_laser_ids) {
					Field::ENEMY_LASERS->erase(laser_id);
				}
				sp3_status = ToroiSP3Status::STEP2_INIT;
			}
			break;

		case ToroiSP3Status::STEP2_INIT:
			for (int i = 0; i < 8; ++i) {
				BulletID ghost_id = Bullet::GENERATE_ID();
				(*Field::ENEMY_BULLETS)[ghost_id] = make_unique<StraightShot>(
					InFieldPosition::MIN_MOVABLE_BOUNDARY_X,
					(double)(Field::PIXEL_SIZE_Y - 200) / 8 * i + 200,
					0.0,
					30.0,
					15,
					1,
					SkinID::TOROI_SP3_GHOST
				);
				sp3_step2_ghost_ids.push_back(ghost_id);
			}
			for (int i = 0; i < 8; ++i) {
				BulletID ghost_id = Bullet::GENERATE_ID();
				(*Field::ENEMY_BULLETS)[ghost_id] = make_unique<StraightShot>(
					InFieldPosition::MAX_MOVABLE_BOUNDARY_X,
					(double)(Field::PIXEL_SIZE_Y - 200) / 8 * i + 200,
					pi,
					30.0,
					15,
					1,
					SkinID::TOROI_SP3_GHOST
				);
				sp3_step2_ghost_ids.push_back(ghost_id);
			}
			sp3_status = ToroiSP3Status::STEP2;
			sp3_last_step_advanced_clock = DxLib::GetNowCount();
			break;

		case ToroiSP3Status::STEP2:
			if (delta_time_step_advance < 18000) {
				int delta_time_ghost_emit = DxLib::GetNowCount() - sp3_step2_last_ghost_emitted_clock;
				if (delta_time_ghost_emit > SP3_GHOSTS_EMIT_INTERVAL) {
					for (const auto& ghost_id : sp3_step2_ghost_ids) {
						double delta_x_mychr = Field::MY_CHARACTER->position->x - position->x;
						double delta_y_mychr = Field::MY_CHARACTER->position->y - position->y;
						double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
						(*Field::ENEMY_BULLETS)[ghost_id]->arg = arg_toward_mychr;
					}
					sp3_step2_ghost_ids.clear();
					for (int i = 0; i < 8; ++i) {
						BulletID ghost_id = Bullet::GENERATE_ID();
						(*Field::ENEMY_BULLETS)[ghost_id] = make_unique<StraightShot>(
							InFieldPosition::MIN_MOVABLE_BOUNDARY_X,
							(double)(Field::PIXEL_SIZE_Y - 200) / 8 * i + 200,
							0.0,
							30.0,
							15,
							1,
							SkinID::TOROI_SP3_GHOST
						);
						sp3_step2_ghost_ids.push_back(ghost_id);
					}
					for (int i = 0; i < 8; ++i) {
						BulletID ghost_id = Bullet::GENERATE_ID();
						(*Field::ENEMY_BULLETS)[ghost_id] = make_unique<StraightShot>(
							InFieldPosition::MAX_MOVABLE_BOUNDARY_X,
							(double)(Field::PIXEL_SIZE_Y - 200) / 8 * i + 200,
							pi,
							30.0,
							15,
							1,
							SkinID::TOROI_SP3_GHOST
						);
						sp3_step2_ghost_ids.push_back(ghost_id);
					}
					sp3_step2_last_ghost_emitted_clock = DxLib::GetNowCount();
				}
			}
			else {
				sp3_last_step_advanced_clock = DxLib::GetNowCount();
				sp3_status = ToroiSP3Status::STEP3_INIT;
			}
			break;
		case ToroiSP3Status::STEP3:
			break;
		case ToroiSP3Status::STEP4:
			break;
		}
	}
	else {
		Field::ENEMY_LASERS->erase(sp3_step1_slash_laser_id);
		for (const auto& laser_id : sp3_step1_besiege_laser_ids) {
			Field::ENEMY_LASERS->erase(laser_id);
		}
		Field::ENEMY_LASERS->erase(sp3_step3_slash_laser_id);
		for (const auto& laser_id : sp3_step3_besiege_laser_ids) {
			Field::ENEMY_LASERS->erase(laser_id);
		}
		STATUS = ToroiStatus::NORMAL3;
	}
}


void Toroi::sp4() {		// 「咲き誇れ、血染めの梅」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP5_ACTIVATE_HP_RATIO) {

	}
	else {
		STATUS = ToroiStatus::SP5;
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP5_NAME));
	}
}


void Toroi::sp5() {		// 「インターネット再興」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * NM4_ACTIVATE_HP_RATIO) {
		// 躁鬱雨
		int sp5_rain_generated_delta_time = DxLib::GetNowCount() - sp5_rain_last_generated_clock;
		if (sp5_rain_generated_delta_time > SP5_RAIN_INTERVAL) {			// 発射のタイミング
			int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);
			// 躁弾
			(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
				random_x,
				SP5_RAIN_SOU_GENERATED_Y,
				1.0 / 2.0 * pi,
				SP5_RAIN_SPEED,
				SP5_RAIN_COLLIDANT_SIZE,
				1,
				SkinID::TOROI_SP5_RAIN_SOU
			);
			// 鬱弾
			random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);					// 躁弾と鬱弾の生成位置をずらす
			(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
				random_x,
				SP5_RAIN_UTU_GENERATED_Y,
				3.0 / 2.0 * pi,
				SP5_RAIN_SPEED,
				SP5_RAIN_COLLIDANT_SIZE,
				1,
				SkinID::TOROI_SP5_RAIN_UTU
			);
			sp5_rain_last_generated_clock = DxLib::GetNowCount();			// 発射したので最終発射時刻を更新
		}
		// ハート弾
		int sp5_heart_generated_delta_time = DxLib::GetNowCount() - sp5_heart_last_generated_clock;
		if (sp5_heart_generated_delta_time > SP5_HEART_INTERVAL) {
			for (int i = 0; i < 2; ++i) {
				int random_x_top = DxLib::GetRand(Field::PIXEL_SIZE_X);
				int random_x_bottom = DxLib::GetRand(Field::PIXEL_SIZE_X);
				int random_y_left = DxLib::GetRand(Field::PIXEL_SIZE_Y);
				int random_y_right = DxLib::GetRand(Field::PIXEL_SIZE_Y);
				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double delta_x_top_mychr = my_chr_pos.x - random_x_top;
				double delta_y_top_mychr = my_chr_pos.y - SP5_HEART_GENERATED_TOP_Y;
				double delta_x_bottom_mychr = my_chr_pos.x - random_x_bottom;
				double delta_y_bottom_mychr = my_chr_pos.y - SP5_HEART_GENERATED_BOTTOM_Y;
				double delta_x_left_mychr = my_chr_pos.x - SP5_HEART_GENERATED_LEFT_X;
				double delta_y_left_mychr = my_chr_pos.y - random_y_left;
				double delta_x_right_mychr = my_chr_pos.x - SP5_HEART_GENERATED_RIGHT_X;
				double delta_y_right_mychr = my_chr_pos.y - random_y_right;
				double top_arg_toward_mychr = atan2(delta_y_top_mychr, delta_x_top_mychr);				// 自機を向いた角度を生成
				double bottom_arg_toward_mychr = atan2(delta_y_bottom_mychr, delta_x_bottom_mychr);;
				double left_arg_toward_mychr = atan2(delta_y_left_mychr, delta_x_left_mychr);;
				double right_arg_toward_mychr = atan2(delta_y_right_mychr, delta_x_right_mychr);;
				SkinID random_heart_handles = SkinID::TOROI_SP5_HEART_RED;								// ImageHandlesの初期化
				// ハート弾(画面外上に生成)
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					random_x_top,
					SP5_HEART_GENERATED_TOP_Y,
					top_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				);
				// ハート弾(画面外下に生成)
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					random_x_bottom,
					SP5_HEART_GENERATED_BOTTOM_Y,
					bottom_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				);
				// ハート弾(画面外左に生成)
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					SP5_HEART_GENERATED_LEFT_X,
					random_y_left,
					left_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				);
				// ハート弾(画面外右に生成)
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					SP5_HEART_GENERATED_RIGHT_X,
					random_y_right,
					right_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				);
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			}
			sp5_heart_last_generated_clock = DxLib::GetNowCount();			// 発射したので最終発射時刻を更新
		}
	}
	else {
		STATUS = ToroiStatus::NORMAL4;
	}
}


void Toroi::sp6() {		// 「Ex-tROiA.ru4(D)」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP7_ACTIVATE_HP_RATIO) {
		switch (sp6_mode) {
		case ToroiSP6Mode::RAN_A_INITIAL: {
			sp6_ran_nozzles.clear();
			sp6_ran_nozzle_radius = SP6_RAN_NOZZLE_INIT_RADIUS;									// ノズル半径の初期化
			for (int i = 0; i < SP6_RAN_MAIN_NOZZLES_AMOUNT; ++i) {
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;						// iノズル目の角度
				double generate_x = position->x + SP6_RAN_NOZZLE_INIT_RADIUS * cos(theta);
				double generate_y = position->y + SP6_RAN_NOZZLE_INIT_RADIUS * sin(theta);
				sp6_ran_nozzles.push_back(make_unique<RotatingStraightShotEmission>(
					generate_x,
					generate_y,
					theta,
					SP6_RAN_SUB_NOZZLES_ROTATE_SPEED,
					true,
					114514,
					SP6_RAN_SUB_NOZZLES_AMOUNT,
					SP6_RAN_SHOT_INTERVAL,
					SP6_RAN_SHOT_SPEED,
					SP6_RAN_SHOT_COLLIDANT_SIZE,
					1,
					TeamID::ENEMY,
					SkinID::TOROI_SP6_RAN_A_CHEESE)
				);
			}
			sp6_mode = ToroiSP6Mode::RAN_A;
			break;
		}
		case ToroiSP6Mode::RAN_A: {		// ラン1回目
			sp6_ran_nozzle_radius -= (double)(update_delta_time * SP6_RAN_CONTRACTION_SPEED) / 1000 / 1000;		// update_delta_timeがマイクロ秒なので計算する
			for (int i = 0; i < SP6_RAN_MAIN_NOZZLES_AMOUNT; ++i) {
				if (sp6_ran_nozzle_radius < 0) {
					sp6_ran_nozzles.at(i)->pause_emitting();
					sp6_mode = ToroiSP6Mode::RAN_B_INITIAL;
				}
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;						// iノズル目の角度
				double update_x = position->x + sp6_ran_nozzle_radius * cos(theta);
				double update_y = position->y + sp6_ran_nozzle_radius * sin(theta);
				sp6_ran_nozzles.at(i)->update(update_x, update_y);
			}
			DxLib::DrawRotaGraph(																		// ラン1回目のポーズ
				SP6_POSE_RAN_A_X_LEFT,
				SP6_POSE_RAN_A_Y,
				SP6_POSE_RAN_A_EXTRATE,
				SP6_POSE_RAN_A_RADIAN_LEFT,
				ImageHandles::POTATO_BASIC,
				TRUE);
			DxLib::DrawRotaGraph(
				SP6_POSE_RAN_A_X_RIGHT,
				SP6_POSE_RAN_A_Y,
				SP6_POSE_RAN_A_EXTRATE,
				SP6_POSE_RAN_A_RADIAN_RIGHT,
				ImageHandles::POTATO_BASIC,
				TRUE);
			break;
		}
		case ToroiSP6Mode::RAN_B_INITIAL: {		// RAN_Aで使用した変数のリセット
			sp6_ran_nozzles.clear();
			sp6_ran_nozzle_radius = SP6_RAN_NOZZLE_INIT_RADIUS;									// ノズル半径の初期化
			for (int i = 0; i < SP6_RAN_MAIN_NOZZLES_AMOUNT; ++i) {
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;						// iノズル目の角度
				double generate_x = position->x + SP6_RAN_NOZZLE_INIT_RADIUS * cos(theta);
				double generate_y = position->y + SP6_RAN_NOZZLE_INIT_RADIUS * sin(theta);
				sp6_ran_nozzles.push_back(make_unique<RotatingStraightShotEmission>(
					generate_x,
					generate_y,
					theta,
					SP6_RAN_SUB_NOZZLES_ROTATE_SPEED,
					true,
					114514,
					SP6_RAN_SUB_NOZZLES_AMOUNT,
					SP6_RAN_SHOT_INTERVAL,
					SP6_RAN_SHOT_SPEED,
					SP6_RAN_SHOT_COLLIDANT_SIZE,
					1,
					TeamID::ENEMY,
					SkinID::TOROI_SP6_RAN_B_LETUS)
				);
			}
			sp6_mode = ToroiSP6Mode::RAN_B;
			break;
		}
		case ToroiSP6Mode::RAN_B: {		// ラン2回目
			sp6_ran_nozzle_radius -= (double)(update_delta_time * SP6_RAN_CONTRACTION_SPEED) / 1000 / 1000;		// update_delta_timeがマイクロ秒なので計算する
			for (int i = 0; i < SP6_RAN_MAIN_NOZZLES_AMOUNT; ++i) {
				if (sp6_ran_nozzle_radius < 0) {
					sp6_ran_nozzles.at(i)->pause_emitting();
					sp6_ru_inital_started_clock = DxLib::GetNowCount();
					sp6_mode = ToroiSP6Mode::RU_INITAL;
				}
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;						// iノズル目の角度
				double update_x = position->x + sp6_ran_nozzle_radius * cos(theta);
				double update_y = position->y + sp6_ran_nozzle_radius * sin(theta);
				sp6_ran_nozzles.at(i)->update(update_x, update_y);
			}
			DxLib::DrawRotaGraph(																		// ラン2回目のポーズ
				SP6_POSE_RAN_B_X_LEFT,
				SP6_POSE_RAN_B_Y,
				SP6_POSE_RAN_B_EXTRATE,
				SP6_POSE_RAN_B_RADIAN_LEFT,
				ImageHandles::POTATO_BASIC,
				TRUE);
			DxLib::DrawRotaGraph(
				SP6_POSE_RAN_B_X_RIGHT,
				SP6_POSE_RAN_B_Y,
				SP6_POSE_RAN_B_EXTRATE,
				SP6_POSE_RAN_B_RADIAN_RIGHT,
				ImageHandles::POTATO_BASIC,
				TRUE);
			break;
		}
		case ToroiSP6Mode::RU_INITAL: {		// ルーの準備
			sp6_ru_tomato_tick_count = 0;														// トマト弾の連射数カウントを初期化
			int sp6_ru_inital_elapsed_time = DxLib::GetNowCount() - sp6_ru_inital_started_clock;
			if (sp6_ru_inital_elapsed_time > SP6_RU_INITAL_LIMITED_TIME) {						// 時間が経過したらルーへ
				sp6_ru_started_clock = DxLib::GetNowCount();
				sp6_mode = ToroiSP6Mode::RU;
			}
			break;
		}
		case ToroiSP6Mode::RU: {		// ルー
			int sp6_ru_elapsed_time = DxLib::GetNowCount() - sp6_ru_started_clock;
			if (sp6_ru_elapsed_time > SP6_RU_LIMITED_TIME) {
				sp6_mode = ToroiSP6Mode::RAN_A_INITIAL;
			}
			// ポテト弾
			int sp6_ru_potato_generated_delta_time = DxLib::GetNowCount() - sp6_ru_potato_last_generated_clock;
			if (sp6_ru_potato_generated_delta_time > SP6_RU_POTATO_INTERVAL) {					// 発射のタイミング
				int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					random_x,
					SP6_RU_POTATO_GENERATED_Y,
					3.0 / 2.0 * pi,
					SP6_RU_POTATO_SPEED,
					SP6_RU_POTATO_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP6_RU_POTATO
				);
				sp6_ru_potato_last_generated_clock = DxLib::GetNowCount();						// 発射したので最終発射時刻を更新
			}
			//トマト弾
			int sp6_ru_tomato_fire_generated_delta_time = DxLib::GetNowCount() - sp6_ru_tomato_fire_last_generated_clock;
			if (sp6_ru_tomato_fire_generated_delta_time > SP6_RU_TOMATO_FIRE_INTERVAL) {
				int sp6_ru_tomato_tick_generated_delta_time = DxLib::GetNowCount() - sp6_ru_tomato_tick_last_generated_clock;
				if (sp6_ru_tomato_tick_generated_delta_time > SP6_RU_TOMATO_TICK_INTERVAL) {
					for (int i = 0; i < SP6_RU_TOMATO_NOZZLES; ++i) {							// ノズル数分繰り返して全方位弾を作る
						double theta = 2 * pi / SP6_RU_TOMATO_NOZZLES * i;
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
							position->x,
							position->y,
							theta,
							SP6_RU_TOMATO_SPEED,
							SP6_RU_TOMATO_COLLIDANT_SIZE,
							1,
							SkinID::TOROI_SP6_RU_TOMATO
						);
					}
					DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
					sp6_ru_tomato_tick_last_generated_clock = DxLib::GetNowCount();
					++sp6_ru_tomato_tick_count;
				}
				if (sp6_ru_tomato_tick_count == SP6_RU_TOMATO_TICK_COUNT_MAX) {					// 連射(小)の連射回数を完了したとき
					sp6_ru_tomato_fire_last_generated_clock = DxLib::GetNowCount();				// 連射(大)の最終生成時間を設定
					sp6_ru_tomato_tick_count = 0;
				}
			}
			DxLib::DrawRotaGraph(																		// ルーのポーズ
				SP6_POSE_RU_X_LEFT,
				SP6_POSE_RU_Y,
				SP6_POSE_RU_EXTRATE,
				SP6_POSE_RU_RADIAN_LEFT,
				ImageHandles::POTATO_BASIC,
				TRUE);
			DxLib::DrawRotaGraph(
				SP6_POSE_RU_X_RIGHT,
				SP6_POSE_RU_Y,
				SP6_POSE_RU_EXTRATE,
				SP6_POSE_RU_RADIAN_RIGHT,
				ImageHandles::POTATO_BASIC,
				TRUE);
			break;
		}
		}
	}
	else {
		STATUS = ToroiStatus::SP7;
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP7_NAME));
	}
}


void Toroi::sp7() {		// 「限りなく降り注ぐ、嬰怨の涙」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > 0) {

	}
	else {

	}
}


enum SkinID Toroi::get_sp5_heart_random_image_handles() {
	SkinID HeartHandles = SkinID::TOROI_SP5_HEART_RED;						// ImageHandlesの初期化
	int sp5_heart_random_image_handle_case_num = DxLib::GetRand(8) + 1;

	switch (sp5_heart_random_image_handle_case_num) {
	case 1:
		HeartHandles = SkinID::TOROI_SP5_HEART_RED;							// ImageHandlesを割当
		break;
	case 2:
		HeartHandles = SkinID::TOROI_SP5_HEART_ORANGE;
		break;
	case 3:
		HeartHandles = SkinID::TOROI_SP5_HEART_YELLOW;
		break;
	case 4:
		HeartHandles = SkinID::TOROI_SP5_HEART_GREEN;
		break;
	case 5:
		HeartHandles = SkinID::TOROI_SP5_HEART_TEAL;
		break;
	case 6:
		HeartHandles = SkinID::TOROI_SP5_HEART_AQUA;
		break;
	case 7:
		HeartHandles = SkinID::TOROI_SP5_HEART_BLUE;
		break;
	case 8:
		HeartHandles = SkinID::TOROI_SP5_HEART_PURPLE;
		break;
	case 9:
		HeartHandles = SkinID::TOROI_SP5_HEART_FUCHSIA;
		break;
	}
	return HeartHandles;
}