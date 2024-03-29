﻿#pragma once
#include <memory>
#include "Position/InFieldPosition.h"

using std::unique_ptr;


class CollideRealm {
protected:
	static const unsigned int DRAW_COLOR;
	static const float DRAW_THICKNESS;
public:
	CollideRealm();
	virtual ~CollideRealm();
	//virtual bool is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) = 0;
	virtual void draw() = 0;
};