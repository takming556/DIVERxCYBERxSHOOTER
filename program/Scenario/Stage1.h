#pragma once
#include <string>
#include <memory>
#include <tuple>
#include <deque>
#include "Offensive/Laser/Laser.h"
#include "Scenario/Scenario.h"

using std::wstring;
using std::unique_ptr;
using std::tuple;
using std::deque;


class Stage1 : public Scenario {
private:
	double test_arg;
	LaserID carte_id;
	LaserID polar_id;
	LONGLONG test_updated_clock;
	static const wstring STAGE_NUM;
	static const wstring STAGE_NAME_MAIN;
	static const wstring STAGE_NAME_SUB;
	static const wstring SONG_NAME;
	static deque<tuple<wstring, wstring, PortraitID>> BEFORE_BOSS_WORDS;
	static deque<tuple<wstring, wstring, PortraitID>> AFTER_BOSS_WORDS;
public:
	static Stage1Progress PROGRESS;
	Stage1();
	void update() override;
};