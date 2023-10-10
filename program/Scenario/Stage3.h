#pragma once
#include <string>
#include "Scenario.h"

using std::wstring;

class Stage3 : public Scenario {
private:
	int Wave1;
	int Wave2;
	static const wstring SONG_NAME;
public:
	static enum Stage3Progress PROGRESS;
	Stage3();
	void update() override;
};