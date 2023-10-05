#pragma once
#include "Scenario/Scenario.h"

class Stage1 : public Scenario {
public:
	static Stage1Progress PROGRESS;
	Stage1();
	void update() override;
};