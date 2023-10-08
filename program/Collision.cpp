#include "DxLib.h"
#include "Collision.h"
#include "enum.h"

using BulletID = unsigned int;
using LaserID = unsigned int;

template class Collision<CharacterID>;
template class Collision<BulletID>;
template class Collision<LaserID>;

template <typename T>
Collision<T>::Collision(T given_id):
	id(given_id),
	last_collided_clock(DxLib::GetNowCount()),
	last_damaged_clock(DxLib::GetNowCount())
{
}

template <typename T>
Collision<T>::Collision(T given_id, int given_collided_clock) :
	id(given_id),
	last_collided_clock(given_collided_clock),
	last_damaged_clock(DxLib::GetNowCount())
{
}

template <typename T>
Collision<T>::Collision(T given_id, int given_collided_clock, int given_damaged_clock):
	id(given_id),
	last_collided_clock(given_collided_clock),
	last_damaged_clock(given_damaged_clock)
{
}