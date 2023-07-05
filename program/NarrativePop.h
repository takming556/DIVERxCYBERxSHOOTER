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
	static const Position DRAW_POS;
public:
	NarrativePop(u8string text, u8string speaker_name, PortraitID portrait_id);
	void draw();
	void update();
};