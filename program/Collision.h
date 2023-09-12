#pragma once
#include <memory>
#include "Offensive/Offensive.h"
#include "Character/Character.h"

using std::shared_ptr;


class Collision {
public:
	shared_ptr<Offensive> offensive;
	shared_ptr<Character> character;
};