#pragma once
#include <string>
#include "DxLib.h"

using std::wstring;

class StageNameDisplay {
private:
	int generated_clock;
	wstring stage_name;
	static unsigned int INIT_POS_X;
	static unsigned int INIT_POS_Y;
	static unsigned int SCROLL_SPEED;
	static unsigned int DURATION;
public:
	StageNameDisplay(wstring given_Stage_name);
	StageNameDisplay() = default;
	void draw();
};