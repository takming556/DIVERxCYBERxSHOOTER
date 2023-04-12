#pragma once
#include "Character/Character.h"


class EnemyCharacter : virtual public Character {
protected:
	unsigned int hp;
	EnemyCharacter(unsigned int init_hp);
public:
	virtual ~EnemyCharacter() {}
	virtual void update() = 0;
	virtual void draw() = 0;
	void damaged();
	void draw_HP();
	bool is_collided_with_my_offensives();
	bool is_dead();
};