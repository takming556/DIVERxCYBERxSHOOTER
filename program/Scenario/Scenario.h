#pragma once

class Scenario {
protected:
	int kept_clock;
	Scenario();
public:
	virtual void update() = 0;
};