#include "DxLib.h"
#include "class.h"

using std::make_unique;
using std::string;


const unsigned int Dial::INITIAL_POSITION = 1;
const string Dial::ENABLED_CHARACTERS(" ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-!?@");


Dial::Dial() :
	position(INITIAL_POSITION)
{
}


void Dial::respond_to_keyinput() {

	if (NicknameInput::CONFIRMING_FLAG == false) {
		if (KeyPushFlags::UP == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_UP] == 1) {
			uproll();
			KeyPushFlags::UP = true;
		}
		if (KeyPushFlags::UP == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_UP] == 0) {
			KeyPushFlags::UP = false;
		}

		if (KeyPushFlags::DOWN == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_DOWN] == 1) {
			downroll();
			KeyPushFlags::DOWN = true;
		}
		if (KeyPushFlags::DOWN == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_DOWN] == 0) {
			KeyPushFlags::DOWN = false;
		}
	}

}


void Dial::uproll() {
	if (position < ENABLED_CHARACTERS.length() - 1) {
		++position;
	}
	else {
		position = 0;
	}
	DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_BACK);
}


void Dial::downroll() {
	if (position >= 1) {
		--position;
	}
	else {
		position = ENABLED_CHARACTERS.length() - 1;
	}
	DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_BACK);
}


string Dial::get() {
	return ENABLED_CHARACTERS.substr(position, 1);
}


void Dial::draw_character(int draw_x, int draw_y) {
	DxLib::DrawFormatStringToHandle(draw_x, draw_y, Colors::RED, FontHandles::CONSOLAS_64, "%c", ENABLED_CHARACTERS.at(position));
}


void Dial::draw_cursor(int draw_x, int draw_y) {
	DxLib::DrawRotaGraph(draw_x, draw_y + 20, 1.0, 0, ImageHandles::DIGIT_CURSOR, TRUE);
}