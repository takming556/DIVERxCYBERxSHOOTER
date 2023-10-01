#pragma once
#include <memory>
#include "CollideRealm/CollideRealm.h"
#include "CollideRealm/CollidePolygon.h"
#include "Position/InFieldPosition.h"

class InFieldPosition;
class CollidePolygon;
using std::unique_ptr;



class CollideCircle : public CollideRealm {
public:
	unique_ptr<InFieldPosition> center_pos;
	unsigned int radius;
	CollideCircle(double init_center_pos_x, double init_center_pos_y, unsigned int init_radius);
	//bool is_collided_with(unique_ptr<CollideRealm>& given_collide_realm);
	bool is_collided_with(unique_ptr<CollideCircle>& given_collide_circle);
	bool is_collided_with(unique_ptr<CollidePolygon>& given_collide_polygon);
	void draw() override;
	void update(unique_ptr<InFieldPosition>& now_pos);
};