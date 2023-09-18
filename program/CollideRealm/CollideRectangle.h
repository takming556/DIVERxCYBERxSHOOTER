#pragma once
#include <memory>
#include "CollideRealm/CollideRealm.h"
#include "Position/InFieldPosition.h"

using std::unique_ptr;

class CollideRectangle : public CollideRealm {
protected:
	unique_ptr<InFieldPosition> pos1;
	unique_ptr<InFieldPosition> pos2;
public:
	CollideRectangle(
		double center_pos_x,
		double center_pos_y,
		double height,
		double width,
		double tilt
	);
};