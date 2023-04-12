#pragma once
#include <string>
#include "Character/EnemyCharacter/EnemyCharacter.h"

using std::string;

class BossCharacter : virtual public EnemyCharacter {
protected:
	string name;
	BossCharacter(string character_name);
};