#pragma once
#include <string>
#include <array>
#include "Dial.h"

using std::string;
using std::array;

class NicknameInput {
private:
	unsigned int operating_digit;
	array<Dial, 16> dials;
public:
	static bool CONFIRMING_FLAG;
	bool determined_flag;
	NicknameInput();
	static void INITIALIZE();
	void update();
	void respond_to_keyinput();
	void digitslide_left();
	void digitslide_right();
	void draw();
	string get();
};