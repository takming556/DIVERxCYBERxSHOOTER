#include "DxLib.h"
#include "class.h"

using std::make_unique;
using std::string;



NicknameInput::NicknameInput() :
	operating_digit(0)
{
}


void NicknameInput::update() {
	respond_to_keyinput();
	dials.at(operating_digit).respond_to_keyinput();
}


void NicknameInput::respond_to_keyinput() {

	if (KeyPushFlags::LEFT == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_LEFT] == 1) {
		digitslide_left();
		KeyPushFlags::LEFT = true;
	}
	if (KeyPushFlags::LEFT == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_LEFT] == 0) {
		KeyPushFlags::LEFT = false;
	}

	if (KeyPushFlags::RIGHT == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_RIGHT] == 1) {
		digitslide_right();
		KeyPushFlags::RIGHT = true;
	}
	if (KeyPushFlags::RIGHT == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_RIGHT] == 0) {
		KeyPushFlags::RIGHT = false;
	}
}


void NicknameInput::digitslide_left() {
	if (operating_digit >= 1) --operating_digit;
}


void NicknameInput::digitslide_right() {
	if (operating_digit <= 14) ++operating_digit;
}


void NicknameInput::draw() {
	int x = 0;
	for (int i = 0; i <= 15; i++) {
		dials.at(i).draw_character((x += 64) - 48, Screen::SCREEN_RESOLUTION_Y / 2);
		if (i == operating_digit) {
			dials.at(i).draw_cursor(x - 24, Screen::SCREEN_RESOLUTION_Y / 2);
		}
	}

}


string NicknameInput::get() {
	string s("");
	for (int i = 0; i <= 15; i++) {
		s += dials.at(i).get();
	}
	return s;
}