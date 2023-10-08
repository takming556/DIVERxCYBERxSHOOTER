﻿#pragma once
#include <vector>
#include <memory>
#include "Offensive/Offensive.h"
#include "CollideRealm/CollidePolygon.h"


using std::unique_ptr;
using LaserID = unsigned int;


class Laser : public Offensive {
protected:
	static LaserID NEXT_ID;
	bool active_flag;
	bool terminated_flag;
	Laser(unsigned int given_dps, bool init_active_flag);
	Laser();
public:
	unique_ptr<CollidePolygon> collidant;
	unsigned int dps;
	static void INITIALIZE();
	bool is_active();
	void activate();
	void inactivate();
	void terminate();
	//virtual void update() = 0;
	static LaserID GENERATE_ID();
};