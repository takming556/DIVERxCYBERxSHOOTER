#pragma once
#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "CollideRealm/CollideRealm.h"
#include "Position/InFieldPosition.h"

using std::unique_ptr;


class Character {
protected:
	LONGLONG last_updated_clock;
	Character(
		enum CharacterID given_id,
		double init_pos_x,
		double init_pos_y,
		int init_hp,
		unique_ptr<CollideRealm> given_collidant
	);
public:
	int hp;
	enum CharacterID id;
	unique_ptr<InFieldPosition> position;
	unique_ptr<CollideRealm> collidant;
	void draw_hp();
	bool is_dead();
	virtual void damaged() = 0;
	virtual void draw() = 0;
	~Character();
};