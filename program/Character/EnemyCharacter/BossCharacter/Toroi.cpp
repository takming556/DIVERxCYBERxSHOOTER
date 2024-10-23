#include <vector>
#include <memory>
#include <cmath>
#include <string>
#include <numbers>
#include <utility>
#include "DxLib.h"
#include "enum.h"
#include "GameConductor.h"
#include "Field.h"
#include "Character/Character.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/Toroi.h"
#include "CollideRealm/CollideCircle.h"
#include "Offensive/Bullet/CurvingShot.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Offensive/Bullet/StraightShot/ReflectShot/ReflectShot.h"
#include "Offensive/Bullet/ParabolicShot.h"
#include "Offensive/Laser/Laser.h"
#include "Offensive/Laser/PolarLaser.h"
#include "Offensive/Laser/CartesianLaser/CartesianLaser.h"
#include "Offensive/Bullet/StraightShot/ReflectShot/DVDShot.h"
#include "Offensive/Bullet/StraightShot/ReflectShot/MultiplyShot.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"
#include "FontHandles.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"


using std::vector;
using std::make_unique;
using std::sin;
using std::cos;
using std::wstring;
using std::numbers::pi;
using std::make_pair;

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

const unsigned int Toroi::NM1_INTERVAL = 12000;

const unsigned int Toroi::NM2_LASER_LENGTH = 700;//長さ
const unsigned int Toroi::NM2_SHOT_LASER_WIDTH = 70;
const unsigned int Toroi::NM2_NOTIFY_LASER_WIDTH = 70;	// 20;
const unsigned int Toroi::LASERNOZZLES = 43;

const unsigned int Toroi::NM3_PARASOL_RAIN_INTERVAL = 1000;
const unsigned int Toroi::NM3_PARASOL_RAIN_LANE_COUNT = 6;
const unsigned int Toroi::NM3_PARASOL_RAIN_THROW_SPEED = 100;
const double Toroi::NM3_PARASOL_RAIN_GRAVITY_ACCEL = 150.0;
const unsigned int Toroi::NM3_PARASOL_RAIN_COLLIDANT_SIZE = 10;
const unsigned int Toroi::NM3_PARASOL_RAIN_FRAMING_INTERVAL = 300;

const unsigned int Toroi::NM4_BIG_NOZZLES = 30;
const unsigned int Toroi::NM4_INTERVAL = 1000;
const double Toroi::NM4_BIG_SPEED = 100;
const double Toroi::NM4_SMALL_SPEED = 200;
const double Toroi::NM4_RED_CURVE_SPEED = 1.0 / 16.0 * pi;;
const double Toroi::NM4_BLUE_CURVE_SPEED = -1.0 / 16.0 * pi;;
const unsigned int Toroi::NM4_COLLIDANT_SIZE_BIG = 20;
const unsigned int Toroi::NM4_COLLIDANT_SIZE_SMALL = 10;

const int Toroi::SP1_THINKING_TIME_LENGTH = 5000;						// [ミリ秒]
const unsigned int Toroi::SP1_TRICK_DURATION = 8000;					// [ミリ秒]
const unsigned int Toroi::SP1_TRICK_NOZZLES = 24;	// 32;						// SP1のTrickのノズル数
const unsigned int Toroi::SP1_TRICK_NOZZLE_RADIUS = 70;					// SP1のTrickの弾の発射点の半径
const double Toroi::SP1_TRICK_NOZZLE_ROTATE_SPEED = (1.0 / 2.0) * pi;	// SP1のTrickのノズル回転速度
const unsigned int Toroi::SP1_TRICK_SHOT_SPEED = 250;					// SP1のTrickの弾の速さ
const unsigned int Toroi::SP1_TRICK_SHOT_INTERVAL = 450;	// 300;				// SP1のTrickの発射間隔[ミリ秒]
const unsigned int Toroi::SP1_TRICK_SHOT_COLLIDANT_SIZE = 10;			// SP1のTrickの弾の当たり判定サイズ
const unsigned int Toroi::SP1_TREAT_DURATION = 8000;					// [ミリ秒]
const unsigned int Toroi::SP1_TREAT_THROW_AMOUNT = 64;
const unsigned int Toroi::SP1_TREAT_THROW_INTERVAL = 1500;				// [ミリ秒]
const unsigned int Toroi::SP1_TRAP_SHOT_INTERVAL = 66; // 33;					// [ミリ秒]
const unsigned int Toroi::SP1_TRAP_SHOT_COLLIDANT_SIZE = 10;
const unsigned int Toroi::SP1_TRAP_ACROSS_SPEED = 250;					// [ピクセル／秒]
const unsigned int Toroi::SP1_TRAP_HORIZONTAL_ACROSS_DURATION = ((double)Field::PIXEL_SIZE_X / Toroi::SP1_TRAP_ACROSS_SPEED) * 1000;	// [ミリ秒]
const unsigned int Toroi::SP1_TRAP_VERTICAL_ACROSS_DURATION = ((double)Field::PIXEL_SIZE_Y / Toroi::SP1_TRAP_ACROSS_SPEED) * 1000;		// [ミリ秒]
const unsigned char Toroi::SP1_TRAP_ACROSS_LANES = 4;

const double Toroi::SP2_SURROUNDED_LEFT_ARG = 5.0 / 4.0 * pi;
const double Toroi::SP2_SURROUNDED_RIGHT_ARG = 7.0 / 4.0 * pi;
const double Toroi::SP2_SURROUNDED_SPEED = 100;
const double Toroi::SP2_SURROUNDED_LEFT_CURVE_SPEED = (1.0 / 12.0) * pi;
const double Toroi::SP2_SURROUNDED_RIGHT_CURVE_SPEED = -(1.0 / 12.0) * pi;
const unsigned int Toroi::SP2_SURROUNDED_COLLIDANT_SIZE = 10;
const unsigned int Toroi::SP2_SURROUNDED_INTERVAL = 1000;
const double Toroi::SP2_STING_GENERATED_TOP_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y + 100;
const double Toroi::SP2_STING_GENERATED_BOTTOM_Y = InFieldPosition::MIN_MOVABLE_BOUNDARY_Y - 100;
const double Toroi::SP2_STING_GENERATED_LEFT_X = InFieldPosition::MIN_MOVABLE_BOUNDARY_X - 100;
const double Toroi::SP2_STING_GENERATED_RIGHT_X = InFieldPosition::MAX_MOVABLE_BOUNDARY_X + 100;
const double Toroi::SP2_STING_SPEED = 150;
const unsigned int Toroi::SP2_STING_COLLIDANT_SIZE = 7;
const unsigned int Toroi::SP2_STING_INTERVAL = 2000;
const double Toroi::SP2_RAIN_LEFT_POS_X = Field::PIXEL_SIZE_X / 2 - 200;
const double Toroi::SP2_RAIN_RIGHT_POS_X = Field::PIXEL_SIZE_X / 2 + 200;
const double Toroi::SP2_RAIN_POS_Y = InFieldPosition::MAX_MOVABLE_BOUNDARY_Y - 100;
const double Toroi::SP2_RAIN_ACCEL = 150.0;
const double Toroi::SP2_RAIN_ACCEL_ARG = -1.0 / 2.0 * pi;
const unsigned int Toroi::SP2_RAIN_COLLIDANT_SIZE = 10;
const unsigned int Toroi::SP2_RAIN_NOZZLES = 20;
const unsigned int Toroi::SP2_RAIN_INTERVAL = 2000;

const unsigned int Toroi::SP3_GHOSTS_EMIT_INTERVAL = 3000;
const unsigned int Toroi::SP3_GHOST_FRAMING_INTERVAL = 200;

const unsigned int Toroi::SP4_INITIAL_WAIT = 3000;
const double Toroi::SP4_KNIFE_INITIAL_POS_X = Field::PIXEL_SIZE_X / 2;
const double Toroi::SP4_KNIFE_INITIAL_POS_Y = InFieldPosition::MIN_MOVABLE_BOUNDARY_X;
const unsigned int Toroi::SP4_KNIFE_COLLIDANT_SIZE = 2;
const double Toroi::SP4_KNIFE_SPEED = 250;
const unsigned int Toroi::SP4_BLOOD_SPLASH_AMOUNT = 50;
const double Toroi::SP4_BLOOD_SPLASH_GRAVITY_ACCEL = 150.0;
const unsigned int Toroi::SP4_BLOOD_SPLASH_COLLIDANT_SIZE = 10;
const unsigned int Toroi::SP4_BLOOD_SPLASH_AFTER_WAIT = 3000;

const unsigned int Toroi::SP5_RAIN_INTERVAL = 250;						// SP5の躁鬱雨の発射間隔(共通)[ミリ秒]
const double Toroi::SP5_RAIN_SOU_GENERATED_Y = -100;					// SP5の躁雨が生成されるY座標(画面外下)
const double Toroi::SP5_RAIN_UTU_GENERATED_Y = 842;						// SP5の鬱雨が生成されるY座標(画面外上)
const unsigned int Toroi::SP5_RAIN_SPEED = 300;							// SP5の躁鬱雨の速度(共通)
const unsigned int Toroi::SP5_RAIN_COLLIDANT_SIZE = 10;					// SP5の躁鬱雨の当たり判定サイズ(共通)
const unsigned int Toroi::SP5_HEART_INTERVAL = 5000;					// SP5のハート弾の発射間隔[ミリ秒]
const double Toroi::SP5_HEART_GENERATED_TOP_Y = 842;					// SP5のハート弾が生成されるY座標(画面外上)
const double Toroi::SP5_HEART_GENERATED_BOTTOM_Y = -100;				// SP5のハート弾が生成されるY座標(画面外下)
const double Toroi::SP5_HEART_GENERATED_LEFT_X = -100;					// SP5のハート弾が生成されるY座標(画面外左)
const double Toroi::SP5_HEART_GENERATED_RIGHT_X = 720;					// SP5のハート弾が生成されるY座標(画面外右)
const double Toroi::SP5_HEART_SPEED = 300;								// SP5のハート弾の速度
const unsigned int Toroi::SP5_HEART_COLLIDANT_SIZE = 7;					// SP5のハート弾の当たり判定サイズ

const unsigned int Toroi::SP6_RAN_NOZZLE_INIT_RADIUS = 800;				// SP6のRANの回転ノズルの発射点の初期半径
const unsigned int Toroi::SP6_RAN_MAIN_NOZZLES_AMOUNT = 8;				// SP6のRANのノズル(大)の数
const unsigned int Toroi::SP6_RAN_SUB_NOZZLES_AMOUNT = 4;				// SP6のRANのノズル(小)の数
const double Toroi::SP6_RAN_SUB_NOZZLES_ROTATE_SPEED = 1.0 / 2.0 * pi;	// SP6のRANのノズル(小)の回転速度
const unsigned int Toroi::SP6_RAN_SHOT_INTERVAL = 500;					// SP6のRANのノズル(小)からのショットの発射間隔
const double Toroi::SP6_RAN_SHOT_SPEED = 200;							// SP6のRANのノズル(小)からのショットの速度
const unsigned int Toroi::SP6_RAN_SHOT_COLLIDANT_SIZE = 7;				// SP6のRANのノズル(小)からのショットの当たり判定サイズ
const unsigned int Toroi::SP6_RAN_CONTRACTION_SPEED = 50;				// SP6のRANの円の収縮速度[ピクセル/秒]

const unsigned int Toroi::SP6_RU_INITAL_LIMITED_TIME = 3000;			// SP6のRUの準備の制限時間[ミリ秒]
const unsigned int Toroi::SP6_RU_LIMITED_TIME = 10000;					// SP6のRUの制限時間[ミリ秒]
const unsigned int Toroi::SP6_RU_POTATO_INTERVAL = 100;					// SP6のRUのポテト弾の発射間隔[ミリ秒]
const double Toroi::SP6_RU_POTATO_GENERATED_Y = 842;					// SP6のRUのポテト弾が生成されるY座標(画面外上)
const unsigned int Toroi::SP6_RU_POTATO_SPEED = 400;					// SP6のRUのポテト弾の速度
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

const unsigned int Toroi::SP7_INITIAL_WAIT = 2000;
const unsigned int Toroi::SP7_DIAL_COUNT = 5;
const unsigned int Toroi::SP7_DIAL_SHOT_COUNT = 48;
const double Toroi::SP7_DIAL_APERTURE_ARG_RANGE = 1.0 / 6.0 * pi;
const double Toroi::SP7_DIAL_ROLLING_SPEED = pi;
const unsigned int Toroi::SP7_DIAL_INNERMOST_RADIUS = 100;
const unsigned int Toroi::SP7_DIAL_RADIUS_STEP = 50;
const unsigned int Toroi::SP7_DIAL_SHOT_COLLIDANT_SIZE = 12;
const double Toroi::SP7_DIAL_SHOT_SCATTER_SPEED = 350;
const unsigned int Toroi::SP7_LASER_EMIT_DURATION = 3000;
const unsigned int Toroi::SP7_LASER_COUNT = 21;
const unsigned int Toroi::SP7_LASER_WIDTH = 10;
const unsigned int Toroi::SP7_LASER_LENGTH = Field::PIXEL_SIZE_Y;
const unsigned int Toroi::SP7_LASER_DPS = 50;
const unsigned int Toroi::SP7_LASER_PRENOTIFY_DURATION = 2000;
const unsigned int Toroi::SP7_LASER_PRENOTIFY_LINE_LENGTH = Field::PIXEL_SIZE_Y;
const double Toroi::SP7_DAGGER_EMIT_POS_Y = 800.0;
const unsigned int Toroi::SP7_DAGGER_EMIT_INTERVAL = 100;
const unsigned int Toroi::SP7_DAGGER_COLLIDANT_SIZE = 5;
const double Toroi::SP7_DAGGER_SPEED = 200;



//const unsigned int Toroi::INITIAL_HP = 1000;
const unsigned int Toroi::INITIAL_HP = 4300;

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

const double Toroi::NM1_ACTIVATE_HP_RATIO = 100.0 / 100.0;	// 300 = 7%
const double Toroi::SP1_ACTIVATE_HP_RATIO = 93.0 / 100.0;	// 500 = 11.6%
const double Toroi::NM2_ACTIVATE_HP_RATIO = 81.4 / 100.0;	// 300 = 7%
const double Toroi::SP2_ACTIVATE_HP_RATIO = 74.4 / 100.0;	// 400 = 9.3%
const double Toroi::SP3_ACTIVATE_HP_RATIO = 65.1 / 100.0;	// 400 = 9.3%
const double Toroi::NM3_ACTIVATE_HP_RATIO = 55.8 / 100.0;	// 300 = 7%
const double Toroi::SP4_ACTIVATE_HP_RATIO = 48.8 / 100.0;	// 400 = 9.3%
const double Toroi::SP5_ACTIVATE_HP_RATIO = 39.5 / 100.0;	// 400 = 9.3%
const double Toroi::NM4_ACTIVATE_HP_RATIO = 30.2 / 100.0;	// 300 = 7%
const double Toroi::SP6_ACTIVATE_HP_RATIO = 23.2 / 100.0;	// 500 = 11.6%
const double Toroi::SP7_ACTIVATE_HP_RATIO = 11.6 / 100.0;	// 500 = 11.6%

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
	kept_clock(DxLib::GetNowCount()),
	nm1_last_generated_clock(DxLib::GetNowCount()),
	nm2_mode(ToroiNM2Mode::WARNING),
	nm2_laser_arg(0.0),
	nm2_laser_width(0),
	nm2_laser_kept_clock(0),
	nm2_laser_notify_count(0),
	nm2_laser_laps(0),
	nm2_notifyarg1(0.0),
	nm2_notifyarg2(0.0),
	nm2_lasercount(0),
	nm2_laser_shot_count(0),
	nm2_random_num(0),
	nm2_shot_arg_yellow(0.0),
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
	sp2_last_surrounded_clock(DxLib::GetNowCount()),
	sp2_last_sting_clock(DxLib::GetNowCount()),
	sp2_last_rain_clock(DxLib::GetNowCount()),
	sp3_status(ToroiSP3Status::STEP1_INIT),
	sp3_last_step_advanced_clock(0),
	sp3_step1_slash_laser_id(0),
	sp3_step2_last_ghost_emitted_clock(0),
	sp3_step3_slash_laser_id(0),
	sp4_started_flag(false),
	sp4_started_clock(0),
	sp4_knife_emitted_flag(false),
	sp4_knife_shot_id(0),
	sp4_blood_splashed_flag(false),
	sp4_blood_splashed_clock(0),
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
	sp6_ru_tomato_tick_count(0),
	sp7_started_flag(false),
	sp7_started_clock(0),
	sp7_last_dagger_emitted_clock(0),
	sp7_dial_generated_flag(false),
	sp7_dial_arg_last_updated_clock(0),
	sp7_now_rolling_dial_num(0),
	sp7_all_dials_unlocked_flag(false),
	sp7_laser_prenotify_last_started_clock(0),
	//sp7_laser_prenotify_started_flag(false),
	sp7_laser_prenotify_last_finished_clock(0),
	sp7_laser_prenotify_finished_flag(false),
	sp7_laser_emit_last_started_clock(0),
	sp7_laser_emit_started_flag(false),
	sp7_laser_emit_last_finished_clock(0),
	sp7_laser_emit_finished_flag(false),
	sp7_dials_shots_scattered_flag(false)
{
	STATUS = ToroiStatus::PREPARE;	// どこを開始地点とするか
	for (int i = 0; i < 45; ++i) {
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
	int elapsed_time = DxLib::GetNowCount() - kept_clock;
	switch (STATUS) {
	case ToroiStatus::PREPARE:
		STATUS = ToroiStatus::NORMAL1;
		break;

	case ToroiStatus::NORMAL1:
		if (elapsed_time > 3000) {
			nm1();
		}
		break;

	case ToroiStatus::SP1:		// 「Trick or Treat or Trap?」
		if (elapsed_time > 3000) {
			sp1();
		}
		break;

	case ToroiStatus::NORMAL2:
		if (elapsed_time > 6000) {
			nm2();
		}
		break;

	case ToroiStatus::SP2:		// 「慈子欺瞞クリーナー」
		if (elapsed_time > 3000) {
			sp2();
		}
		break;

	case ToroiStatus::SP3:		// 「赤き怨みは稲穂を揺らす」
		if (elapsed_time > 6000) {
			sp3();
		}
		break;

	case ToroiStatus::NORMAL3:
		if (elapsed_time > 3000) {
			nm3();
		}
		break;

	case ToroiStatus::SP4:		// 「咲き誇れ、血染めの梅」
		if (elapsed_time > 3000) {
			sp4();
		}
		break;

	case ToroiStatus::SP5:		// 「インターネット再興」
		if (elapsed_time > 3000) {
			sp5();
		}
		break;

	case ToroiStatus::NORMAL4:
		if (elapsed_time > 3000) {
			nm4();
		}
		break;

	case ToroiStatus::SP6:		// 「Ex-tROiA.ru4(D)」
		if (elapsed_time > 7000) {
			sp6();
		}
		break;

	case ToroiStatus::SP7:		// 「限りなく降り注ぐ、嬰怨の涙」
		if (elapsed_time > 3000) {
			sp7();
		}
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
		int nm1_generated_delta_time = DxLib::GetNowCount() - nm1_last_generated_clock;
		if (nm1_generated_delta_time > NM1_INTERVAL) {
			Field::ENEMY_BULLETS->clear();
			for (int i = 0; i < 3; ++i) {
				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<MultiplyShot>(
					position->x,
					position->y,
					3.0 / 2.0 * pi - 1.0 / 6.0 * pi + 1.0 / 6.0 * i * pi
				);
			}
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			nm1_last_generated_clock = DxLib::GetNowCount();
		}
	}
	else {
		Field::ENEMY_BULLETS->clear();
		STATUS = ToroiStatus::SP1;
		kept_clock = DxLib::GetNowCount();
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(L"「Trick or Treat or Trap?」"));
	}
}


void Toroi::nm2() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP2_ACTIVATE_HP_RATIO) {
		int nm2_laser_elaspsed_time = DxLib::GetNowCount() - nm2_laser_kept_clock;
		if (nm2_mode == ToroiNM2Mode::WARNING) {//アンチ出すよ
			if (nm2_laser_notify_count == 0) {
				if ((nm2_laser_laps + 2) % 2 == 0) {
					nm2_random_num = 10 + DxLib::GetRand(4);
				}
				else {
					nm2_random_num = DxLib::GetRand(24);
				}
				nm2_laser_arg = 24.0 / 24.0 * pi + 1.0 / 24.0 * nm2_random_num * pi;
				nm2_notifyarg1 = nm2_laser_arg + 1.0 / 12.0 * pi;
				nm2_notifyarg2 = nm2_laser_arg - 1.0 / 12.0 * pi + 2.0 * pi;
				++nm2_laser_laps;
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
				nm2_laser_arg = 24.0 / 24.0 * pi + 1.0 / 24.0 * nm2_random_num * pi;
				nm2_notifyarg1 = nm2_laser_arg + 1.0 / 12.0 * pi;
				nm2_notifyarg2 = nm2_laser_arg - 1.0 / 12.0 * pi + 2.0 * pi;
			}
			nm2_shot_arg_yellow = nm2_notifyarg1 + 1.0 / 24.0 * pi;
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
			for (int i = 0; i < LASERNOZZLES;++i) {
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
				nm2_shot_arg_yellow += 1.0 / 24.0 * pi;
			}
			if (nm2_laser_elaspsed_time > 3000) {
				nm2_laser_notify_count = 0;
				nm2_mode = ToroiNM2Mode::SHOT;
				nm2_laser_kept_clock = DxLib::GetNowCount();
			}
		}
		else if (nm2_mode == ToroiNM2Mode::SHOT) {
			if (nm2_lasercount == 0) {
				nm2_laser_arg = nm2_notifyarg1;
				for (int i = 0; i < LASERNOZZLES + 2; ++i) {
					if (i == 0 || i == LASERNOZZLES + 2 - 1) {
						nm2_laser_width = NM2_NOTIFY_LASER_WIDTH;
					}
					else {
						nm2_laser_width = NM2_SHOT_LASER_WIDTH;
					}
					nm2_laser_id[i] = Laser::GENERATE_ID();
					(*Field::ENEMY_LASERS)[nm2_laser_id[i]] = make_unique<PolarLaser>(
						position->x,
						position->y,
						nm2_laser_arg,
						NM2_LASER_LENGTH,
						nm2_laser_width,
						10.0,
						true,
						SkinID::TOROI_NM2LASER_RED
					);
					nm2_laser_arg += 1.0 / 24.0 * pi;
					++nm2_laser_shot_count;
				}
				nm2_lasercount += 1;
			}
			if (nm2_laser_elaspsed_time > 3000) {
				nm2_lasercount = 0;
				/*for (int i = 0; i < LASERNOZZLES; ++i) {
					(*Field::ENEMY_LASERS).erase(nm2_laser_id[i]);
				}*/
				(*Field::ENEMY_LASERS).clear();
				nm2_mode = ToroiNM2Mode::WARNING;
				nm2_laser_kept_clock = DxLib::GetNowCount();
			}
		}

	}
	else {
		STATUS = ToroiStatus::SP2;
		kept_clock = DxLib::GetNowCount();
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP2_NAME));
		/*for (int i = 0; i < LASERNOZZLES; ++i) {
			(*Field::ENEMY_LASERS).erase(nm2_laser_id[i]);
		}*/
		(*Field::ENEMY_LASERS).clear();
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
		kept_clock = DxLib::GetNowCount();
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP4_NAME));
	}
}


void Toroi::nm4() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP6_ACTIVATE_HP_RATIO) {
		int nm4_generated_delta_time = DxLib::GetNowCount() - nm4_last_generated_clock;
		if (nm4_generated_delta_time > NM4_INTERVAL) {
			if (nm4_color_flag == ToroiNM4ColorFlag::RED) {
				int nm4_red_small_rand_arg = DxLib::GetRand(4);
				for (int j = 0; j < 12; ++j) {
					for (int i = 0; i < 5; ++i) {
						double theta = 2.0 * pi / 120 * i + (1.0 / 6.0 * pi * j);
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<CurvingShot>(	// RED_BIG
							position->x,
							position->y,
							theta,
							NM4_BIG_SPEED,
							NM4_RED_CURVE_SPEED,
							NM4_COLLIDANT_SIZE_BIG,
							1,
							SkinID::TOROI_NM4_RED_BIG
						);
					}
					for (int i = 0; i < 3; ++i) {
						double theta = 2.0 * pi / 60 * i + (1.0 / 6.0 * pi * j) - 0.0 + nm4_red_small_rand_arg / 36.0 * pi; // 240
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(	// RED_SMALL
							position->x,
							position->y,
							theta,
							NM4_SMALL_SPEED,
							NM4_COLLIDANT_SIZE_SMALL,
							1,
							SkinID::TOROI_NM4_RED_SMALL
						);
					}
				}
				nm4_color_flag = ToroiNM4ColorFlag::BLUE;
			}
			else if (nm4_color_flag == ToroiNM4ColorFlag::BLUE) {
				int nm4_blue_small_rand_arg = DxLib::GetRand(4);
				for (int j = 0; j < 12; ++j) {
					for (int i = 0; i < 5; ++i) {
						double theta = 2.0 * pi / 120 * i + (1.0 / 6.0 * pi * j) - 1.0 / 12.0 * pi;
						(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<CurvingShot>(	// BLUE_BIG
							position->x,
							position->y,
							theta,
							NM4_BIG_SPEED,
							NM4_BLUE_CURVE_SPEED,
							NM4_COLLIDANT_SIZE_BIG,
							1,
							SkinID::TOROI_NM4_BLUE_BIG
						);
					}
					for (int i = 0; i < 3; ++i) {
						double theta = 2.0 * pi / 60 * i + (1.0 / 6.0 * pi * j) - 3.0 + nm4_blue_small_rand_arg / 36.0 * pi;
						(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(	// BLUE_SMALL
							position->x,
							position->y,
							theta,
							NM4_SMALL_SPEED,
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
		kept_clock = DxLib::GetNowCount();
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
		case ToroiSP1Mode::TRAP_INIT:
		{
			sp1_trap_last_started_clock = DxLib::GetNowCount();
			sp1_trap_phase = 1;
			sp1_mode = ToroiSP1Mode::TRAP_ACROSS_INIT;
		}
		case ToroiSP1Mode::TRAP_ACROSS_INIT: {
			sp1_trap_last_across_started_clock = DxLib::GetNowCount();
			sp1_mode = ToroiSP1Mode::TRAP;
			break;
		}
		case ToroiSP1Mode::TRAP:
		{
			int trap_start_delta_time = DxLib::GetNowCount() - sp1_trap_last_started_clock;
			if (trap_start_delta_time < 3000) {
				InFieldPosition trap_pos(
					InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0 - 25.0,
					InFieldPosition::MAX_MOVABLE_BOUNDARY_Y / 2.0 + 150.0
				);
				DxLib::DrawFormatString(
					trap_pos.get_draw_position().x,
					trap_pos.get_draw_position().y,
					Colors::YELLOW,
					L"*Trap*"
				);

			}

			int across_delta_time = DxLib::GetNowCount() - sp1_trap_last_across_started_clock;
			int shot_delta_time = DxLib::GetNowCount() - sp1_trap_last_shot_clock;

			if (sp1_trap_phase > SP1_TRAP_ACROSS_LANES * 2) {
				sp1_mode = ToroiSP1Mode::INITIAL;
			}
			else if(sp1_trap_phase % 2 == 0){	// (2), (4), (6), (8) 縦によぎる
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
		GameConductor::TECHNICAL_SCORE += SP1_ACCOMPLISH_BONUS;
		STATUS = ToroiStatus::NORMAL2;
		kept_clock = DxLib::GetNowCount();
	}
}


void Toroi::sp2() {		// 「慈子欺瞞クリーナー」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP3_ACTIVATE_HP_RATIO) {
		int sp2_surrounded_delta_time = DxLib::GetNowCount() - sp2_last_surrounded_clock;
		if (sp2_surrounded_delta_time > SP2_SURROUNDED_INTERVAL) {
			(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<CurvingShot>(
					position->x,
					position->y,
					SP2_SURROUNDED_LEFT_ARG,
					SP2_SURROUNDED_SPEED,
					SP2_SURROUNDED_LEFT_CURVE_SPEED,
					SP2_SURROUNDED_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP2_SURROUNDED
			);
			(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<CurvingShot>(
					position->x,
					position->y,
					SP2_SURROUNDED_RIGHT_ARG,
					SP2_SURROUNDED_SPEED,
					SP2_SURROUNDED_RIGHT_CURVE_SPEED,
					SP2_SURROUNDED_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP2_SURROUNDED
			);
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			sp2_last_surrounded_clock = DxLib::GetNowCount();
		}

		int sp2_sting_delta_time = DxLib::GetNowCount() - sp2_last_sting_clock;
		if (sp2_sting_delta_time > SP2_STING_INTERVAL) {
			for (int i = 0; i < 2; ++i) {
				int random_x_top = DxLib::GetRand(Field::PIXEL_SIZE_X);
				int random_x_bottom = DxLib::GetRand(Field::PIXEL_SIZE_X);
				int random_y_left = DxLib::GetRand(Field::PIXEL_SIZE_Y);
				int random_y_right = DxLib::GetRand(Field::PIXEL_SIZE_Y);
				InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
				double delta_x_top_mychr = my_chr_pos.x - random_x_top;
				double delta_y_top_mychr = my_chr_pos.y - SP2_STING_GENERATED_TOP_Y;
				double delta_x_bottom_mychr = my_chr_pos.x - random_x_bottom;
				double delta_y_bottom_mychr = my_chr_pos.y - SP2_STING_GENERATED_BOTTOM_Y;
				double delta_x_left_mychr = my_chr_pos.x - SP2_STING_GENERATED_LEFT_X;
				double delta_y_left_mychr = my_chr_pos.y - random_y_left;
				double delta_x_right_mychr = my_chr_pos.x - SP2_STING_GENERATED_RIGHT_X;
				double delta_y_right_mychr = my_chr_pos.y - random_y_right;
				double top_arg_toward_mychr = atan2(delta_y_top_mychr, delta_x_top_mychr);
				double bottom_arg_toward_mychr = atan2(delta_y_bottom_mychr, delta_x_bottom_mychr);;
				double left_arg_toward_mychr = atan2(delta_y_left_mychr, delta_x_left_mychr);;
				double right_arg_toward_mychr = atan2(delta_y_right_mychr, delta_x_right_mychr);;
				
				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					random_x_top,
					SP2_STING_GENERATED_TOP_Y,
					top_arg_toward_mychr,
					SP2_STING_SPEED,
					SP2_STING_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP2_STING
				);
				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					random_x_bottom,
					SP5_HEART_GENERATED_BOTTOM_Y,
					bottom_arg_toward_mychr,
					SP2_STING_SPEED,
					SP2_STING_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP2_STING
				);
				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					SP2_STING_GENERATED_LEFT_X,
					random_y_left,
					left_arg_toward_mychr,
					SP2_STING_SPEED,
					SP2_STING_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP2_STING
				);
				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					SP5_HEART_GENERATED_RIGHT_X,
					random_y_right,
					right_arg_toward_mychr,
					SP2_STING_SPEED,
					SP2_STING_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP2_STING
				);
			}
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			sp2_last_sting_clock = DxLib::GetNowCount();
		}

		int sp2_rain_delta_time = DxLib::GetNowCount() - sp2_last_rain_clock;
		if (sp2_rain_delta_time > SP2_RAIN_INTERVAL) {
			for (int i = 0; i < SP2_RAIN_NOZZLES; ++i) {
				double sp2_rain_arg = DxLib::GetRand(96) / 96.0 * pi;
				double sp2_rain_speed = DxLib::GetRand(50);
				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<ParabolicShot>(
					SP2_RAIN_LEFT_POS_X,
					SP2_RAIN_POS_Y,
					sp2_rain_arg,
					sp2_rain_speed,
					SP2_RAIN_ACCEL,
					SP2_RAIN_ACCEL_ARG,
					SP2_RAIN_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP2_RAIN
				);
				sp2_rain_arg = DxLib::GetRand(96) / 96.0 * pi;
				sp2_rain_speed = DxLib::GetRand(50);
				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<ParabolicShot>(
					SP2_RAIN_RIGHT_POS_X,
					SP2_RAIN_POS_Y,
					sp2_rain_arg,
					sp2_rain_speed,
					SP2_RAIN_ACCEL,
					SP2_RAIN_ACCEL_ARG,
					SP2_RAIN_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP2_RAIN
				);
			}
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			sp2_last_rain_clock = DxLib::GetNowCount();
		}
	}
	else {
		GameConductor::TECHNICAL_SCORE += SP2_ACCOMPLISH_BONUS;
		STATUS = ToroiStatus::SP3;
		kept_clock = DxLib::GetNowCount();
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
				sp3_status = ToroiSP3Status::STEP2;
				sp3_last_step_advanced_clock = DxLib::GetNowCount();
			}
			break;

		case ToroiSP3Status::STEP2:
			if (delta_time_step_advance < 18000) {
				int delta_time_ghost_emit = DxLib::GetNowCount() - sp3_step2_last_ghost_emitted_clock;
				if (delta_time_ghost_emit > SP3_GHOSTS_EMIT_INTERVAL) {
					for (const auto& ghost_id : sp3_step2_ghost_ids) {
						InFieldPosition mychr_pos = *(Field::MY_CHARACTER->position);
						InFieldPosition ghost_pos = *(*Field::ENEMY_BULLETS)[ghost_id]->position;
						double delta_x_mychr = mychr_pos.x - ghost_pos.x;
						double delta_y_mychr = mychr_pos.y - ghost_pos.y;
						double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
						(*Field::ENEMY_BULLETS)[ghost_id]->arg = arg_toward_mychr;
						(*Field::ENEMY_BULLETS)[ghost_id]->speed = 250;
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
				for (const auto& ghost_id : sp3_step2_ghost_ids) {
					Field::ENEMY_BULLETS->erase(ghost_id);
				}
				sp3_step2_ghost_ids.clear();
				sp3_last_step_advanced_clock = DxLib::GetNowCount();
				sp3_status = ToroiSP3Status::STEP3_INIT;
			}
			break;

		case ToroiSP3Status::STEP3_INIT:
		{
			sp3_step3_slash_laser_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[sp3_step3_slash_laser_id] = make_unique<CartesianLaser>(
				InFieldPosition::MAX_MOVABLE_BOUNDARY_X,
				450,
				InFieldPosition::MIN_MOVABLE_BOUNDARY_X,
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
			sp3_step3_besiege_laser_ids.push_back(temp_id);

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
			sp3_step3_besiege_laser_ids.push_back(temp_id);

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
			sp3_step3_besiege_laser_ids.push_back(temp_id);

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
			sp3_step3_besiege_laser_ids.push_back(temp_id);

			sp3_status = ToroiSP3Status::STEP3;
			sp3_last_step_advanced_clock = DxLib::GetNowCount();
			break;
		}
		case ToroiSP3Status::STEP3:
			if (delta_time_step_advance < 5000) {

			}
			else {
				Field::ENEMY_LASERS->erase(sp3_step3_slash_laser_id);
				for (const auto& laser_id : sp3_step3_besiege_laser_ids) {
					Field::ENEMY_LASERS->erase(laser_id);
				}
				sp3_step3_besiege_laser_ids.clear();
				sp3_status = ToroiSP3Status::STEP4_INIT;
			}
			break;

		case ToroiSP3Status::STEP4_INIT:
		{
			sp3_step4_slash_laser_id = Laser::GENERATE_ID();
			(*Field::ENEMY_LASERS)[sp3_step4_slash_laser_id] = make_unique<CartesianLaser>(
				500,
				450,
				120,
				220,
				10,
				100,
				true,
				SkinID::TOROI_SP3_SLASH
			);

			InFieldPosition radiation_pos((500 + 120) / 2, (450 + 220) / 2);
			for (int i = 0; i < 47; ++i) {
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					radiation_pos.x,
					radiation_pos.y,
					1.0 / 47.0 * i * 2.0 * pi,
					200,
					2,
					1,
					SkinID::TOROI_SP3_BLOOD_SPLASH
				);
			}
			sp3_status = ToroiSP3Status::STEP4;
			sp3_last_step_advanced_clock = DxLib::GetNowCount();
			break;
		}
		case ToroiSP3Status::STEP4:
			if (delta_time_step_advance < 1000) {

			}
			else {
				Field::ENEMY_LASERS->erase(sp3_step4_slash_laser_id);
				sp3_status = ToroiSP3Status::STEP5;
				sp3_last_step_advanced_clock = DxLib::GetNowCount();
			}
			break;

		case ToroiSP3Status::STEP5:
			if (delta_time_step_advance < 18000) {
				int delta_time_ghost_emit = DxLib::GetNowCount() - sp3_step5_last_ghost_emitted_clock;
				if (delta_time_ghost_emit > SP3_GHOSTS_EMIT_INTERVAL) {
					for (const auto& ghost_id : sp3_step5_ghost_ids) {
						InFieldPosition mychr_pos = *(Field::MY_CHARACTER->position);
						InFieldPosition ghost_pos = *(*Field::ENEMY_BULLETS)[ghost_id]->position;
						double delta_x_mychr = mychr_pos.x - ghost_pos.x;
						double delta_y_mychr = mychr_pos.y - ghost_pos.y;
						double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
						(*Field::ENEMY_BULLETS)[ghost_id]->arg = arg_toward_mychr;
						(*Field::ENEMY_BULLETS)[ghost_id]->speed = 250;
					}
					sp3_step5_ghost_ids.clear();
					for (int i = 0; i < 9; ++i) {
						BulletID ghost_id = Bullet::GENERATE_ID();
						(*Field::ENEMY_BULLETS)[ghost_id] = make_unique<StraightShot>(
							InFieldPosition::MIN_MOVABLE_BOUNDARY_X,
							(double)(Field::PIXEL_SIZE_Y - 200) / 9 * i + 200,
							0.0,
							30.0,
							15,
							1,
							SkinID::TOROI_SP3_GHOST
						);
						sp3_step5_ghost_ids.push_back(ghost_id);
					}
					for (int i = 0; i < 9; ++i) {
						BulletID ghost_id = Bullet::GENERATE_ID();
						(*Field::ENEMY_BULLETS)[ghost_id] = make_unique<StraightShot>(
							InFieldPosition::MAX_MOVABLE_BOUNDARY_X,
							(double)(Field::PIXEL_SIZE_Y - 200) / 9 * i + 200,
							pi,
							30.0,
							15,
							1,
							SkinID::TOROI_SP3_GHOST
						);
						sp3_step5_ghost_ids.push_back(ghost_id);
					}
					sp3_step5_last_ghost_emitted_clock = DxLib::GetNowCount();
				}
			}
			else {
				for (const auto& ghost_id : sp3_step5_ghost_ids) {
					Field::ENEMY_BULLETS->erase(ghost_id);
				}
				sp3_step5_ghost_ids.clear();
				sp3_last_step_advanced_clock = DxLib::GetNowCount();
				sp3_status = ToroiSP3Status::STEP1_INIT;
			}
			break;
		}
	}
	else {
		Field::ENEMY_LASERS->erase(sp3_step1_slash_laser_id);
		for (const auto& laser_id : sp3_step1_besiege_laser_ids) {
			Field::ENEMY_LASERS->erase(laser_id);
		}
		for (const auto& ghost_id : sp3_step2_ghost_ids) {
			Field::ENEMY_BULLETS->erase(ghost_id);
		}
		Field::ENEMY_LASERS->erase(sp3_step3_slash_laser_id);
		for (const auto& laser_id : sp3_step3_besiege_laser_ids) {
			Field::ENEMY_LASERS->erase(laser_id);
		}
		Field::ENEMY_LASERS->erase(sp3_step4_slash_laser_id);
		for (const auto& ghost_id : sp3_step5_ghost_ids) {
			Field::ENEMY_BULLETS->erase(ghost_id);
		}
		sp3_step1_besiege_laser_ids.clear();
		sp3_step2_ghost_ids.clear();
		sp3_step3_besiege_laser_ids.clear();
		sp3_step5_ghost_ids.clear();
		GameConductor::TECHNICAL_SCORE += SP3_ACCOMPLISH_BONUS;
		STATUS = ToroiStatus::NORMAL3;
		kept_clock = DxLib::GetNowCount();
	}
}


void Toroi::sp4() {		// 「咲き誇れ、血染めの梅」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP5_ACTIVATE_HP_RATIO) {

		if (sp4_started_flag == false) {
			sp4_started_clock = DxLib::GetNowCount();
			sp4_started_flag = true;
		}

		if (sp4_knife_emitted_flag == false) {
			int elapsed_time_sp4_started = DxLib::GetNowCount() - sp4_started_clock;
			if (elapsed_time_sp4_started > SP4_INITIAL_WAIT) {
				sp4_knife_shot_id = Bullet::GENERATE_ID();
				unique_ptr<BossCharacter>& boss = Field::GET_BOSS_CHARACTER(CharacterID::TOROI);
				double delta_x_boss = position->x - SP4_KNIFE_INITIAL_POS_X;
				double delta_y_boss = position->y - SP4_KNIFE_INITIAL_POS_Y;
				double arg_toward_boss = atan2(delta_y_boss, delta_x_boss);

				(*Field::ENEMY_BULLETS)[ sp4_knife_shot_id ] = make_unique<StraightShot>(
					SP4_KNIFE_INITIAL_POS_X,
					SP4_KNIFE_INITIAL_POS_Y,
					arg_toward_boss,
					SP4_KNIFE_SPEED,
					SP4_KNIFE_COLLIDANT_SIZE,
					10000,
					SkinID::TOROI_SP4_KNIFE
				);
				sp4_knife_emitted_flag = true;
			}
		}

		if (sp4_knife_emitted_flag == true && sp4_blood_splashed_flag == false) {
			unique_ptr<Bullet>& knife = (*Field::ENEMY_BULLETS)[ sp4_knife_shot_id ];
			if (knife->position->y >= position->y) {
				Field::ENEMY_BULLETS->erase(sp4_knife_shot_id);
				for (int i = 0; i < SP4_BLOOD_SPLASH_AMOUNT; ++i) {
					(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<ParabolicShot>(
						position->x,
						position->y,
						1.0 / 72.0 * 2 * pi * DxLib::GetRand(72),
						50 + DxLib::GetRand(150),
						SP4_BLOOD_SPLASH_GRAVITY_ACCEL,
						-1.0 / 2.0 * pi,
						SP4_BLOOD_SPLASH_COLLIDANT_SIZE,
						1,
						SkinID::TOROI_SP4_BLOOD_SPLASH
					);
					sp4_blood_splashed_clock = DxLib::GetNowCount();
					sp4_blood_splashed_flag = true;
				}
			}
		}

		if (sp4_blood_splashed_flag == true) {
			int elapsed_time_blood_splashed = DxLib::GetNowCount() - sp4_blood_splashed_clock;
			if (elapsed_time_blood_splashed > SP4_BLOOD_SPLASH_AFTER_WAIT) {
				sp4_knife_emitted_flag = false;
				sp4_blood_splashed_flag = false;
			}
		}

	}
	else {
		GameConductor::TECHNICAL_SCORE += SP4_ACCOMPLISH_BONUS;
		STATUS = ToroiStatus::SP5;
		kept_clock = DxLib::GetNowCount();
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP5_NAME));
	}
}


void Toroi::sp5() {		// 「インターネット再興」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * NM4_ACTIVATE_HP_RATIO) {
		int sp5_rain_generated_delta_time = DxLib::GetNowCount() - sp5_rain_last_generated_clock;	// 躁鬱雨
		if (sp5_rain_generated_delta_time > SP5_RAIN_INTERVAL) {									// 発射のタイミング
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
			random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);											// 鬱弾	// 躁弾と鬱弾の生成位置をずらす
			(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
				random_x,
				SP5_RAIN_UTU_GENERATED_Y,
				3.0 / 2.0 * pi,
				SP5_RAIN_SPEED,
				SP5_RAIN_COLLIDANT_SIZE,
				1,
				SkinID::TOROI_SP5_RAIN_UTU
			);
			sp5_rain_last_generated_clock = DxLib::GetNowCount();									// 発射したので最終発射時刻を更新
		}
		int sp5_heart_generated_delta_time = DxLib::GetNowCount() - sp5_heart_last_generated_clock;	// ハート弾
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
				double top_arg_toward_mychr = atan2(delta_y_top_mychr, delta_x_top_mychr);			// 自機を向いた角度を生成
				double bottom_arg_toward_mychr = atan2(delta_y_bottom_mychr, delta_x_bottom_mychr);;
				double left_arg_toward_mychr = atan2(delta_y_left_mychr, delta_x_left_mychr);;
				double right_arg_toward_mychr = atan2(delta_y_right_mychr, delta_x_right_mychr);;
				SkinID random_heart_handles = SkinID::TOROI_SP5_HEART_RED;							// ImageHandlesの初期化
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();					// ハート弾(画面外上に生成)
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					random_x_top,
					SP5_HEART_GENERATED_TOP_Y,
					top_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				);
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();					// ハート弾(画面外下に生成)
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					random_x_bottom,
					SP5_HEART_GENERATED_BOTTOM_Y,
					bottom_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				);
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();					// ハート弾(画面外左に生成)
				(*Field::ENEMY_BULLETS)[Bullet::GENERATE_ID()] = make_unique<StraightShot>(
					SP5_HEART_GENERATED_LEFT_X,
					random_y_left,
					left_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				);
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();					// ハート弾(画面外右に生成)
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
		GameConductor::TECHNICAL_SCORE += SP5_ACCOMPLISH_BONUS;
		STATUS = ToroiStatus::NORMAL4;
		kept_clock = DxLib::GetNowCount();
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
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;				// iノズル目の角度
				double update_x = position->x + sp6_ran_nozzle_radius * cos(theta);
				double update_y = position->y + sp6_ran_nozzle_radius * sin(theta);
				sp6_ran_nozzles.at(i)->update(update_x, update_y);
			}
			DxLib::DrawRotaGraph(														// ラン1回目のポーズ
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
			sp6_ran_nozzle_radius = SP6_RAN_NOZZLE_INIT_RADIUS;							// ノズル半径の初期化
			for (int i = 0; i < SP6_RAN_MAIN_NOZZLES_AMOUNT; ++i) {
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;				// iノズル目の角度
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
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;				// iノズル目の角度
				double update_x = position->x + sp6_ran_nozzle_radius * cos(theta);
				double update_y = position->y + sp6_ran_nozzle_radius * sin(theta);
				sp6_ran_nozzles.at(i)->update(update_x, update_y);
			}
			DxLib::DrawRotaGraph(														// ラン2回目のポーズ
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
			DxLib::DrawRotaGraph(																// ルーのポーズ
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
		GameConductor::TECHNICAL_SCORE += SP6_ACCOMPLISH_BONUS;
		STATUS = ToroiStatus::SP7;
		kept_clock = DxLib::GetNowCount();
		Field::SP_NAME_DISPLAY.reset(new SpNameDisplay(SP7_NAME));
	}
}


void Toroi::sp7() {		// 「限りなく降り注ぐ、嬰怨の涙」
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > 0) {

		if (sp7_started_flag == false) {
			sp7_started_clock = DxLib::GetNowCount();
			sp7_started_flag = true;
		}

		if (sp7_started_flag == true) {
			int elapsed_time_since_last_dagger_emitted = DxLib::GetNowCount() - sp7_last_dagger_emitted_clock;
			if (elapsed_time_since_last_dagger_emitted > SP7_DAGGER_EMIT_INTERVAL) {
				(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
					(double)Field::PIXEL_SIZE_X * DxLib::GetRand(100) / 100,
					SP7_DAGGER_EMIT_POS_Y,
					-1.0 / 2.0 * pi,
					SP7_DAGGER_SPEED,
					SP7_DAGGER_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP7_DAGGER
				);
				sp7_last_dagger_emitted_clock = DxLib::GetNowCount();
			}
		}

		if (sp7_started_flag == true && sp7_dial_generated_flag == false) {

			double begin_arg = -pi + SP7_DIAL_APERTURE_ARG_RANGE / 2;
			double end_arg = pi - SP7_DIAL_APERTURE_ARG_RANGE / 2;
			double dial_arg_range = end_arg - begin_arg;
			double element_arg = dial_arg_range / SP7_DIAL_SHOT_COUNT;

			for (int i = 0; i < SP7_DIAL_COUNT; ++i) {
				vector<double> temp_args;
				for (int j = 0; j < SP7_DIAL_SHOT_COUNT; ++j) {
					double temp_arg = begin_arg + element_arg * j;
					temp_args.push_back(temp_arg);
				}
				double begin_arg = -2.0 * pi;
				double end_arg = 2.0 * pi;
				double shift_arg_range = end_arg - begin_arg;
				double elem_arg = shift_arg_range / 48;
				double shift_arg = begin_arg + elem_arg * DxLib::GetRand(48);
				for (auto& temp_arg : temp_args) {
					temp_arg += shift_arg + 1.0 / 2.0 * pi + elem_arg / 4.0;
				}
				if (shift_arg > 0) {
					sp7_dial_aperture_args.push_back(make_pair(shift_arg, true));
				}
				else {
					sp7_dial_aperture_args.push_back(make_pair(shift_arg, false));
				}
				sp7_dials_shot_args.push_back(temp_args);
			}

			for (int i = 0; i < sp7_dials_shot_args.size(); ++i) {
				vector<BulletID> temp_shot_ids;

				SkinID skin_id;
				switch (i) {
				case 0:
					skin_id = SkinID::TOROI_SP7_1ST_DIAL_SHOT;
					break;
				case 1:
					skin_id = SkinID::TOROI_SP7_2ND_DIAL_SHOT;
					break;
				case 2:
					skin_id = SkinID::TOROI_SP7_3RD_DIAL_SHOT;
					break;
				case 3:
					skin_id = SkinID::TOROI_SP7_4TH_DIAL_SHOT;
					break;
				case 4:
					skin_id = SkinID::TOROI_SP7_5TH_DIAL_SHOT;
					break;
				default:
					skin_id = SkinID::TOROI_SP7_5TH_DIAL_SHOT;
					break;
				}

				for (int j = 0; j < sp7_dials_shot_args.at(i).size(); ++j) {
					BulletID temp_id = Bullet::GENERATE_ID();
					(*Field::ENEMY_BULLETS)[ temp_id ] = make_unique<StraightShot>(
						position->x + (SP7_DIAL_INNERMOST_RADIUS + i * SP7_DIAL_RADIUS_STEP) * cos(sp7_dials_shot_args.at(i).at(j)),
						position->y + (SP7_DIAL_INNERMOST_RADIUS + i * SP7_DIAL_RADIUS_STEP) * sin(sp7_dials_shot_args.at(i).at(j)),
						sp7_dials_shot_args.at(i).at(j),
						0,
						SP7_DIAL_SHOT_COLLIDANT_SIZE,
						1,
						skin_id
					);
					temp_shot_ids.push_back(temp_id);
				}
				sp7_dials_shot_ids.push_back(temp_shot_ids);
			}

			sp7_dial_generated_flag = true;
			sp7_dial_arg_last_updated_clock = DxLib::GetNowHiPerformanceCount();

		}

		if (sp7_dial_generated_flag == true && sp7_all_dials_unlocked_flag == false) {

			LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - sp7_dial_arg_last_updated_clock;
			double delta_arg = SP7_DIAL_ROLLING_SPEED * update_delta_time / 1000 / 1000;

			if (sp7_dial_aperture_args.at(sp7_now_rolling_dial_num).second == true) {
				sp7_dial_aperture_args.at(sp7_now_rolling_dial_num).first -= delta_arg;
			}
			else {
				sp7_dial_aperture_args.at(sp7_now_rolling_dial_num).first += delta_arg;
			}

			for (int i = 0; i < SP7_DIAL_SHOT_COUNT; ++i) {

				if (sp7_dial_aperture_args.at(sp7_now_rolling_dial_num).second == true) {
					sp7_dials_shot_args.at(sp7_now_rolling_dial_num).at(i) -= delta_arg;
				}
				else {
					sp7_dials_shot_args.at(sp7_now_rolling_dial_num).at(i) += delta_arg;
				}

				BulletID now_id = sp7_dials_shot_ids.at(sp7_now_rolling_dial_num).at(i);
				if (Field::IS_THERE(now_id) == true) {
					double temp_radius = SP7_DIAL_INNERMOST_RADIUS + SP7_DIAL_RADIUS_STEP * sp7_now_rolling_dial_num;
					double new_position_x = position->x + temp_radius * cos(sp7_dials_shot_args.at(sp7_now_rolling_dial_num).at(i));
					double new_position_y = position->y + temp_radius * sin(sp7_dials_shot_args.at(sp7_now_rolling_dial_num).at(i));
					(*Field::ENEMY_BULLETS)[ now_id ]->position->x = new_position_x;
					(*Field::ENEMY_BULLETS)[ now_id ]->position->y = new_position_y;
				}
			}

			sp7_dial_arg_last_updated_clock = DxLib::GetNowHiPerformanceCount();

			if (
				sp7_dial_aperture_args.at(sp7_now_rolling_dial_num).second == true &&
				sp7_dial_aperture_args.at(sp7_now_rolling_dial_num).first <= 0 ||
				sp7_dial_aperture_args.at(sp7_now_rolling_dial_num).second == false &&
				sp7_dial_aperture_args.at(sp7_now_rolling_dial_num).first >= 0
			) 
			{
				if (sp7_now_rolling_dial_num == SP7_DIAL_COUNT - 1) {
					sp7_all_dials_unlocked_flag = true;
					sp7_laser_prenotify_last_started_clock = DxLib::GetNowCount();
				}
				else {
					++sp7_now_rolling_dial_num;
				}
			}

		}

		if (sp7_all_dials_unlocked_flag == true && sp7_laser_prenotify_finished_flag == false) {
			int elapsed_time_since_laser_prenotify_last_started = DxLib::GetNowCount() - sp7_laser_prenotify_last_started_clock;
			if (elapsed_time_since_laser_prenotify_last_started < SP7_LASER_PRENOTIFY_DURATION) {
				double elem_arg = SP7_DIAL_APERTURE_ARG_RANGE / SP7_LASER_COUNT;
				double base_arg = -1.0 / 2.0 * pi - SP7_DIAL_APERTURE_ARG_RANGE / 2 + elem_arg / 4;
				InFieldPosition begin_pos = *position;
				for (int i = 0; i < SP7_LASER_COUNT; ++i) {
					double temp_arg = base_arg + elem_arg * i;
					double end_pos_x = position->x + SP7_LASER_PRENOTIFY_LINE_LENGTH * cos(temp_arg);
					double end_pos_y = position->y + SP7_LASER_PRENOTIFY_LINE_LENGTH * sin(temp_arg);
					InFieldPosition end_pos = InFieldPosition(end_pos_x, end_pos_y);
					DxLib::DrawLine(
						begin_pos.get_draw_position().x,
						begin_pos.get_draw_position().y,
						end_pos.get_draw_position().x,
						end_pos.get_draw_position().y,
						Colors::YELLOW
					);
				}
				//InFieldPosition begin_pos = *position;
				//InFieldPosition end_pos = InFieldPosition(Field::PIXEL_SIZE_X / 2, InFieldPosition::MIN_MOVABLE_BOUNDARY_Y);
				//DxLib::DrawLine(
				//	begin_pos.get_draw_position().x,
				//	begin_pos.get_draw_position().y,
				//	end_pos.get_draw_position().x,
				//	end_pos.get_draw_position().y,
				//	Colors::YELLOW
				//);
			}
			else {
				sp7_laser_prenotify_finished_flag = true;
				sp7_laser_prenotify_last_finished_clock = DxLib::GetNowCount();
			}

		}

		if (sp7_laser_prenotify_finished_flag == true && sp7_laser_emit_started_flag == false) {
			double elem_arg = SP7_DIAL_APERTURE_ARG_RANGE / SP7_LASER_COUNT;
			double begin_arg = -1.0 / 2.0 * pi - SP7_DIAL_APERTURE_ARG_RANGE / 2 + elem_arg / 4;
			for (int i = 0; i < SP7_LASER_COUNT; ++i) {
				LaserID temp_id = Laser::GENERATE_ID();
				(*Field::ENEMY_LASERS)[ temp_id ] = make_unique<PolarLaser>(
					position->x,
					position->y,
					begin_arg + elem_arg * i,
					SP7_LASER_LENGTH,
					SP7_LASER_WIDTH,
					SP7_LASER_DPS,
					true,
					SkinID::TOROI_SP7_LASER
				);
				sp7_laser_ids.push_back(temp_id);
			}
			sp7_laser_emit_started_flag = true;
			sp7_laser_emit_last_started_clock = DxLib::GetNowCount();

		}

		if (sp7_laser_emit_started_flag == true && sp7_laser_emit_finished_flag == false) {
			int elapsed_time_since_laser_emit_started = DxLib::GetNowCount() - sp7_laser_emit_last_started_clock;
			if (elapsed_time_since_laser_emit_started > SP7_LASER_EMIT_DURATION) {
				for (const auto& laser_id : sp7_laser_ids) {
					(*Field::ENEMY_LASERS)[ laser_id ]->inactivate();
				}
				sp7_laser_emit_finished_flag = true;
				sp7_laser_emit_last_finished_clock = DxLib::GetNowCount();
			}
		}

		if (sp7_laser_emit_finished_flag == true && sp7_dials_shots_scattered_flag == false) {
			for (int i = 0; i < SP7_DIAL_COUNT; ++i) {
				for (int j = 0; j < SP7_DIAL_SHOT_COUNT; ++j) {
					BulletID now_id = sp7_dials_shot_ids.at(i).at(j);
					if (Field::IS_THERE(now_id) == true) {
						InFieldPosition mychr_pos = *Field::MY_CHARACTER->position;
						InFieldPosition bullt_pos = *(*Field::ENEMY_BULLETS)[ sp7_dials_shot_ids.at(i).at(j) ]->position;
						double delta_pos_x = mychr_pos.x - bullt_pos.x;
						double delta_pos_y = mychr_pos.y - bullt_pos.y;
						double arg_toward_mychr = atan2(delta_pos_y, delta_pos_x);
						(*Field::ENEMY_BULLETS)[ sp7_dials_shot_ids.at(i).at(j) ]->set_arg(arg_toward_mychr);
						(*Field::ENEMY_BULLETS)[ sp7_dials_shot_ids.at(i).at(j) ]->set_speed(SP7_DIAL_SHOT_SCATTER_SPEED);
					}
				}
			}
			sp7_dials_shots_scattered_flag = true;
		}

		if (sp7_dials_shots_scattered_flag == true) {
			sp7_started_flag = false;
			sp7_dial_generated_flag = false;
			sp7_all_dials_unlocked_flag = false;
			sp7_now_rolling_dial_num = 0;
			sp7_laser_prenotify_finished_flag = false;
			sp7_laser_emit_started_flag = false;
			sp7_laser_emit_finished_flag = false;
			sp7_dials_shots_scattered_flag = false;
			sp7_dial_aperture_args.clear();
			sp7_dials_shot_args.clear();
			sp7_dials_shot_ids.clear();
			sp7_laser_ids.clear();
		}

	}
	else {
		GameConductor::TECHNICAL_SCORE += SP7_ACCOMPLISH_BONUS;
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