#pragma once
#include "Scenario.h"

class Stage3 : public Scenario {
private:
	enum Stage3Progress progress;
	int Wave1;
	int Wave2;
public:
	Stage3();
	void update() override;
};