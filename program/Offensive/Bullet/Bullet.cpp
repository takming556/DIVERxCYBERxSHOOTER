#include <memory>
#include "DxLib.h"
#include "Offensive/Bullet/Bullet.h"
#include "Position/Position.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"

using std::make_unique;


Bullet::Bullet(double init_pos_x, double init_pos_y, double init_arg, double init_speed) :
	position(make_unique<InFieldPosition>(init_pos_x, init_pos_y)),
	arg(init_arg),
	speed(init_speed),
	last_frame_updated_clock(0),
	now_frame(0)
{
}