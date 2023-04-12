#pragma once
#include "Scenario/Scenario.h"
#include "Scenario/Stage1.h"

class Stage1 : public Scenario {
private:
	enum Stage1Progress stage1_progress;
public:
	Stage1();
	void update() override;
};