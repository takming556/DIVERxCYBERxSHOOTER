#pragma once
#include <string>
#include "DxLib.h"

using std::wstring;

class Scenario {
protected:
	int kept_clock;
private:
	static int MUSIC_NAME_LAST_APPENDED_CLOCK;
	static unsigned int MUSIC_NAME_INIT_POS_X;
	static unsigned int MUSIC_NAME_INIT_POS_Y;
	static unsigned int MUSIC_NAME_SCROLL_SPEED;
public:
	Scenario();
	Scenario() = default;
	void INITIALIZE();
	virtual void update() = 0;
	static void DISPLAY_MUSIC_NAME(wstring& given_music_name);
};