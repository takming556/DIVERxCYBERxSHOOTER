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
	int game_started_clock;
	double game_time;
	unsigned int survival_time_score;
	static const unsigned int SURVIVAL_BONUS;
public:
	static Stage NOW_STAGE;
	static unique_ptr<Scenario> STAGE;
	static unsigned int SCORE;
	static unsigned int TECHNICAL_SCORE;
	static bool SURVIVAL_BONUS_ENABLE_FLAG;
	static bool GAMEOVER_FLAG;
	static bool GAMECLEAR_FLAG;
	static bool STAGE1_CLEAR_FLAG;
	static bool STAGE2_CLEAR_FLAG;
	static bool STAGE3_CLEAR_FLAG;
	static vector<NarrativePop> NARRATIVE_POPS;
	static void INITIALIZE();
	GameConductor();
	~GameConductor();
	void update();
	void draw_score();
	void draw_my_hp();
};
