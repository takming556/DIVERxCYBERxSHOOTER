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


using std::string;
using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;


const string Toroi::NAME("à§ê∂ÉgÉçÉC");
const int Toroi::INITIAL_POS_X = 310;
const int Toroi::INITIAL_POS_Y = 620;
const unsigned int Toroi::INITIAL_COLLIDANT_SIZE = 60;
const double Toroi::DRAW_EXTRATE = 0.07;
const unsigned int Toroi::SP5_RAIN_INTERVAL = 250;
const double Toroi::SP5_RAIN_SOU_GENARATED_Y = -100;	//ÁNâJÇ™ê∂ê¨Ç≥ÇÍÇÈèÍèä(âÊñ äO)
const double Toroi::SP5_RAIN_UTU_GENARATED_Y = 842;		//üTâJÇ™ê∂ê¨Ç≥ÇÍÇÈèÍèä(âÊñ äO)
const unsigned int Toroi::SP5_RAIN_SPEED = 300;			//ÁNüTâJÇÃë¨ìx
const unsigned int Toroi::SP5_RAIN_COLLIDANT_SIZE = 10;	//ÁNüTâJÇÃìñÇΩÇËîªíË



const int Toroi::SP1_THINKING_TIME_LENGTH = 5000;						// [ms]
const unsigned int Toroi::SP1_TRICK_DURATION = 10000;					// [É~Éäïb]
const unsigned int Toroi::SP1_TRICK_NOZZLES = 32;						// SP1ÇÃTrickÇÃÉmÉYÉãêî
const unsigned int Toroi::SP1_TRICK_NOZZLE_RADIUS = 80;					// SP1ÇÃTrickÇÃíeÇÃî≠éÀì_ÇÃîºåa
const double Toroi::SP1_TRICK_NOZZLE_ROTATE_SPEED = (1.0 / 2.0) * pi;	// SP1ÇÃTrickÇÃÉmÉYÉãâÒì]ë¨ìx
const unsigned int Toroi::SP1_TRICK_SHOT_SPEED = 250;					// SP1ÇÃTrickÇÃíeÇÃë¨Ç≥
const unsigned int Toroi::SP1_TRICK_SHOT_INTERVAL = 300;				// SP1ÇÃTrickÇÃî≠éÀä‘äu[ms]
//const unsigned int Toroi::SP1_TRICK_SHOT_TURN_POSTPONE_TIME = 400;	// [É~Éäïb]
const unsigned int Toroi::SP1_TRICK_SHOT_COLLIDANT_SIZE = 10;			// SP1ÇÃTrickÇÃíeÇÃìñÇΩÇËîªíËÉTÉCÉY


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
	status(ToroiStatus::SP1),
	sp1_mode(ToroiSP1Mode::INITIAL),
	sp1_last_questioned_clock(0),
	sp1_trick_last_started_clock(0),
	sp1_trick_last_emitted_clock(0),
	sp1_trick_nozzle_rotate_arg(0.0),
	sp5_rain_last_generated_clock(0)
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
						"Å© Trick or Treat? Å®"
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

	case ToroiStatus::SP5:														//Stage3 Sp5ÅuÉCÉìÉ^Å[ÉlÉbÉgçƒãªÅv
		if (hp > INITIAL_HP * SP5_TERMINATE_HP_RATIO) {
			//ÁNüTâJ
			int sp5_generated_delta_time = DxLib::GetNowCount() - sp5_rain_last_generated_clock;
			if (sp5_generated_delta_time > SP5_RAIN_INTERVAL) {					//î≠éÀÇÃÉ^ÉCÉ~ÉìÉO
				int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);

				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(	//ÁNíe
					random_x,
					SP5_RAIN_SOU_GENARATED_Y,
					1.0 / 2.0 * pi,
					SP5_RAIN_SPEED,
					SP5_RAIN_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP5_RAIN_SOU
					));
				
				random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);					//ÁNíeÇ∆üTíeÇÃê∂ê¨à íuÇÇ∏ÇÁÇ∑

				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(	//üTíe
					random_x,
					SP5_RAIN_UTU_GENARATED_Y,
					3.0 / 2.0 * pi,
					SP5_RAIN_SPEED,
					SP5_RAIN_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP5_RAIN_UTU
					));

				sp5_rain_last_generated_clock = DxLib::GetNowCount();			//î≠éÀÇµÇΩÇÃÇ≈ç≈èIî≠éÀéûçèÇçXêV

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