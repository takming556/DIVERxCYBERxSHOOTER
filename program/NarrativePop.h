#pragma once
#include <string>
#include "enum.h"
#include "Position/Position.h"

using std::u8string;

class NarrativePop {
private:
	u8string text;
	u8string speaker_name;
	PortraitID portrait_id;
	NarrativePopState state;
	static const Position DRAW_POS;
public:
	NarrativePop(u8string text, u8string speaker_name, PortraitID portrait_id);
	void activate();
	void draw();
	void update();
};