#pragma once
#include <string>
#include <tuple>
#include "enum.h"
#include "Position/InFieldPosition.h"

using std::wstring;
using std::tuple;

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
	static InFieldPosition POS;
	static InFieldPosition PORTRAIT_POS;
	static InFieldPosition TEXT_POS;
	static InFieldPosition SPEAKER_NAME_POS;
	static InFieldPosition AWAITING_INDICATOR_POS;
	static const double TEXT_ROLL_SPEED;
	static const unsigned int AWAITING_INDICATOR_BLINK_WAIT;
public:
	NarrativePop(tuple<wstring, wstring, PortraitID> given_narration);
	NarrativePopState state;
	void activate();
	void update();
	void draw();
};