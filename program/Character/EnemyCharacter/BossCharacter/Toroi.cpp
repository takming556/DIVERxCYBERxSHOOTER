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
#include "DebugParams.h"
#include "Field.h"
//#include "Offensive/Bullet/StraightShot/TurnShot.h"
#include "Offensive/Bullet/CurvingShot.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "Offensive/Bullet/HomingShot/HomingShot.h"


using std::string;
using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;


const string Toroi::NAME("愛生トロイ");
const int Toroi::INITIAL_POS_X = 310;
const int Toroi::INITIAL_POS_Y = 620;
const unsigned int Toroi::INITIAL_COLLIDANT_SIZE = 60;
const double Toroi::DRAW_EXTRATE = 0.07;
const unsigned int Toroi::SP5_RAIN_INTERVAL = 250;						//ハート弾の生成間隔
const double Toroi::SP5_RAIN_SOU_GENARATED_Y = -100;					//躁雨が生成される場所(画面外)
const double Toroi::SP5_RAIN_UTU_GENARATED_Y = 842;						//鬱雨が生成される場所(画面外)
const unsigned int Toroi::SP5_RAIN_SPEED = 300;							//躁鬱雨の速度
const unsigned int Toroi::SP5_RAIN_COLLIDANT_SIZE = 10;					//躁鬱雨の当たり判定サイズ
const unsigned int Toroi::SP5_HEART_INTERVAL = 3000;					//ハート弾の生成間隔
const double Toroi::SP5_HEART_GENARATED_TOP_Y = -100;					//ハート弾が生成生成される場所
const double Toroi::SP5_HEART_GENARATED_BOTTOM_Y = 842;
const double Toroi::SP5_HEART_GENARATED_LEFT_X = -100;
const double Toroi::SP5_HEART_GENARATED_RIGHT_X = 720;
const double Toroi::SP5_HEART_SPEED = 400;								//ハート弾の速度
const unsigned int Toroi::SP5_HEART_COLLIDANT_SIZE = 10;				//ハート弾の当たり判定サイズ



const int Toroi::SP1_THINKING_TIME_LENGTH = 5000;						// [ms]
const unsigned int Toroi::SP1_TRICK_DURATION = 10000;					// [ミリ秒]
const unsigned int Toroi::SP1_TRICK_NOZZLES = 32;						// SP1のTrickのノズル数
const unsigned int Toroi::SP1_TRICK_NOZZLE_RADIUS = 80;					// SP1のTrickの弾の発射点の半径
const double Toroi::SP1_TRICK_NOZZLE_ROTATE_SPEED = (1.0 / 2.0) * pi;	// SP1のTrickのノズル回転速度
const unsigned int Toroi::SP1_TRICK_SHOT_SPEED = 250;					// SP1のTrickの弾の速さ
const unsigned int Toroi::SP1_TRICK_SHOT_INTERVAL = 300;				// SP1のTrickの発射間隔[ms]
//const unsigned int Toroi::SP1_TRICK_SHOT_TURN_POSTPONE_TIME = 400;	// [ミリ秒]
const unsigned int Toroi::SP1_TRICK_SHOT_COLLIDANT_SIZE = 10;			// SP1のTrickの弾の当たり判定サイズ


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

const double Toroi::SP1_ACTIVATE_HP_RATIO = 92.0 / 100.0;
const double Toroi::SP1_TERMINATE_HP_RATIO = 82.0 / 100.0;
const double Toroi::SP2_ACTIVATE_HP_RATIO = 75.0 / 100.0;
const double Toroi::SP3_ACTIVATE_HP_RATIO = 65.0 / 100.0;
const double Toroi::SP3_TERMINATE_HP_RATIO = 55.0 / 100.0;
const double Toroi::SP4_ACTIVATE_HP_RATIO = 48.0 / 100.0;
const double Toroi::SP5_ACTIVATE_HP_RATIO = 38.0 / 100.0;
const double Toroi::SP5_TERMINATE_HP_RATIO = 28.0 / 100.0;
const double Toroi::SP6_ACTIVATE_HP_RATIO = 21.0 / 100.0;
const double Toroi::SP7_ACTIVATE_HP_RATIO = 11.0 / 100.0;

const unsigned int Toroi::SP1_ACCOMPLISH_BONUS = 150000;
const unsigned int Toroi::SP2_ACCOMPLISH_BONUS = 200000;
const unsigned int Toroi::SP3_ACCOMPLISH_BONUS = 200000;
const unsigned int Toroi::SP4_ACCOMPLISH_BONUS = 350000;
const unsigned int Toroi::SP5_ACCOMPLISH_BONUS = 350000;
const unsigned int Toroi::SP6_ACCOMPLISH_BONUS = 500000;
const unsigned int Toroi::SP7_ACCOMPLISH_BONUS = 1000000;


Toroi::Toroi() :
	Character(
		INITIAL_POS_X,
		INITIAL_POS_Y,
		make_unique<CollideCircle>(INITIAL_POS_X, INITIAL_POS_Y, INITIAL_COLLIDANT_SIZE)
	),
	EnemyCharacter(INITIAL_HP),
	BossCharacter(NAME),
	status(ToroiStatus::SP5),
	sp1_mode(ToroiSP1Mode::INITIAL),
	sp1_last_questioned_clock(0),
	sp1_trick_last_started_clock(0),
	sp1_trick_last_emitted_clock(0),
	sp1_trick_nozzle_rotate_arg(0.0),
	sp5_rain_last_generated_clock(0),
	sp5_heart_last_generated_clock(0)
{
}


void Toroi::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	switch (status) {
	case ToroiStatus::NORMAL1:
		if (hp > INITIAL_HP * SP1_ACTIVATE_HP_RATIO) {
		}
		else {
			status = ToroiStatus::SP1;
		}
		break;

	case ToroiStatus::SP1:
		if (hp > INITIAL_HP * SP1_TERMINATE_HP_RATIO) {
			if (sp1_mode == ToroiSP1Mode::INITIAL) {
				sp1_last_questioned_clock = DxLib::GetNowCount();
				sp1_mode = ToroiSP1Mode::QUESTIONING;
			}
			else if (sp1_mode == ToroiSP1Mode::QUESTIONING) {
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
						3
					);
					InFieldPosition t_or_t_pos(
						InFieldPosition::MAX_MOVABLE_BOUNDARY_X / 2.0 - 88.0,
						InFieldPosition::MAX_MOVABLE_BOUNDARY_Y / 2.0 + 150.0
					);
					DxLib::DrawFormatString(
						t_or_t_pos.get_draw_position().x,
						t_or_t_pos.get_draw_position().y,
						Colors::YELLOW,
						"← Trick or Treat? →"
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
						"%.1lf",
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
					else
						sp1_mode = ToroiSP1Mode::TREAT;
				}
			}
			else if (sp1_mode == ToroiSP1Mode::TRICK) {
				int elapsed_time_since_last_started = DxLib::GetNowCount() - sp1_trick_last_started_clock;
				sp1_trick_nozzle_rotate_arg += SP1_TRICK_NOZZLE_ROTATE_SPEED * update_delta_time / 1000 / 1000;
				if (elapsed_time_since_last_started < SP1_TRICK_DURATION) {
					int elapsed_time_since_last_emitted = DxLib::GetNowCount() - sp1_trick_last_emitted_clock;
					if (elapsed_time_since_last_emitted > SP1_TRICK_SHOT_INTERVAL) {
						for (int i = 0; i < SP1_TRICK_NOZZLES; ++i) {

							double theta = 2 * pi / SP1_TRICK_NOZZLES * i + sp1_trick_nozzle_rotate_arg;
							double emit_x = position->x + SP1_TRICK_NOZZLE_RADIUS * cos(theta);
							double emit_y = position->y + SP1_TRICK_NOZZLE_RADIUS * sin(theta);
							Field::ENEMY_OFFENSIVES->push_back(make_unique<CurvingShot>(
								emit_x,
								emit_y,
								theta,
								SP1_TRICK_SHOT_SPEED,
								(1.0 / 12.0) * pi,
								SP1_TRICK_SHOT_COLLIDANT_SIZE,
								1,
								SkinID::TOROI_SP1_TRICK)
							);
							Field::ENEMY_OFFENSIVES->push_back(make_unique<CurvingShot>(
								emit_x,
								emit_y,
								theta,
								SP1_TRICK_SHOT_SPEED,
								- (1.0 / 12.0) * pi,
								SP1_TRICK_SHOT_COLLIDANT_SIZE,
								1,
								SkinID::TOROI_SP1_TRICK)
							);
						}
						sp1_trick_last_emitted_clock = DxLib::GetNowCount();
					}
				}
				else
					sp1_mode = ToroiSP1Mode::TRAP;
			}
			else if (sp1_mode == ToroiSP1Mode::TREAT) {

			}
			else if (sp1_mode == ToroiSP1Mode::TRAP) {

			}
		}
		else {
			status = ToroiStatus::NORMAL2;
		}
		break;

	case ToroiStatus::NORMAL2:
		if (hp > INITIAL_HP * SP2_ACTIVATE_HP_RATIO) {

		}
		else {
			status = ToroiStatus::SP2;
		}
		break;

	case ToroiStatus::SP2:
		if (hp > INITIAL_HP * SP3_ACTIVATE_HP_RATIO) {

		}
		else {
			status = ToroiStatus::SP3;
		}
		break;

	case ToroiStatus::SP3:
		if (hp > INITIAL_HP * SP3_TERMINATE_HP_RATIO) {

		}
		else {
			status = ToroiStatus::NORMAL3;
		}
		break;

	case ToroiStatus::NORMAL3:
		if (hp > INITIAL_HP * SP4_ACTIVATE_HP_RATIO) {

		}
		else {
			status = ToroiStatus::SP4;
		}
		break;

	case ToroiStatus::SP4:
		if (hp > INITIAL_HP * SP5_ACTIVATE_HP_RATIO) {

		}
		else {
			status = ToroiStatus::SP5;
		}
		break;

	case ToroiStatus::SP5:														//Stage3 Sp5「インターネット再興」
		if (hp > INITIAL_HP * SP5_TERMINATE_HP_RATIO) {
			//躁鬱雨
			int sp5_rain_generated_delta_time = DxLib::GetNowCount() - sp5_rain_last_generated_clock;
			if (sp5_rain_generated_delta_time > SP5_RAIN_INTERVAL) {					//発射のタイミング
				int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);

				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(	//躁弾
					random_x,
					SP5_RAIN_SOU_GENARATED_Y,
					1.0 / 2.0 * pi,
					SP5_RAIN_SPEED,
					SP5_RAIN_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP5_RAIN_SOU
					));

				random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);					//躁弾と鬱弾の生成位置をずらす

				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(	//鬱弾
					random_x,
					SP5_RAIN_UTU_GENARATED_Y,
					3.0 / 2.0 * pi,
					SP5_RAIN_SPEED,
					SP5_RAIN_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP5_RAIN_UTU
					));

				sp5_rain_last_generated_clock = DxLib::GetNowCount();			//発射したので最終発射時刻を更新

			}

			//ハート弾
			int sp5_heart_generated_delta_time = DxLib::GetNowCount() - sp5_heart_last_generated_clock;
			if (sp5_heart_generated_delta_time > SP5_HEART_INTERVAL) {
			
			unsigned int i = 0;
			for (i; i < 2; i++) {
					int random_x_top = DxLib::GetRand(Field::PIXEL_SIZE_X);
					//int random_y_top = DxLib::GetRand(Field::PIXEL_SIZE_Y);
					int random_x_bottom = DxLib::GetRand(Field::PIXEL_SIZE_X);
					//int random_y_bottom = DxLib::GetRand(Field::PIXEL_SIZE_Y);
					//int random_x_left = DxLib::GetRand(Field::PIXEL_SIZE_X);
					int random_y_left = DxLib::GetRand(Field::PIXEL_SIZE_Y);
					//int random_x_right = DxLib::GetRand(Field::PIXEL_SIZE_X);
					int random_y_right = DxLib::GetRand(Field::PIXEL_SIZE_Y);

					InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);

					double delta_x_top_mychr = my_chr_pos.x - random_x_top;
					double delta_y_top_mychr = my_chr_pos.y - SP5_HEART_GENARATED_TOP_Y;
					double delta_x_bottom_mychr = my_chr_pos.x - random_x_bottom;
					double delta_y_bottom_mychr = my_chr_pos.y - SP5_HEART_GENARATED_BOTTOM_Y;
					double delta_x_left_mychr = my_chr_pos.x - SP5_HEART_GENARATED_LEFT_X;
					double delta_y_left_mychr = my_chr_pos.y - random_y_left;
					double delta_x_right_mychr = my_chr_pos.x - SP5_HEART_GENARATED_RIGHT_X;
					double delta_y_right_mychr = my_chr_pos.y - random_y_right;

					double top_arg_toward_mychr = atan2(delta_y_top_mychr, delta_x_top_mychr);					//自機を向いた角度を生成
					double bottom_arg_toward_mychr = atan2(delta_y_bottom_mychr, delta_x_bottom_mychr);;
					double left_arg_toward_mychr = atan2(delta_y_left_mychr, delta_x_left_mychr);;
					double right_arg_toward_mychr = atan2(delta_y_right_mychr, delta_x_right_mychr);;

					SkinID random_heart_handles = SkinID::TOROI_SP5_HEART_RED;		//ImageHandlesの初期化
					random_heart_handles = Toroi::get_sp5_heart_random_image_handles();

					Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(		//上に生成
						random_x_top,
						SP5_HEART_GENARATED_TOP_Y,
						top_arg_toward_mychr,
						SP5_HEART_SPEED,
						SP5_HEART_COLLIDANT_SIZE,
						1,
						random_heart_handles
						));

					random_heart_handles = Toroi::get_sp5_heart_random_image_handles();

					Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(		//下に生成
						random_x_bottom,
						SP5_HEART_GENARATED_BOTTOM_Y,
						bottom_arg_toward_mychr,
						SP5_HEART_SPEED,
						SP5_HEART_COLLIDANT_SIZE,
						1,
						random_heart_handles
						));

					random_heart_handles = Toroi::get_sp5_heart_random_image_handles();

					Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(		//左に生成
						SP5_HEART_GENARATED_LEFT_X,
						random_y_left,
						left_arg_toward_mychr,
						SP5_HEART_SPEED,
						SP5_HEART_COLLIDANT_SIZE,
						1,
						random_heart_handles
						));

					random_heart_handles = Toroi::get_sp5_heart_random_image_handles();

					Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(		//右に生成
						SP5_HEART_GENARATED_RIGHT_X,
						random_y_right,
						right_arg_toward_mychr,
						SP5_HEART_SPEED,
						SP5_HEART_COLLIDANT_SIZE,
						1,
						random_heart_handles
						));
				}
				sp5_heart_last_generated_clock = DxLib::GetNowCount();			//発射したので最終発射時刻を更新

			}
			


		}
		else {
			status = ToroiStatus::NORMAL4;
		}
		break;

	case ToroiStatus::NORMAL4:
		if (hp > INITIAL_HP * SP6_ACTIVATE_HP_RATIO) {

		}
		else {
			status = ToroiStatus::SP6;
		}
		break;

	case ToroiStatus::SP6:
		if (hp > INITIAL_HP * SP7_ACTIVATE_HP_RATIO) {
			
		}
		else {
			status = ToroiStatus::SP7;
		}
		break;

	case ToroiStatus::SP7:
		if (hp > 0) {

		}
		else {

		}
		break;
	}
	collidant->update(position);
	last_updated_clock = DxLib::GetNowHiPerformanceCount();
}


void Toroi::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_TOROI, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}

enum SkinID Toroi::get_sp5_heart_random_image_handles() {
	SkinID HeartHandles = SkinID::TOROI_SP5_HEART_RED;		//ImageHandlesの初期化
	int sp5_heart_random_image_handle_case_num = DxLib::GetRand(8) + 1;

	switch (sp5_heart_random_image_handle_case_num) {
	case 1:
		HeartHandles = SkinID::TOROI_SP5_HEART_RED;		//ImageHandlesを割当
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