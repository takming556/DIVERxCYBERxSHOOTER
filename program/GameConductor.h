#pragma once
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

class Scoreboard;
class Stage1;

class GameConductor {
private:
	unique_ptr<Scoreboard> scoreboard;
	int gameStartedClock;
	double gameTime;
	static double SURVIVAL_TIME;
	static unsigned int SURVIVAL_TIME_SCORE;
	static const unsigned int SURVIVAL_BONUS_RATE;
	static bool IS_SURVIVAL_BONUS_ENABLED;
	static int SURVIVAL_BONUS_LAST_ENABLED_CLOCK;
	static unsigned int MAX_CONTINUE_COUNT;
	static bool IS_PRACTICE_MODE_ENABLED;
	static bool IS_FIELD_UPDATE_ENABLED;
	static bool IS_FIELD_UPDATE_STOP_REQUESTED;
public:
	static Stage CURRENT_STAGE;
	static unique_ptr<Scenario> STAGE;
	static unsigned int SCORE;
	static unsigned int TECHNICAL_SCORE;
	static unsigned int CONTINUE_COUNT;
	static bool GAMEOVER_FLAG;
	static bool GAMECLEAR_FLAG;
	static bool STAGE1_CLEAR_FLAG;
	static bool STAGE2_CLEAR_FLAG;
	static bool STAGE3_CLEAR_FLAG;
	static vector<unique_ptr<NarrativePop>> NARRATIVE_POPS;
	static void INITIALIZE(Stage start_from, bool is_practice_mode);
	static void ENABLE_SURVIVAL_BONUS();
	static void DISABLE_SURVIVAL_BONUS();
	static void RESET_SCORE();
	static void REQUEST_FIELD_UPDATE_STOP();
	GameConductor();
	~GameConductor();
	void Update();
	void DrawScore();
	void DrawMyHp();
	void DrawContinueCount();
};