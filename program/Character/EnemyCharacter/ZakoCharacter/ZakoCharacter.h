#pragma once
#include "Character/EnemyCharacter/EnemyCharacter.h"


class ZakoCharacter : virtual public EnemyCharacter {
protected:
	ZakoCharacter() {}
public:
	virtual ~ZakoCharacter() = default;
	static const unsigned int CRUSH_BONUS;
	virtual void funeral() final override;
};
