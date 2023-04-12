#pragma once

class Scenario {
protected:
	int kept_clock;
	int elapsed_time;
	Scenario();
	virtual void update() = 0;
};