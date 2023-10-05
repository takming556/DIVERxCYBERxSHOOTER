#pragma once
#include "Scenario.h"

class Stage3 : public Scenario {
private:
	int Wave1;
	int Wave2;
public:
	static enum Stage3Progress PROGRESS;
	Stage3();
	void update() override;
};