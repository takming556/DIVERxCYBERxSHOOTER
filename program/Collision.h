#pragma once
#include "enum.h"

class Collision {
public:
	Collision(CharacterID given_character_id);
	Collision(CharacterID given_character_id, int given_collided_clock);
	Collision(CharacterID given_character_id, int given_collided_clock, int given_damaged_clock);
	CharacterID character_id;
	int last_collided_clock;
	int last_damaged_clock;
};