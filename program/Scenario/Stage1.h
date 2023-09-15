#pragma once
#include "Scenario/Scenario.h"

class Stage1 : public Scenario {
private:
	enum Stage1Progress stage1_progress;
public:
	Stage1();
	void update() override;
};