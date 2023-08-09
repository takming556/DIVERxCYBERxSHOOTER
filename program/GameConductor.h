#pragma once
#include <memory>
#include "enum.h"
#include "Scenario/Scenario.h"
//#include "Scoreboard.h"
//#include "Scenario/Stage1.h"

using std::unique_ptr;

class Scoreboard;
class Stage1;

class GameConductor {
private:
	Stage now_stage;
	unique_ptr<Scoreboard> scoreboard;
	unique_ptr<Scenario> stage;
	int last_updated_clock;
	double game_time;
	static const unsigned int SURVIVAL_BONUS;
public:
	static unsigned int SCORE;
	static bool SURVIVAL_BONUS_ENABLE_FLAG;
	static bool GAMEOVER_FLAG;
	static bool GAMECLEAR_FLAG;
	static void INITIALIZE();
	GameConductor();
	~GameConductor();
	void update();
	void draw_score();
	void draw_my_hp();
};
