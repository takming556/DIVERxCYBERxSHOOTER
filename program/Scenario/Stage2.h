#pragma once
#include <string>
#include "Scenario.h"

using std::wstring;

class Stage2 : public Scenario {
private:
	int wave6count;
	int wave7count;
	int wave8_generated_count;
	int wave8_go_count;

	int wave4_elapsed_time;
	int wave5_elapsed_time;
	int wave6_elapsed_time[5+1+1];
	int wave7_elapsed_time[5+1+1];
	int wave8_generated_elapsed_time[8+1+1];
	int wave8_lower_elapsed_time[4+1+1];
	int boss_elapsed_time;

	static const wstring SONG_NAME;
	static const wstring STAGE_NAME;

	static const unsigned int WAVE4_BASIC_ELAPSED_TIME;
	static const unsigned int WAVE5_BASIC_ELAPSED_TIME;
	static const unsigned int WAVE6_BASIC_ELAPSED_TIME;
	static const unsigned int WAVE7_BASIC_ELAPSED_TIME;
	static const unsigned int WAVE8_GENERATED_BASIC_ELAPSED_TIME;
	static const unsigned int WAVE8_LOWER_BASIC_ELAPSED_TIME;
	static const unsigned int BOSS_BASIC_ELAPSED_TIME;
	static const unsigned int WAVE3_GENERATED_TO_ENDED_TIME;
	static const unsigned int WAVE4_GENERATED_TO_ENDED_TIME;
	static const unsigned int WAVE5_GENERATED_TO_ENDED_TIME;
	static const unsigned int WAVE6_GENERATED_TO_ENDED_TIME;
	static const unsigned int WAVE7_GENERATED_TO_ENDED_TIME;
	static const unsigned int WAVE8_GENERATED_TO_LOWER_TIME;
	static const unsigned int WAVE8_LOWER_TO_ENDED_TIME;

public:
	static enum Stage2Progress PROGRESS;
	Stage2();
	void update() override;
};