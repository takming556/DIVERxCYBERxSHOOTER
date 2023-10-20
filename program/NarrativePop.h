#pragma once
#include <string>
#include "enum.h"
#include "Position/InFieldPosition.h"

using std::wstring;

class NarrativePop {
private:
	const wstring text;
	wstring displaying_text;
	wstring speaker_name;
	PortraitID portrait_id;
	unsigned int display_letter_count;
	int activated_clock;
	bool awaiting_indicator_lighting_flag;
	int awaiting_indicator_last_blinked_clock;
	static const InFieldPosition POS;
	static const double TEXT_ROLL_SPEED;
	static const unsigned int AWAITING_INDICATOR_BLINK_WAIT;
public:
	NarrativePop(wstring text, wstring speaker_name, PortraitID portrait_id);
	NarrativePopState state;
	void activate();
	void update();
	void draw();
};