#pragma once
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"

class ZkChhrStg2BsNm4 : public ZakoCharacter {
	double speed;
	double arg;
	int last_turned_clock;
	static const unsigned int INITIAL_HP;
	static const double DRAW_EXTRATE;
public:
	ZkChhrStg2BsNm4();
	void update() override;
	void draw() override;
};