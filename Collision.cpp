#include "DxLib.h"
#include "Collision.h"
#include "enum.h"

Collision::Collision(CharacterID given_character_id):
	character_id(given_character_id),
	last_collided_clock(DxLib::GetNowCount()),
	last_damaged_clock(DxLib::GetNowCount())
{
}


Collision::Collision(CharacterID given_character_id, int given_collided_clock) :
	character_id(given_character_id),
	last_collided_clock(given_collided_clock),
	last_damaged_clock(DxLib::GetNowCount())
{
}


Collision::Collision(CharacterID given_character_id, int given_collided_clock, int given_damaged_clock):
	character_id(given_character_id),
	last_collided_clock(given_collided_clock),
	last_damaged_clock(given_damaged_clock)
{
}