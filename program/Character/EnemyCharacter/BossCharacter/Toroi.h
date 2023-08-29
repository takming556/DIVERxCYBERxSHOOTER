#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Barrage/Emission/StraightShotEmission/RotatingStraightShotEmission.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "enum.h"

using std::string;
using std::unique_ptr;
using std::vector;

class Toroi : public BossCharacter {
private:
	ToroiStatus status;
	ToroiSP1Mode sp1_mode;
	int sp1_last_questioned_clock;
	int sp1_trick_last_started_clock;
	int sp1_trick_last_emitted_clock;
	double sp1_trick_nozzle_rotate_arg;
	int sp1_treat_last_started_clock;
	int sp1_treat_last_threw_clock;
	int sp5_rain_last_generated_clock;
	int sp5_heart_last_generated_clock;
	ToroiSP6Mode sp6_mode;
	vector<unique_ptr<RotatingStraightShotEmission>> sp6_ran_nozzles;
	int sp6_ran_count;
	double sp6_ran_nozzle_radius;
	int sp6_ru_inital_started_clock;
	int sp6_ru_started_clock;
	int sp6_ru_potato_last_generated_clock;
	int sp6_ru_tomato_tick_last_generated_clock;
	int sp6_ru_tomato_fire_last_generated_clock;
	int sp6_ru_tomato_tick_count;

	static const string NAME;
	static const int INITIAL_POS_X;
	static const int INITIAL_POS_Y;
	static const unsigned int INITIAL_COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const int SP1_THINKING_TIME_LENGTH;
	static const unsigned int SP1_TRICK_DURATION;
	static const unsigned int SP1_TRICK_NOZZLES;
	static const unsigned int SP1_TRICK_NOZZLE_RADIUS;
	static const double SP1_TRICK_NOZZLE_ROTATE_SPEED;
	static const unsigned int SP1_TRICK_SHOT_INTERVAL;
	static const unsigned int SP1_TRICK_SHOT_SPEED;
	static const unsigned int SP1_TRICK_SHOT_COLLIDANT_SIZE;
	static const unsigned int SP1_TREAT_DURATION;
	static const unsigned int SP1_TREAT_THROW_AMOUNT;
	static const unsigned int SP1_TREAT_THROW_INTERVAL;

	static const unsigned int SP5_RAIN_INTERVAL;						// ÁNüTâJÇÃê∂ê¨ä‘äu(ÁNüTã§í )
	static const double SP5_RAIN_SOU_GENARATED_Y;						// ÁN
	static const double SP5_RAIN_UTU_GENARATED_Y;						// üT
	static const unsigned int SP5_RAIN_SPEED;							// ÁNüTâJÇÃë¨ìx(ÁNüTã§í )
	static const unsigned int SP5_RAIN_COLLIDANT_SIZE;					// ÁNüTâJÇÃìñÇΩÇËîªíËÉTÉCÉY(ÁNüTã§í )
	static const unsigned int SP5_HEART_INTERVAL;
	static const double SP5_HEART_GENARATED_TOP_Y;
	static const double SP5_HEART_GENARATED_BOTTOM_Y;
	static const double SP5_HEART_GENARATED_LEFT_X;
	static const double SP5_HEART_GENARATED_RIGHT_X;
	static const double SP5_HEART_SPEED;
	static const unsigned int SP5_HEART_COLLIDANT_SIZE;

	static const unsigned int SP6_RAN_NOZZLE_INIT_RADIUS;				// èâä˙îºåa
	static const unsigned int SP6_RAN_MAIN_NOZZLES_AMOUNT;				// ÉmÉYÉã(ëÂ)ÇÃêî
	static const unsigned int SP6_RAN_SUB_NOZZLES_AMOUNT;				// ÉmÉYÉã(è¨)ÇÃêî
	static const double SP6_RAN_SUB_NOZZLES_ROTATE_SPEED;				// ÉmÉYÉã(è¨)ÇÃâÒì]ë¨ìx
	static const unsigned int SP6_RAN_SHOT_INTERVAL;					// ÉmÉYÉã(è¨)Ç©ÇÁÇÃÉVÉáÉbÉgÇÃî≠éÀä‘äu
	static const double SP6_RAN_SHOT_SPEED;								// ÉmÉYÉã(è¨)Ç©ÇÁÇÃÉVÉáÉbÉgÇÃë¨ìx
	static const unsigned int SP6_RAN_SHOT_COLLIDANT_SIZE;				// ÉmÉYÉã(è¨)Ç©ÇÁÇÃÉVÉáÉbÉgÇÃìñÇΩÇËîªíËÉTÉCÉY
	static const unsigned int SP6_RAN_CONTRACTION_SPEED;				// â~ÇÃé˚èkë¨ìx

	static const unsigned int SP6_RU_INITAL_LIMITED_TIME;
	static const unsigned int SP6_RU_LIMITED_TIME;
	static const unsigned int SP6_RU_POTATO_INTERVAL;
	static const double SP6_RU_POTATO_GENARATED_Y;
	static const unsigned int SP6_RU_POTATO_SPEED;
	static const unsigned int SP6_RU_POTATO_COLLIDANT_SIZE;
	static const unsigned int SP6_RU_TOMATO_TICK_INTERVAL;
	static const unsigned int SP6_RU_TOMATO_FIRE_INTERVAL;
	static const unsigned int SP6_RU_TOMATO_SPEED;
	static const unsigned int SP6_RU_TOMATO_COLLIDANT_SIZE;
	static const unsigned int SP6_RU_TOMATO_NOZZLES;
	static const unsigned int SP6_RU_TOMATO_TICK_COUNT_MAX;

	static const unsigned int SP6_POSE_RAN_A_X_LEFT;
	static const unsigned int SP6_POSE_RAN_A_X_RIGHT;
	static const unsigned int SP6_POSE_RAN_A_Y;
	static const unsigned int SP6_POSE_RAN_A_EXTRATE;
	static const double SP6_POSE_RAN_A_RADIAN_LEFT;
	static const double SP6_POSE_RAN_A_RADIAN_RIGHT;
	static const unsigned int SP6_POSE_RAN_B_X_LEFT;
	static const unsigned int SP6_POSE_RAN_B_X_RIGHT;
	static const unsigned int SP6_POSE_RAN_B_Y;
	static const unsigned int SP6_POSE_RAN_B_EXTRATE;
	static const double SP6_POSE_RAN_B_RADIAN_LEFT;
	static const double SP6_POSE_RAN_B_RADIAN_RIGHT;
	static const unsigned int SP6_POSE_RU_X_LEFT;
	static const unsigned int SP6_POSE_RU_X_RIGHT;
	static const unsigned int SP6_POSE_RU_Y;
	static const unsigned int SP6_POSE_RU_EXTRATE;
	static const double SP6_POSE_RU_RADIAN_LEFT;
	static const double SP6_POSE_RU_RADIAN_RIGHT;

	static const unsigned int INITIAL_HP;
	static const double SP1_ACTIVATE_HP_RATIO;
	static const double SP1_TERMINATE_HP_RATIO;
	static const double SP2_ACTIVATE_HP_RATIO;
	static const double SP3_ACTIVATE_HP_RATIO;
	static const double SP3_TERMINATE_HP_RATIO;
	static const double SP4_ACTIVATE_HP_RATIO;
	static const double SP5_ACTIVATE_HP_RATIO;
	static const double SP5_TERMINATE_HP_RATIO;
	static const double SP6_ACTIVATE_HP_RATIO;
	static const double SP7_ACTIVATE_HP_RATIO;

	enum SkinID get_sp5_heart_random_image_handles();

public:
	Toroi();
	void update() override;
	void draw() override;

	static const unsigned int SP1_ACCOMPLISH_BONUS;
	static const unsigned int SP2_ACCOMPLISH_BONUS;
	static const unsigned int SP3_ACCOMPLISH_BONUS;
	static const unsigned int SP4_ACCOMPLISH_BONUS;
	static const unsigned int SP5_ACCOMPLISH_BONUS;
	static const unsigned int SP6_ACCOMPLISH_BONUS;
	static const unsigned int SP7_ACCOMPLISH_BONUS;

};