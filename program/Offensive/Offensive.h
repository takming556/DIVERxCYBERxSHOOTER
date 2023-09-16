#pragma once
#include <memory>
#include <vector>
#include "DxLib.h"
#include "CollideRealm/CollideRealm.h"
#include "Position/InFieldPosition.h"

using std::unique_ptr;
using std::shared_ptr;
using std::vector;


class Offensive {
protected:
	static unsigned int NEXT_ID;
	LONGLONG last_updated_clock;
	Offensive(unique_ptr<CollideRealm> given_collidant);
	Offensive();
public:
	static void INITIALIZE();
	unique_ptr<CollideRealm> collidant;
	virtual bool is_collided_with_my_character();
	virtual bool is_collided_with_enemy_characters();
	virtual bool is_broken() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual ~Offensive();
	static unsigned int GENERATE_ID();
};