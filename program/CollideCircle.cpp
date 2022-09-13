#include <memory>
#include "class.h"

using std::make_unique;

CollideCircle::CollideCircle(double init_center_pos_x, double init_center_pos_y, int init_radius) :
	center_pos(make_unique<InFieldPosition>(init_center_pos_x, init_center_pos_y)),
	radius(init_radius)
{
}