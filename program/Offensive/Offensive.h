#pragma once
#include <memory>
#include <vector>
#include "DxLib.h"
#include "CollideRealm/CollideRealm.h"
#include "Position/InFieldPosition.h"
#include "Collision.h"

using std::unique_ptr;
using std::shared_ptr;
using std::vector;


class Offensive {
protected:
	LONGLONG last_updated_clock;
	Offensive(unique_ptr<CollideRealm> given_collidant);
	Offensive();
public:
	unique_ptr<CollideRealm> collidant;
	vector<shared_ptr<Collision>> collisions;
	virtual bool is_collided_with_my_character();
	virtual bool is_collided_with_enemy_characters();
	virtual bool is_broken() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual ~Offensive();
};