#pragma once
#include <string>

using std::string;

class Dial {
private:
	unsigned int position;
	static const string ENABLED_CHARACTERS;
	static const unsigned int INITIAL_POSITION;
public:
	Dial();
	void respond_to_keyinput();
	void uproll();
	void downroll();
	void draw_character(int draw_x, int draw_y);
	void draw_cursor(int draw_x, int draw_y);
	string get();
};