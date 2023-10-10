﻿#pragma once
#include <string>

using std::wstring;

class SongNameDisplay {
private:
	int generated_clock;
	wstring song_name;
	static unsigned int POS_X;
	static unsigned int POS_Y;
	static unsigned int DURATION;
public:
	SongNameDisplay(wstring given_song_name);
	SongNameDisplay() = default;
	void update();
};