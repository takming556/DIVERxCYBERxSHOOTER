#pragma once
#include <string>
#include "DxLib.h"

using std::wstring;

class StageNameDisplay {
private:
	int generated_clock;
	wstring stage_num;
	wstring stage_name_main;
	wstring stage_name_sub;
	static unsigned int STAGE_NUM_INIT_POS_X;
	static unsigned int STAGE_NUM_INIT_POS_Y;
	static unsigned int MAIN_INIT_POS_Y;
	static unsigned int SUB_INIT_POS_Y;
	// static unsigned int SCROLL_SPEED;
	static unsigned int DURATION;
public:
	StageNameDisplay(
		wstring given_stage_num,
		wstring given_stage_name_main,
		wstring given_stage_name_sub
	);
	StageNameDisplay() = default;
	void draw();
};