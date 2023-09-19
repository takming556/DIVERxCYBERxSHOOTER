#pragma once
#include "Scenario.h"

class Stage2 : public Scenario {
private:
	enum Stage2Progress progress;
	int wave6count;
	int wave7count;
	int wave8count;

	static const double WAVE8_LINE_UP_X_L1;
	static const double WAVE8_LINE_UP_X_L2;
	static const double WAVE8_LINE_UP_X_L3;
	static const double WAVE8_LINE_UP_X_L4;
	static const double WAVE8_LINE_UP_X_L5;
	static const double WAVE8_LINE_UP_X_L6;
	static const double WAVE8_LINE_UP_X_L7;
	static const double WAVE8_LINE_UP_X_L8;
	static const double WAVE8_LINE_UP_X_R1;
	static const double WAVE8_LINE_UP_X_R2;
	static const double WAVE8_LINE_UP_X_R3;
	static const double WAVE8_LINE_UP_X_R4;
	static const double WAVE8_LINE_UP_X_R5;
	static const double WAVE8_LINE_UP_X_R6;
	static const double WAVE8_LINE_UP_X_R7;
	static const double WAVE8_LINE_UP_X_R8;

public:
	Stage2();
	void update() override;
};