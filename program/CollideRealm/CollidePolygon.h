#pragma once
#include <memory>
#include <vector>
#include "CollideRealm/CollideRealm.h"
#include "Position/InFieldPosition.h"

using std::unique_ptr;
using std::vector;


class CollidePolygon : public CollideRealm {
protected:
	vector<InFieldPosition> angle_positions;
public:
	CollidePolygon(vector<InFieldPosition>& given_angle_positions);
	bool is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) override;
	void draw() override;
	void update(vector<InFieldPosition>& upd_angle_positions);
};