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
	Offensive(vector<unique_ptr<CollideRealm>> given_collidants);
public:
	vector<unique_ptr<CollideRealm>> collidants;
	vector<shared_ptr<Collision>> collisions;
	bool is_collided_with_my_character();
	bool is_collided_with_enemy_characters();
	bool is_broken();
	void damaged();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void draw_durability() = 0;
	virtual ~Offensive();
};