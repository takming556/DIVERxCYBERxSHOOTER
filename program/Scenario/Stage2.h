#pragma once
#include "Scenario.h"

class Stage2 : public Scenario {
private:
	enum Stage2Progress progress;
	int wave6count;
public:
	Stage2();
	void update() override;
};