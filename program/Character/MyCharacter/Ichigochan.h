#pragma once
#include <string>
#include "Character/MyCharacter/MyCharacter.h"

using std::wstring;

class IchigoChan : public MyCharacter {
private:
	static const wstring CHARACTER_NAME;
	static const double DRAW_EXTRATE;
public:
	IchigoChan();
	void draw() override;
};