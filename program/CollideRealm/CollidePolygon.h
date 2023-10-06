#pragma once
#include <memory>
#include <vector>
#include "CollideRealm/CollideRealm.h"
#include "CollideRealm/CollideCircle.h"
#include "Position/InFieldPosition.h"

using std::unique_ptr;
using std::vector;
class CollideCircle;



class CollidePolygon : public CollideRealm {
protected:
public:
	vector<InFieldPosition> angle_positions;
	CollidePolygon(vector<InFieldPosition>& given_angle_positions);
	//bool is_collided_with(unique_ptr<CollideRealm>& given_collide_realm);
	bool is_collided_with(unique_ptr<CollideCircle>& given_collide_circle);
	//bool is_collided_with(unique_ptr<CollidePolygon>& given_collide_circle);
	void draw() override;
	void update(vector<InFieldPosition>& upd_angle_positions);
};