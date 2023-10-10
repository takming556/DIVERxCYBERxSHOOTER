#pragma once
#include <string>
#include "DxLib.h"

using std::wstring;

class SongNameDisplay {
private:
	int generated_clock;
	wstring song_name;
	static unsigned int POS_X;
	static unsigned int POS_Y;
	static unsigned int SCROLL_SPEED;
	static unsigned int DURATION;
public:
	SongNameDisplay(wstring given_song_name);
	SongNameDisplay() = default;
	void draw();
};