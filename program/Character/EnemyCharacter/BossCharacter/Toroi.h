#pragma once
#include <string>
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "enum.h"

using std::string;


class Toroi : public BossCharacter {
private:
	ToroiStatus status;
	ToroiSP1Mode sp1_mode;

	static const string NAME;
	static const int INITIAL_POS_X;
	static const int INITIAL_POS_Y;
	static const unsigned int INITIAL_COLLIDANT_SIZE;
	static const double DRAW_EXTRATE;
	static const unsigned int INITIAL_HP;

};