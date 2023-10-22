#pragma once
#include <string>
#include <deque>
#include <tuple>
#include "enum.h"
#include "Scenario.h"

using std::wstring;
using std::deque;
using std::tuple;

class Stage3 : public Scenario {
private:
	int Wave1;
	int Wave2;
	int Wave3;
	int Wave4;
	int Wave5;
	int Wave6;
	int Wave7;
	bool before_decision_pushed_flag;
	Y_N yes_no_indicator_status;
	bool yes_no_decided_flag;
	
	static const wstring STAGE_NUM;
	static const wstring STAGE_NAME_MAIN;
	static const wstring STAGE_NAME_SUB;
	static const wstring SONG_NAME;

	static const deque<tuple<wstring, wstring, PortraitID>> BEFORE_BOSS_WORDS;
	static const deque<tuple<wstring, wstring, PortraitID>> BEFORE_BOSS_ADDITIONAL_WORDS;
	static const deque<tuple<wstring, wstring, PortraitID>> BEFORE_BOSS_REST_WORDS;
	static const deque<tuple<wstring, wstring, PortraitID>> AFTER_BOSS_WORDS;

public:
	static enum Stage3Progress PROGRESS;
	Stage3();
	void update() override;
};