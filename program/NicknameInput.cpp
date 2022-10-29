#include "DxLib.h"
#include "class.h"

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

		if (KeyPushFlags::Z == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_Z] == 1) {
			CONFIRMING_FLAG = true;
			KeyPushFlags::Z = true;
		}
		if (KeyPushFlags::Z == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_Z] == 0) {
			KeyPushFlags::Z = false;
		}
	}
	else {

		if (KeyPushFlags::X == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_X] == 1) {
			CONFIRMING_FLAG = false;
			KeyPushFlags::X = true;
		}
		if (KeyPushFlags::X == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_X] == 0) {
			KeyPushFlags::X = false;
		}

		if (KeyPushFlags::ENTER == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_RETURN] == 1) {
			determined_flag = true;
			KeyPushFlags::ENTER = true;
		}
		if (KeyPushFlags::ENTER == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_RETURN] == 0) {
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
		DxLib::DrawFormatStringToHandle(0, 100, Colors::MAZENTA, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "�v���C���[������͂��ă����L���O�ɎQ�����悤");
		DxLib::DrawFormatStringToHandle(0, 650, Colors::MAZENTA, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "�����ŕ���������ԁ@�����ŃJ�[�\�����ړ��@Z�Ŋm��");
	}
	else {
		DxLib::DrawFormatStringToHandle(0, 100, Colors::MAZENTA, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "����ł�낵���ł����H");
		DxLib::DrawFormatStringToHandle(0, 650, Colors::MAZENTA, FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32, "ENTER�Ō���@X�ŕҏW�ɖ߂�");
	}
}


string NicknameInput::get() {
	string s("");
	for (int i = 0; i <= 15; i++) {
		s += dials.at(i).get();
	}
	return s;
}