#pragma once
#include <memory>
#include "Scenario/Scenario.h"

using std::unique_ptr;

class Stage1 : public Scenario {
private:
	enum Stage1Progress stage1_progress;
public:
	Stage1();
	void update() override;
};