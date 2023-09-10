#pragma once
#include <string>
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "enum.h"

using std::string;

class Neon : public BossCharacter {
private:
	NeonStatus status;

	double nm3_shot_arg;
	int nm3_last_generated_clock;
	int nm3_oval_image_handle_count;

	void nm1();
	void nm2();
	void nm3();
	void nm4();
	void sp1();
	void sp2();
	void sp3();
	void sp4();

	enum SkinID get_nm3_oval_image_handles();

	static const string NAME;
	static const int INITIAL_POS_X;
	static const int INITIAL_POS_Y;
	static const unsigned int INITIAL_COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;

	static const double NM3_SHOT_SPEED;
	static const unsigned int NM3_COLLIDANT_SIZE;
	static const unsigned int NM3_INTERVAL;

	static const unsigned int INITIAL_HP;
	static const double SP1_ACTIVATE_HP_RATIO;
	static const double SP1_TERMINATE_HP_RATIO;
	static const double SP2_ACTIVATE_HP_RATIO;
	static const double SP2_TERMINATE_HP_RATIO;
	static const double SP3_ACTIVATE_HP_RATIO;
	static const double SP3_TERMINATE_HP_RATIO;
	static const double SP4_ACTIVATE_HP_RATIO;
	static const double SP4_TERMINATE_HP_RATIO;

public:
	Neon();
	void update() override;
	void draw() override;

	static const unsigned int SP1_ACCOMPLISH_BONUS;
	static const unsigned int SP2_ACCOMPLISH_BONUS;
	static const unsigned int SP3_ACCOMPLISH_BONUS;
	static const unsigned int SP4_ACCOMPLISH_BONUS;
};