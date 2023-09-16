#pragma once
#include "Scenario.h"

class Stage3 : public Scenario {
private:
	enum Stage3Progress progress;
	int Wave1;
public:
	Stage3();
	void update() override;
};