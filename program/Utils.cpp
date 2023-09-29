#include <cmath>
#include <numbers>
#include "Utils.h"

using std::atan2;
using std::numbers::pi;


Utils::Utils() = default;

double Utils::fixed_atan2(double Y, double X) {
	double theta = atan2(Y, X);
	if (X >= 0 && Y >= 0)
		return theta;
	else if (X <= 0 && Y >= 0)
		return theta + pi;
	else if (X <= 0 && Y <= 0)
		return theta + pi;
	else if (X >= 0 && Y <= 0)
		return theta + 2 * pi;
}