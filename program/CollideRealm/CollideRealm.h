#pragma once
#include <memory>
#include "Position/InFieldPosition.h"

using std::unique_ptr;


class CollideRealm {
protected:
	static const unsigned int DRAW_COLOR;
public:
	CollideRealm();
	virtual ~CollideRealm();
	virtual bool is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) = 0;
	virtual void draw() = 0;
	virtual void update(unique_ptr<InFieldPosition>& now_pos) = 0;
};