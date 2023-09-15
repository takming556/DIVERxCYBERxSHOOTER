#pragma once
#include <memory>
#include "CollideRealm/CollideRealm.h"
#include "Position/InFieldPosition.h"

class InFieldPosition;


using std::unique_ptr;

class CollideCircle : public CollideRealm {
protected:
	unique_ptr<InFieldPosition> center_pos;
	unsigned int radius;
public:
	CollideCircle(double init_center_pos_x, double init_center_pos_y, unsigned int init_radius);
	bool is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) override;
	void draw() override;
	void update(unique_ptr<InFieldPosition>& now_pos) override;
};