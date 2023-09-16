#pragma once
#include <vector>
#include "Character/Character.h"


using std::vector;


class EnemyCharacter : virtual public Character {
protected:
	EnemyCharacter();
	vector<unsigned int> last_collided_my_bullet_ids;
	bool is_last_collided_with(unsigned int given_my_bullet_id);
public:
	static unsigned int DPS;		// Damage Per Second
	virtual ~EnemyCharacter() {}
	virtual void update() = 0;
	virtual void draw() = 0;
	void damaged() override;
	bool is_collided_with_my_offensives();
	void deal_collision();
};