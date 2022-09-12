#include <memory>
#include "class.h"

using std::make_unique;


Bullet::Bullet(double init_x, double init_y) :
	center_pos(make_unique<InFieldPosition>(init_x, init_y))
{
}