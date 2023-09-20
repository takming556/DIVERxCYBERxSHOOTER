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
};