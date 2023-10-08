#pragma once
#include <string>
#include "Character/EnemyCharacter/EnemyCharacter.h"

using std::wstring;

class BossCharacter : virtual public EnemyCharacter {
protected:
	wstring name;
	const unsigned int initial_hp;
	const unsigned int crush_bonus;
	BossCharacter(wstring character_name, unsigned int given_initial_hp, unsigned int given_crush_bonus);
public:
	virtual void funeral() override;
	void HPDonut();
};