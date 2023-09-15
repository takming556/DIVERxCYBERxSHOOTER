#pragma once
#include <string>
#include "Character/MyCharacter/MyCharacter.h"

using std::string;

class IchigoChan : public MyCharacter {
private:
	static const string CHARACTER_NAME;
	static const double DRAW_EXTRATE;
public:
	IchigoChan();
	void draw() override;
};