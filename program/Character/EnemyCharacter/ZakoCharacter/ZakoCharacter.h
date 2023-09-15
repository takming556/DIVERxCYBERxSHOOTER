#pragma once
#include "Character/EnemyCharacter/EnemyCharacter.h"


class ZakoCharacter : virtual public EnemyCharacter {
protected:
	ZakoCharacter() {}
public:
	static const unsigned int CRUSH_BONUS;
};
