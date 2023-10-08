#pragma once
#include <string>
#include "Character/EnemyCharacter/EnemyCharacter.h"

using std::string;

class BossCharacter : virtual public EnemyCharacter {
protected:
	string name;
	const unsigned int crush_bonus;
	BossCharacter(string character_name, unsigned int given_crush_bonus);
public:
	virtual void funeral() override;
};