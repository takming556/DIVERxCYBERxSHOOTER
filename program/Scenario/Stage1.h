#pragma once
#include <memory>
#include "Scenario/Scenario.h"

using std::unique_ptr;

class Stage1 : public Scenario {
public:
	static Stage1Progress PROGRESS;
	Stage1();
	void update() override;
};