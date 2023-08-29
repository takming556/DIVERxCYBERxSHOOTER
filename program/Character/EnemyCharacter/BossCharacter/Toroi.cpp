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


using std::string;
using std::make_unique;
using std::sin;
using std::cos;
using std::numbers::pi;


const string Toroi::NAME("�����g���C");
const int Toroi::INITIAL_POS_X = 310;
const int Toroi::INITIAL_POS_Y = 620;
const unsigned int Toroi::INITIAL_COLLIDANT_SIZE = 60;
const double Toroi::DRAW_EXTRATE = 0.07;

const int Toroi::SP1_THINKING_TIME_LENGTH = 5000;						// [�~���b]
const unsigned int Toroi::SP1_TRICK_DURATION = 10000;					// [�~���b]
const unsigned int Toroi::SP1_TRICK_NOZZLES = 32;						// SP1��Trick�̃m�Y����
const unsigned int Toroi::SP1_TRICK_NOZZLE_RADIUS = 120;				// SP1��Trick�̒e�̔��˓_�̔��a
const double Toroi::SP1_TRICK_NOZZLE_ROTATE_SPEED = (1.0 / 2.0) * pi;	// SP1��Trick�̃m�Y����]���x
const unsigned int Toroi::SP1_TRICK_SHOT_SPEED = 250;					// SP1��Trick�̒e�̑���
const unsigned int Toroi::SP1_TRICK_SHOT_INTERVAL = 300;				// SP1��Trick�̔��ˊԊu[�~���b]
const unsigned int Toroi::SP1_TRICK_SHOT_COLLIDANT_SIZE = 10;			// SP1��Trick�̒e�̓����蔻��T�C�Y
const unsigned int Toroi::SP1_TREAT_DURATION = 100000;					// [�~���b]
const unsigned int Toroi::SP1_TREAT_THROW_AMOUNT = 64;
const unsigned int Toroi::SP1_TREAT_THROW_INTERVAL = 1500;				// [�~���b]

const unsigned int Toroi::SP5_RAIN_INTERVAL = 250;						// SP5���N�T�J�̔��ˊԊu(����)[�~���b]
const double Toroi::SP5_RAIN_SOU_GENERATED_Y = -100;					// SP5���N�J�����������Y���W(��ʊO��)
const double Toroi::SP5_RAIN_UTU_GENERATED_Y = 842;						// SP5�̟T�J�����������Y���W(��ʊO��)
const unsigned int Toroi::SP5_RAIN_SPEED = 300;							// SP5���N�T�J�̑��x(����)
const unsigned int Toroi::SP5_RAIN_COLLIDANT_SIZE = 10;					// SP5���N�T�J�̓����蔻��T�C�Y(����)
const unsigned int Toroi::SP5_HEART_INTERVAL = 3000;					// SP5�̃n�[�g�e�̔��ˊԊu[�~���b]
const double Toroi::SP5_HEART_GENERATED_TOP_Y = 842;					// SP5�̃n�[�g�e�����������Y���W(��ʊO��)
const double Toroi::SP5_HEART_GENERATED_BOTTOM_Y = -100;				// SP5�̃n�[�g�e�����������Y���W(��ʊO��)
const double Toroi::SP5_HEART_GENERATED_LEFT_X = -100;					// SP5�̃n�[�g�e�����������Y���W(��ʊO��)
const double Toroi::SP5_HEART_GENERATED_RIGHT_X = 720;					// SP5�̃n�[�g�e�����������Y���W(��ʊO�E)
const double Toroi::SP5_HEART_SPEED = 400;								// SP5�̃n�[�g�e�̑��x
const unsigned int Toroi::SP5_HEART_COLLIDANT_SIZE = 10;				// SP5�̃n�[�g�e�̓����蔻��T�C�Y

const unsigned int Toroi::SP6_RAN_NOZZLE_INIT_RADIUS = 800;				// SP6��RAN�̉�]�m�Y���̔��˓_�̏������a
const unsigned int Toroi::SP6_RAN_MAIN_NOZZLES_AMOUNT = 8;				// SP6��RAN�̃m�Y��(��)�̐�
const unsigned int Toroi::SP6_RAN_SUB_NOZZLES_AMOUNT = 4;				// SP6��RAN�̃m�Y��(��)�̐�
const double Toroi::SP6_RAN_SUB_NOZZLES_ROTATE_SPEED = 1.0 / 2.0 * pi;	// SP6��RAN�̃m�Y��(��)�̉�]���x
const unsigned int Toroi::SP6_RAN_SHOT_INTERVAL = 300;					// SP6��RAN�̃m�Y��(��)����̃V���b�g�̔��ˊԊu
const double Toroi::SP6_RAN_SHOT_SPEED = 200;							// SP6��RAN�̃m�Y��(��)����̃V���b�g�̑��x
const unsigned int Toroi::SP6_RAN_SHOT_COLLIDANT_SIZE = 10;				// SP6��RAN�̃m�Y��(��)����̃V���b�g�̓����蔻��T�C�Y
const unsigned int Toroi::SP6_RAN_CONTRACTION_SPEED = 50;				// SP6��RAN�̉~�̎��k���x[�s�N�Z��/�b]

const unsigned int Toroi::SP6_RU_INITAL_LIMITED_TIME = 3000;			// SP6��RU�̏����̐�������[�~���b]
const unsigned int Toroi::SP6_RU_LIMITED_TIME = 10000;					// SP6��RU�̐�������[�~���b]
const unsigned int Toroi::SP6_RU_POTATO_INTERVAL = 40;					// SP6��RU�̃|�e�g�e�̔��ˊԊu[�~���b]
const double Toroi::SP6_RU_POTATO_GENERATED_Y = 842;					// SP6��RU�̃|�e�g�e�����������Y���W(��ʊO��)
const unsigned int Toroi::SP6_RU_POTATO_SPEED = 600;					// SP6��RU�̃|�e�g�e�̑��x
const unsigned int Toroi::SP6_RU_POTATO_COLLIDANT_SIZE = 10;			// SP6��RU�̃|�e�g�e�̓����蔻��T�C�Y
const unsigned int Toroi::SP6_RU_TOMATO_TICK_INTERVAL = 100;			// SP6��RU�̃g�}�g�e�̘A��(��)�Ԋu[�~���b]
const unsigned int Toroi::SP6_RU_TOMATO_FIRE_INTERVAL = 300;			// SP6��RU�̃g�}�g�e�̘A��(��)�Ԋu[�~���b]
const unsigned int Toroi::SP6_RU_TOMATO_SPEED = 400;					// SP6��RU�̃g�}�g�e�̑��x
const unsigned int Toroi::SP6_RU_TOMATO_COLLIDANT_SIZE = 20;			// SP6��RU�̃g�}�g�e�̓����蔻��T�C�Y
const unsigned int Toroi::SP6_RU_TOMATO_NOZZLES = 16;					// SP6��RU�̃g�}�g�e�̃m�Y����
const unsigned int Toroi::SP6_RU_TOMATO_TICK_COUNT_MAX = 3;				// SP6��RU�̃g�}�g�e�̘A��(��)�̍ő�A�ˉ�

const unsigned int Toroi::SP6_POSE_RAN_A_X_LEFT = 350;					// SP6�̃|�[�Y�̃���1��ڂ�X���W(��)
const unsigned int Toroi::SP6_POSE_RAN_A_X_RIGHT = 350;					// SP6�̃|�[�Y�̃���1��ڂ�X���W(�E)
const unsigned int Toroi::SP6_POSE_RAN_A_Y = 160;						// SP6�̃|�[�Y�̃���1��ڂ�Y���W(����)
const unsigned int Toroi::SP6_POSE_RAN_A_EXTRATE = 1.0;					// SP6�̃���1��ڂ̃|�[�Y�̊g�嗦
const double Toroi::SP6_POSE_RAN_A_RADIAN_LEFT = 1.0 / 4.0 * pi;		// SP6�̃���1��ڂ̃|�[�Y�̉E�̊p�x
const double Toroi::SP6_POSE_RAN_A_RADIAN_RIGHT = 3.0 / 4.0 * pi;		// SP6�̃���1��ڂ̃|�[�Y�̍��̊p�x
const unsigned int Toroi::SP6_POSE_RAN_B_X_LEFT = 350 + 30;				// SP6�̃|�[�Y�̃���2��ڂ�X���W(��)
const unsigned int Toroi::SP6_POSE_RAN_B_X_RIGHT = 350 - 30;			// SP6�̃|�[�Y�̃���2��ڂ�X���W(�E)
const unsigned int Toroi::SP6_POSE_RAN_B_Y = 160;						// SP6�̃|�[�Y�̃���2��ڂ�Y���W(����)
const unsigned int Toroi::SP6_POSE_RAN_B_EXTRATE = 1.0;					// SP6�̃���2��ڂ̃|�[�Y�̊g�嗦
const double Toroi::SP6_POSE_RAN_B_RADIAN_LEFT = 1.0 / 4.0 * pi;		// SP6�̃���2��ڂ̃|�[�Y�̉E�̊p�x
const double Toroi::SP6_POSE_RAN_B_RADIAN_RIGHT = 3.0 / 4.0 * pi;		// SP6�̃���2��ڂ̃|�[�Y�̍��̊p�x
const unsigned int Toroi::SP6_POSE_RU_X_LEFT = 350 - 40;				// SP6�̃|�[�Y�̃��[��X���W(��)
const unsigned int Toroi::SP6_POSE_RU_X_RIGHT = 350 + 40;				// SP6�̃|�[�Y�̃��[��X���W(�E)
const unsigned int Toroi::SP6_POSE_RU_Y = 80;							// SP6�̃|�[�Y�̃��[��Y���W(����)
const unsigned int Toroi::SP6_POSE_RU_EXTRATE = 1.0;					// SP6�̃��[�̃|�[�Y�̊g�嗦
const double Toroi::SP6_POSE_RU_RADIAN_LEFT = 2.0 / 4.0 * pi;			// SP6�̃��[�̃|�[�Y�̉E�̊p�x
const double Toroi::SP6_POSE_RU_RADIAN_RIGHT = 2.0 / 4.0 * pi;			// SP6�̃��[�̃|�[�Y�̍��̊p�x



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
	status(ToroiStatus::SP1),					// �ǂ����J�n�n�_�Ƃ��邩
	sp1_mode(ToroiSP1Mode::INITIAL),
	sp1_last_questioned_clock(0),
	sp1_trick_last_started_clock(0),
	sp1_trick_last_emitted_clock(0),
	sp1_trick_nozzle_rotate_arg(0.0),
	sp1_treat_last_started_clock(0),
	sp1_treat_last_threw_clock(0),
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
}


void Toroi::update() {
	switch (status) {
	case ToroiStatus::NORMAL1:
		nm1();
		break;

	case ToroiStatus::SP1:		// �uTrick or Treat or Trap?�v
		sp1();
		break;

	case ToroiStatus::NORMAL2:
		nm2();
		break;

	case ToroiStatus::SP2:		// �u���q�\�ԃN���[�i�[�v
		sp2();
		break;

	case ToroiStatus::SP3:		// �u�Ԃ����݂͈���h�炷�v
		sp3();
		break;

	case ToroiStatus::NORMAL3:
		nm3();
		break;

	case ToroiStatus::SP4:		// �u�炫�ւ�A�����߂̔~�v
		sp4();
		break;

	case ToroiStatus::SP5:		// �u�C���^�[�l�b�g�ċ��v
		sp5();
		break;

	case ToroiStatus::NORMAL4:
		nm4();
		break;

	case ToroiStatus::SP6:		// �uEx-tROiA.ru4(D)�v
		sp6();
		break;

	case ToroiStatus::SP7:
		sp7();
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


void Toroi::nm1() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP1_ACTIVATE_HP_RATIO) {
	}
	else {
		status = ToroiStatus::SP1;
	}
}


void Toroi::nm2() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP2_ACTIVATE_HP_RATIO) {

	}
	else {
		status = ToroiStatus::SP2;
	}
}


void Toroi::nm3() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP4_ACTIVATE_HP_RATIO) {

	}
	else {
		status = ToroiStatus::SP4;
	}
}


void Toroi::nm4() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP6_ACTIVATE_HP_RATIO) {

	}
	else {
		status = ToroiStatus::SP6;
	}
}


void Toroi::sp1() {		// �uTrick or Treat or Trap?�v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

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
					"�� Trick or Treat? ��"
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
				else {
					sp1_mode = ToroiSP1Mode::TREAT;
					sp1_treat_last_started_clock = DxLib::GetNowCount();
				}
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
							-(1.0 / 12.0) * pi,
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
			int elapsed_time_since_last_started = DxLib::GetNowCount() - sp1_treat_last_started_clock;
			if (elapsed_time_since_last_started < SP1_TREAT_DURATION) {
				int elapsed_time_since_last_threw = DxLib::GetNowCount() - sp1_treat_last_threw_clock;
				if (elapsed_time_since_last_threw > SP1_TREAT_THROW_INTERVAL) {
					for (int i = 0; i < SP1_TREAT_THROW_AMOUNT; ++i) {
						Field::ENEMY_OFFENSIVES->push_back(make_unique<ParabolicShot>(
							position->x,
							position->y,
							static_cast<double>(DxLib::GetRand(96)) / 96.0 * pi,
							DxLib::GetRand(300),
							150.0,
							-1.0 / 2.0 * pi,
							10,
							1,
							SkinID::NORMAL_BLUE)
						);
					}
					sp1_treat_last_threw_clock = DxLib::GetNowCount();
				}
			}
			else
				sp1_mode = ToroiSP1Mode::TRAP;

		}
		else if (sp1_mode == ToroiSP1Mode::TRAP) {

		}
	}
	else {
		status = ToroiStatus::NORMAL2;
	}
}


void Toroi::sp2() {		// �u���q�\�ԃN���[�i�[�v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP3_ACTIVATE_HP_RATIO) {

	}
	else {
		status = ToroiStatus::SP3;
	}
}


void Toroi::sp3() {		// �u�Ԃ����݂͈���h�炷�v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP3_TERMINATE_HP_RATIO) {

	}
	else {
		status = ToroiStatus::NORMAL3;
	}
}


void Toroi::sp4() {		// �u�炫�ւ�A�����߂̔~�v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP5_ACTIVATE_HP_RATIO) {

	}
	else {
		status = ToroiStatus::SP5;
	}
}


void Toroi::sp5() {		// �u�C���^�[�l�b�g�ċ��v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;

	if (hp > INITIAL_HP * SP5_TERMINATE_HP_RATIO) {
		// �N�T�J
		int sp5_rain_generated_delta_time = DxLib::GetNowCount() - sp5_rain_last_generated_clock;
		if (sp5_rain_generated_delta_time > SP5_RAIN_INTERVAL) {			// ���˂̃^�C�~���O
			int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);
			// �N�e
			Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
				random_x,
				SP5_RAIN_SOU_GENERATED_Y,
				1.0 / 2.0 * pi,
				SP5_RAIN_SPEED,
				SP5_RAIN_COLLIDANT_SIZE,
				1,
				SkinID::TOROI_SP5_RAIN_SOU
			));
			// �T�e
			random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);					// �N�e�ƟT�e�̐����ʒu�����炷
			Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
				random_x,
				SP5_RAIN_UTU_GENERATED_Y,
				3.0 / 2.0 * pi,
				SP5_RAIN_SPEED,
				SP5_RAIN_COLLIDANT_SIZE,
				1,
				SkinID::TOROI_SP5_RAIN_UTU
			));
			sp5_rain_last_generated_clock = DxLib::GetNowCount();			// ���˂����̂ōŏI���ˎ������X�V
		}
		// �n�[�g�e
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
				double top_arg_toward_mychr = atan2(delta_y_top_mychr, delta_x_top_mychr);				// ���@���������p�x�𐶐�
				double bottom_arg_toward_mychr = atan2(delta_y_bottom_mychr, delta_x_bottom_mychr);;
				double left_arg_toward_mychr = atan2(delta_y_left_mychr, delta_x_left_mychr);;
				double right_arg_toward_mychr = atan2(delta_y_right_mychr, delta_x_right_mychr);;
				SkinID random_heart_handles = SkinID::TOROI_SP5_HEART_RED;								// ImageHandles�̏�����
				// �n�[�g�e(��ʊO��ɐ���)
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();
				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					random_x_top,
					SP5_HEART_GENERATED_TOP_Y,
					top_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				));
				// �n�[�g�e(��ʊO���ɐ���)
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();
				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					random_x_bottom,
					SP5_HEART_GENERATED_BOTTOM_Y,
					bottom_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				));
				// �n�[�g�e(��ʊO���ɐ���)
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();
				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					SP5_HEART_GENERATED_LEFT_X,
					random_y_left,
					left_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				));
				// �n�[�g�e(��ʊO�E�ɐ���)
				random_heart_handles = Toroi::get_sp5_heart_random_image_handles();
				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					SP5_HEART_GENERATED_RIGHT_X,
					random_y_right,
					right_arg_toward_mychr,
					SP5_HEART_SPEED,
					SP5_HEART_COLLIDANT_SIZE,
					1,
					random_heart_handles
				));
				DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
			}
			sp5_heart_last_generated_clock = DxLib::GetNowCount();			// ���˂����̂ōŏI���ˎ������X�V
		}
	}
	else {
		status = ToroiStatus::NORMAL4;
	}
}


void Toroi::sp6() {		// �uEx-tROiA.ru4(D)�v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > INITIAL_HP * SP7_ACTIVATE_HP_RATIO) {
		switch (sp6_mode) {
		case ToroiSP6Mode::RAN_A_INITIAL: {
			sp6_ran_nozzles.clear();
			sp6_ran_nozzle_radius = SP6_RAN_NOZZLE_INIT_RADIUS;									// �m�Y�����a�̏�����
			for (int i = 0; i < SP6_RAN_MAIN_NOZZLES_AMOUNT; ++i) {
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;						// i�m�Y���ڂ̊p�x
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
		case ToroiSP6Mode::RAN_A: {		// ����1���
			sp6_ran_nozzle_radius -= (double)(update_delta_time * SP6_RAN_CONTRACTION_SPEED) / 1000 / 1000;		// update_delta_time���}�C�N���b�Ȃ̂Ōv�Z����
			for (int i = 0; i < SP6_RAN_MAIN_NOZZLES_AMOUNT; ++i) {
				if (sp6_ran_nozzle_radius < 0) {
					sp6_ran_nozzles.at(i)->pause_emitting();
					sp6_mode = ToroiSP6Mode::RAN_B_INITIAL;
				}
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;						// i�m�Y���ڂ̊p�x
				double update_x = position->x + sp6_ran_nozzle_radius * cos(theta);
				double update_y = position->y + sp6_ran_nozzle_radius * sin(theta);
				sp6_ran_nozzles.at(i)->update(update_x, update_y);
			}
			DxLib::DrawRotaGraph(																		// ����1��ڂ̃|�[�Y
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
		case ToroiSP6Mode::RAN_B_INITIAL: {		// RAN_A�Ŏg�p�����ϐ��̃��Z�b�g
			sp6_ran_nozzles.clear();
			sp6_ran_nozzle_radius = SP6_RAN_NOZZLE_INIT_RADIUS;									// �m�Y�����a�̏�����
			for (int i = 0; i < SP6_RAN_MAIN_NOZZLES_AMOUNT; ++i) {
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;						// i�m�Y���ڂ̊p�x
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
		case ToroiSP6Mode::RAN_B: {		// ����2���
			sp6_ran_nozzle_radius -= (double)(update_delta_time * SP6_RAN_CONTRACTION_SPEED) / 1000 / 1000;		// update_delta_time���}�C�N���b�Ȃ̂Ōv�Z����
			for (int i = 0; i < SP6_RAN_MAIN_NOZZLES_AMOUNT; ++i) {
				if (sp6_ran_nozzle_radius < 0) {
					sp6_ran_nozzles.at(i)->pause_emitting();
					sp6_ru_inital_started_clock = DxLib::GetNowCount();
					sp6_mode = ToroiSP6Mode::RU_INITAL;
				}
				double theta = 2 * pi / SP6_RAN_MAIN_NOZZLES_AMOUNT * i;						// i�m�Y���ڂ̊p�x
				double update_x = position->x + sp6_ran_nozzle_radius * cos(theta);
				double update_y = position->y + sp6_ran_nozzle_radius * sin(theta);
				sp6_ran_nozzles.at(i)->update(update_x, update_y);
			}
			DxLib::DrawRotaGraph(																		// ����2��ڂ̃|�[�Y
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
		case ToroiSP6Mode::RU_INITAL: {		// ���[�̏���
			sp6_ru_tomato_tick_count = 0;														// �g�}�g�e�̘A�ː��J�E���g��������
			int sp6_ru_inital_elapsed_time = DxLib::GetNowCount() - sp6_ru_inital_started_clock;
			if (sp6_ru_inital_elapsed_time > SP6_RU_INITAL_LIMITED_TIME) {						// ���Ԃ��o�߂����烋�[��
				sp6_ru_started_clock = DxLib::GetNowCount();
				sp6_mode = ToroiSP6Mode::RU;
			}
			break;
		}
		case ToroiSP6Mode::RU: {		// ���[
			int sp6_ru_elapsed_time = DxLib::GetNowCount() - sp6_ru_started_clock;
			if (sp6_ru_elapsed_time > SP6_RU_LIMITED_TIME) {
				sp6_mode = ToroiSP6Mode::RAN_A_INITIAL;
			}
			// �|�e�g�e
			int sp6_ru_potato_generated_delta_time = DxLib::GetNowCount() - sp6_ru_potato_last_generated_clock;
			if (sp6_ru_potato_generated_delta_time > SP6_RU_POTATO_INTERVAL) {					// ���˂̃^�C�~���O
				int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);
				Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
					random_x,
					SP6_RU_POTATO_GENERATED_Y,
					3.0 / 2.0 * pi,
					SP6_RU_POTATO_SPEED,
					SP6_RU_POTATO_COLLIDANT_SIZE,
					1,
					SkinID::TOROI_SP6_RU_POTATO
				));
				sp6_ru_potato_last_generated_clock = DxLib::GetNowCount();						// ���˂����̂ōŏI���ˎ������X�V
			}
			//�g�}�g�e
			int sp6_ru_tomato_fire_generated_delta_time = DxLib::GetNowCount() - sp6_ru_tomato_fire_last_generated_clock;
			if (sp6_ru_tomato_fire_generated_delta_time > SP6_RU_TOMATO_FIRE_INTERVAL) {
				int sp6_ru_tomato_tick_generated_delta_time = DxLib::GetNowCount() - sp6_ru_tomato_tick_last_generated_clock;
				if (sp6_ru_tomato_tick_generated_delta_time > SP6_RU_TOMATO_TICK_INTERVAL) {
					for (int i = 0; i < SP6_RU_TOMATO_NOZZLES; ++i) {							// �m�Y�������J��Ԃ��đS���ʒe�����
						double theta = 2 * pi / SP6_RU_TOMATO_NOZZLES * i;
						Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
							position->x,
							position->y,
							theta,
							SP6_RU_TOMATO_SPEED,
							SP6_RU_TOMATO_COLLIDANT_SIZE,
							1,
							SkinID::TOROI_SP6_RU_TOMATO)
						);
					}
					DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
					sp6_ru_tomato_tick_last_generated_clock = DxLib::GetNowCount();
					++sp6_ru_tomato_tick_count;
				}
				if (sp6_ru_tomato_tick_count == SP6_RU_TOMATO_TICK_COUNT_MAX) {					// �A��(��)�̘A�ˉ񐔂����������Ƃ�
					sp6_ru_tomato_fire_last_generated_clock = DxLib::GetNowCount();				// �A��(��)�̍ŏI�������Ԃ�ݒ�
					sp6_ru_tomato_tick_count = 0;
				}
			}
			DxLib::DrawRotaGraph(																		// ���[�̃|�[�Y
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
		status = ToroiStatus::SP7;
	}
}


void Toroi::sp7() {		// �u����Ȃ��~�蒍���A�d���̗܁v
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	if (hp > 0) {

	}
	else {

	}
}


enum SkinID Toroi::get_sp5_heart_random_image_handles() {
	SkinID HeartHandles = SkinID::TOROI_SP5_HEART_RED;						// ImageHandles�̏�����
	int sp5_heart_random_image_handle_case_num = DxLib::GetRand(8) + 1;

	switch (sp5_heart_random_image_handle_case_num) {
	case 1:
		HeartHandles = SkinID::TOROI_SP5_HEART_RED;							// ImageHandles������
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