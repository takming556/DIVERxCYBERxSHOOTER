#pragma once
#include <string>
#include "enum.h"
#include "Position/Position.h"

using std::wstring;

class NarrativePop {
private:
	wstring text;
	wstring speaker_name;
	PortraitID portrait_id;
	static const Position DRAW_POS;
public:
	NarrativePop(wstring text, wstring speaker_name, PortraitID portrait_id);
	NarrativePopState state;
	void activate();
	void draw();
	void update();
};