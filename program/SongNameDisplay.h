#pragma once
#include <string>
#include "DxLib.h"

using std::wstring;

class SongNameDisplay {
private:
	double pos_x;
	double arg;
	double scroll_speed;
	int generated_clock;
	double last_updated_clock;
	wstring song_name;
	static const unsigned int INIT_POS_X;
	static const unsigned int POS_Y;
	static const double INIT_ARG;
	static const double INIT_SCROLL_SPEED;
public:
	SongNameDisplay(wstring given_song_name);
	SongNameDisplay() = default;
	void draw();
};