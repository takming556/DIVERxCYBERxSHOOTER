#pragma once
#include <memory>
#include "DxLib.h"

#include "CollideRealm/CollideRealm.h"
#include "Position/InFieldPosition.h"

using std::unique_ptr;

//class CollideRealm;
//class InFieldPosition;

class Character {
protected:
	LONGLONG last_updated_clock;
	Character(int init_pos_x, int init_pos_y, unique_ptr<CollideRealm> given_collidant);
public:
	unique_ptr<InFieldPosition> position;
	unique_ptr<CollideRealm> collidant;
	~Character();
};