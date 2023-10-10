#pragma once
#include <memory>
#include "Offensive/Laser/Laser.h"
#include "Scenario/Scenario.h"

using std::unique_ptr;


class Stage1 : public Scenario {
private:
	double test_arg;
	LaserID carte_id;
	LaserID polar_id;
	LONGLONG test_updated_clock;
public:
	static Stage1Progress PROGRESS;
	Stage1();
	void update() override;
};