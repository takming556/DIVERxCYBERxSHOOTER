#pragma once
#include "enum.h"

template <typename T>
class Collision {
public:
	Collision(T given_id);
	Collision(T given_id, int given_collided_clock);
	Collision(T given_id, int given_collided_clock, int given_damaged_clock);
	T id;
	int last_collided_clock;
	int last_damaged_clock;
};