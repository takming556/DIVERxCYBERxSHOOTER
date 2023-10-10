#pragma once
#include <memory>
#include "Scenario/Scenario.h"

using std::unique_ptr;

class Stage1 : public Scenario {
private:
	static const wstring STAGE_NAME;
public:
	static Stage1Progress PROGRESS;
	Stage1();
	void update() override;
};