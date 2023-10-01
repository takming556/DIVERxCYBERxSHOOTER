#pragma once
#include <vector>
#include <memory>
#include "Offensive/Offensive.h"
#include "CollideRealm/CollidePolygon.h"


using std::unique_ptr;


class Laser : public Offensive {
protected:
	bool active_flag;
	bool terminated_flag;
	Laser(bool init_active_flag);
	Laser();
public:
	unique_ptr<CollidePolygon> collidant;
	bool is_active();
	void activate();
	void inactivate();
	void terminate();
	virtual void update() = 0;
};