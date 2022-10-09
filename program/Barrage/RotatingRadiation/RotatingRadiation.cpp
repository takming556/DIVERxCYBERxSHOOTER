#include <memory>
#include "DxLib.h"
#include "class.h"

using std::unique_ptr;
using std::make_unique;


RotatingRadiation::RotatingRadiation(double init_pos_x, double init_pos_y, double given_rotate_speed, unsigned int given_emit_nozzles) :
	x(init_pos_x),
	y(init_pos_y),
	rotate_speed(given_rotate_speed),
	emit_nozzles(given_emit_nozzles)
{
}