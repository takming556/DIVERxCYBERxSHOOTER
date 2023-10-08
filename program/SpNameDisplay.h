#pragma once
#include <string>
#include "DxLib.h"

using std::wstring;

class SpNameDisplay {
private:
	int generated_clock;
	wstring sp_name;
	static unsigned int INIT_POS_X;
	static unsigned int INIT_POS_Y;
	static unsigned int SCROLL_SPEED;
public:
	SpNameDisplay(wstring given_sp_name);
	SpNameDisplay() = default;
	void update();
};