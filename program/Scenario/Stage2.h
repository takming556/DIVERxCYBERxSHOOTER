#pragma once
#include "Scenario.h"

class Stage2 : public Scenario {
private:
	enum Stage2Progress progress;
public:
	Stage2();
	void update() override;
};