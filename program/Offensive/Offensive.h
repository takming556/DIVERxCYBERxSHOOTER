#pragma once
#include <memory>
#include "DxLib.h"

#include "CollideRealm/CollideRealm.h"
#include "Position/InFieldPosition.h"

using std::unique_ptr;

//class CollideRealm;
//class InFieldPosition;

class Offensive {
protected:
	unsigned int durability;
	LONGLONG last_updated_clock;
	Offensive(double init_pos_x, double init_pos_y, unique_ptr<CollideRealm> given_collidant, unsigned int init_durability);
	Offensive() {}
public:
	unique_ptr<CollideRealm> collidant;
	unique_ptr<InFieldPosition> position;
	bool is_collided_with_my_character();
	bool is_collided_with_enemy_characters();
	bool is_broken();
	void damaged();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void draw_durability() = 0;
	virtual ~Offensive();
};