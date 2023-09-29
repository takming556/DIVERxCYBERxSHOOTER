#pragma once
#include <vector>
#include <memory>
#include "Offensive/Offensive.h"

class Laser : public Offensive {
protected:
	bool active_flag;
	Laser(bool init_active_flag);
public:
	bool is_active();
	void activate();
	void inactivate();
};