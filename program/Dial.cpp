#include <memory>
#include "DxLib.h"
#include "AppSession.h"
#include "Dial.h"
#include "KeyPushFlags.h"
#include "NicknameInput.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "FontHandles.h"
#include "Colors.h"

using std::make_unique;
using std::wstring;


const unsigned int Dial::INITIAL_POSITION = 0;
const wstring Dial::ENABLED_CHARACTERS(L" ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-!?@");


Dial::Dial() :
	position(INITIAL_POSITION)
{
}


void Dial::respond_to_keyinput() {

	if (NicknameInput::CONFIRMING_FLAG == false) {
		if (KeyPushFlags::UP == false && AppSession::KEY_BUFFER[KEY_INPUT_UP] == 1) {
			uproll();
			KeyPushFlags::UP = true;
		}
		if (KeyPushFlags::UP == true && AppSession::KEY_BUFFER[KEY_INPUT_UP] == 0) {
			KeyPushFlags::UP = false;
		}

		if (KeyPushFlags::DOWN == false && AppSession::KEY_BUFFER[KEY_INPUT_DOWN] == 1) {
			downroll();
			KeyPushFlags::DOWN = true;
		}
		if (KeyPushFlags::DOWN == true && AppSession::KEY_BUFFER[KEY_INPUT_DOWN] == 0) {
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


wstring Dial::get() {
	return ENABLED_CHARACTERS.substr(position, 1);
}


void Dial::draw_character(int draw_x, int draw_y) {
	DxLib::DrawFormatStringToHandle(draw_x, draw_y, Colors::RED, FontHandles::CONSOLAS_64, L"%c", ENABLED_CHARACTERS.at(position));
}


void Dial::draw_cursor(int draw_x, int draw_y) {
	DxLib::DrawRotaGraph(draw_x, draw_y + 20, 1.0, 0, ImageHandles::DIGIT_CURSOR, TRUE);
}