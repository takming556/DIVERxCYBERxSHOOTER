#include <memory>
#include "DxLib.h"
#include "AppSession.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "FontHandles.h"
#include "Screen/Screen.h"
#include "NicknameInput.h"
#include "KeyPushFlags.h"
#include "Colors.h"

using std::make_unique;
using std::string;


bool NicknameInput::CONFIRMING_FLAG = false;


NicknameInput::NicknameInput() :
	operating_digit(0),
	determined_flag(false)
{
	INITIALIZE();
}


void NicknameInput::INITIALIZE() {
	CONFIRMING_FLAG = false;
}


void NicknameInput::update() {
	respond_to_keyinput();
	dials.at(operating_digit).respond_to_keyinput();
}


void NicknameInput::respond_to_keyinput() {

	if (CONFIRMING_FLAG == false) {

		if (KeyPushFlags::LEFT == false && AppSession::KEY_BUFFER[KEY_INPUT_LEFT] == 1) {
			digitslide_left();
			KeyPushFlags::LEFT = true;
		}
		if (KeyPushFlags::LEFT == true && AppSession::KEY_BUFFER[KEY_INPUT_LEFT] == 0) {
			KeyPushFlags::LEFT = false;
		}

		if (KeyPushFlags::RIGHT == false && AppSession::KEY_BUFFER[KEY_INPUT_RIGHT] == 1) {
			digitslide_right();
			KeyPushFlags::RIGHT = true;
		}
		if (KeyPushFlags::RIGHT == true && AppSession::KEY_BUFFER[KEY_INPUT_RIGHT] == 0) {
			KeyPushFlags::RIGHT = false;
		}

		if (KeyPushFlags::Z == false && AppSession::KEY_BUFFER[KEY_INPUT_Z] == 1) {
			CONFIRMING_FLAG = true;
			DxLib::PlaySoundMem(SoundHandles::FORWARD, DX_PLAYTYPE_BACK);
			KeyPushFlags::Z = true;
		}
		if (KeyPushFlags::Z == true && AppSession::KEY_BUFFER[KEY_INPUT_Z] == 0) {
			KeyPushFlags::Z = false;
		}
	}
	else {

		if (KeyPushFlags::X == false && AppSession::KEY_BUFFER[KEY_INPUT_X] == 1) {
			CONFIRMING_FLAG = false;
			DxLib::PlaySoundMem(SoundHandles::BACKWARD, DX_PLAYTYPE_BACK);
			KeyPushFlags::X = true;
		}
		if (KeyPushFlags::X == true && AppSession::KEY_BUFFER[KEY_INPUT_X] == 0) {
			KeyPushFlags::X = false;
		}

		if (KeyPushFlags::ENTER == false && AppSession::KEY_BUFFER[KEY_INPUT_RETURN] == 1) {
			determined_flag = true;
			DxLib::PlaySoundMem(SoundHandles::FORWARD, DX_PLAYTYPE_BACK);
			KeyPushFlags::ENTER = true;
		}
		if (KeyPushFlags::ENTER == true && AppSession::KEY_BUFFER[KEY_INPUT_RETURN] == 0) {
			KeyPushFlags::ENTER = false;
		}

	}

}


void NicknameInput::digitslide_left() {
	if (operating_digit >= 1) --operating_digit;
	DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_BACK);
}


void NicknameInput::digitslide_right() {
	if (operating_digit <= 14) ++operating_digit;
	DxLib::PlaySoundMem(SoundHandles::CURSORMOVE, DX_PLAYTYPE_BACK);
}


void NicknameInput::draw() {
	DxLib::DrawGraph(0, 0, ImageHandles::SCREEN_BACKGROUND, TRUE);
	int x = 0;
	for (int i = 0; i <= 15; i++) {
		dials.at(i).draw_character((x += 64) - 48, Screen::SCREEN_RESOLUTION_Y / 2);
		if (i == operating_digit && CONFIRMING_FLAG == false) {
			dials.at(i).draw_cursor(x - 24, Screen::SCREEN_RESOLUTION_Y / 2);
		}
	}
	if (CONFIRMING_FLAG == false) {
		DxLib::DrawFormatStringToHandle(0, 100, Colors::MAZENTA, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "プレイヤー名を入力してランキングに参加しよう");
		DxLib::DrawFormatStringToHandle(0, 650, Colors::MAZENTA, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "↑↓で文字をえらぶ　←→でカーソルを移動　Zで確定");
	}
	else {
		DxLib::DrawFormatStringToHandle(0, 100, Colors::MAZENTA, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "これでよろしいですか？");
		DxLib::DrawFormatStringToHandle(0, 650, Colors::MAZENTA, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "ENTERで決定　Xで編集に戻る");
	}
}


string NicknameInput::get() {
	string s("");
	for (int i = 0; i <= 15; i++) {
		s += dials.at(i).get();
	}
	return s;
}