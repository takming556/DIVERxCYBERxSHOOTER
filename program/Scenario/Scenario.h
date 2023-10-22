#pragma once
#include <string>
#include "DxLib.h"

using std::wstring;

class Scenario {
protected:
	int kept_clock;
	bool boss_advented_flag;
	int boss_advented_clock;
	bool boss_crushed_flag;

private:
	static int MUSIC_NAME_LAST_APPENDED_CLOCK;
	static unsigned int MUSIC_NAME_INIT_POS_X;
	static unsigned int MUSIC_NAME_INIT_POS_Y;
	static unsigned int MUSIC_NAME_SCROLL_SPEED;
public:
	Scenario();
	virtual void update() = 0;
};