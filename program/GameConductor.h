﻿#pragma once
#include <memory>
#include <vector>
#include "DxLib.h"
#include "enum.h"
#include "Scenario/Scenario.h"
#include "NarrativePop.h"
//#include "Scoreboard.h"
//#include "Scenario/Stage1.h"

using std::unique_ptr;
using std::vector;
using EffectID = unsigned int;

class Scoreboard;
class Stage1;

class GameConductor {
private:
	unique_ptr<Scoreboard> scoreboard;
	int game_started_clock;
	double game_time;
	int continue_count;
	EffectID my_crash_effect_id;
	int my_crash_effect_start;
	int my_crash_effect_end;
	bool my_crash_effect_is_there;
	static double SURVIVAL_TIME;
	static unsigned int SURVIVAL_TIME_SCORE;
	static const unsigned int SURVIVAL_BONUS_RATE;
	static bool SURVIVAL_BONUS_ENABLE_FLAG;
	static int SURVIVAL_BONUS_LAST_ENABLED_CLOCK;
	static int CONTINUE_MAX;
	static bool FIELD_UPDATE_ENABLE_FLAG;
	static bool FIELD_UPDATE_STOP_REQUESTED_FLAG;
public:
	static Stage NOW_STAGE;
	static unique_ptr<Scenario> STAGE;
	static unsigned int SCORE;
	static unsigned int TECHNICAL_SCORE;
	static bool GAMEOVER_FLAG;
	static bool GAMECLEAR_FLAG;
	static bool STAGE1_CLEAR_FLAG;
	static bool STAGE2_CLEAR_FLAG;
	static bool STAGE3_CLEAR_FLAG;
	static vector<unique_ptr<NarrativePop>> NARRATIVE_POPS;
	static void INITIALIZE();
	static void ENABLE_SURVIVAL_BONUS();
	static void DISABLE_SURVIVAL_BONUS();
	static void RESET_SCORE();
	static void REQUEST_FIELD_UPDATE_STOP();
	GameConductor();
	~GameConductor();
	void update();
	void draw_score();
	void draw_my_hp();
	void draw_continue();
	void my_crash();
};
