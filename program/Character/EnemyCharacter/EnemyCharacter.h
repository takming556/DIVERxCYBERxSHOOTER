#pragma once
#include "Character/Character.h"


class EnemyCharacter : virtual public Character {
protected:
	EnemyCharacter();
public:
	virtual ~EnemyCharacter() {}
	virtual void update() = 0;
	virtual void draw() = 0;
	void damaged() override;
	bool is_collided_with_my_offensives();
};