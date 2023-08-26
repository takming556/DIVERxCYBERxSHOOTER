#pragma once
#include <string>
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "enum.h"

using std::string;


class Toroi : public BossCharacter {
private:
	ToroiStatus status;
	ToroiSP1Mode sp1_mode;
	int sp1_last_questioned_clock;
	int sp1_trick_last_started_clock;
	int sp1_trick_last_emitted_clock;
	double sp1_trick_nozzle_rotate_arg;
	int sp5_rain_last_generated_clock;
	int sp5_heart_last_generated_clock;

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
	//static const unsigned int SP1_TRICK_SHOT_TURN_POSTPONE_TIME;
	static const unsigned int SP1_TRICK_SHOT_COLLIDANT_SIZE;

	static const unsigned int SP5_RAIN_INTERVAL;
	static const double SP5_RAIN_SOU_GENARATED_Y;
	static const double SP5_RAIN_UTU_GENARATED_Y;
	static const unsigned int SP5_RAIN_SPEED;
	static const unsigned int SP5_RAIN_COLLIDANT_SIZE;
	static const unsigned int SP5_HEART_INTERVAL;
	static const double SP5_HEART_GENARATED_TOP_Y;
	static const double SP5_HEART_GENARATED_BOTTOM_Y;
	static const double SP5_HEART_GENARATED_LEFT_X;
	static const double SP5_HEART_GENARATED_RIGHT_X;

	static const double SP5_HEART_SPEED;
	static const unsigned int SP5_HEART_COLLIDANT_SIZE;

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