#include <string>
#include "DxLib.h"
#include "class.h"

using std::string;

MyCharacter::MyCharacter(string character_name) :
	Character(INITIAL_POSITION_X, INITIAL_POSITION_Y),
	SPS(4.0),
	is_z_key_pushed(false),
	is_up_key_pushed(false),
	is_down_key_pushed(false),
	is_left_key_pushed(false),
	is_right_key_pushed(false),
	name(character_name),
	life(3)
{
}


void MyCharacter::update() {

}


void MyCharacter::draw() {

}


void MyCharacter::respond_to_keyinput(char key_buffer[]) {

	//Z�L�[
	if (is_z_key_pushed == false && key_buffer[KEY_INPUT_Z] == 1) {	//Z�L�[�����܂ŉ����Ă��Ȃ��������A�����n�߂��u��
		is_z_key_pushed = true;

	}
	else if (is_z_key_pushed == true && key_buffer[KEY_INPUT_Z] == 0) {	//Z�L�[�����܂ŉ����Ă������A�������u��
		is_z_key_pushed = false;
	}
	else if (is_z_key_pushed == true && key_buffer[KEY_INPUT_Z] == 1) {	//Z�L�[�����܂ŉ����Ă������A���������Ă���

	}

	//X�L�[
	//if (is_x_key_pushed == false && key_buffer[KEY_INPUT_X] == 1) {
	//	is_x_key_pushed = true;
	//}
	//else if (is_x_key_pushed == true && key_buffer[KEY_INPUT_X] == 0) {
	//	is_x_key_pushed = false;
	//}

	//����L�[
	if (is_up_key_pushed == false && key_buffer[KEY_INPUT_UP] == 1) {
		is_up_key_pushed = true;
	}
	else if (is_up_key_pushed == true && key_buffer[KEY_INPUT_UP] == 0) {
		is_up_key_pushed = false;
	}

	//�����L�[
	if (is_down_key_pushed == false && key_buffer[KEY_INPUT_DOWN] == 1) {
		is_down_key_pushed = true;
	}
	else if (is_down_key_pushed == true && key_buffer[KEY_INPUT_DOWN] == 0) {
		is_down_key_pushed = false;
	}

	//�����L�[
	if (is_left_key_pushed == false && key_buffer[KEY_INPUT_LEFT] == 1) {
		is_left_key_pushed = true;
	}
	else if (is_left_key_pushed == true && key_buffer[KEY_INPUT_LEFT] == 0) {
		is_left_key_pushed = false;
	}

	//�E���L�[
	if (is_right_key_pushed == false && key_buffer[KEY_INPUT_RIGHT] == 1) {
		is_right_key_pushed = true;
	}
	else if (is_right_key_pushed == true && key_buffer[KEY_INPUT_RIGHT] == 0) {
		is_right_key_pushed = false;
	}

}


void MyCharacter::move_upward() {
	position_x += -1;
}


void MyCharacter::move_downward() {
	position_x += 1;
}


void MyCharacter::move_leftward() {
	position_y += -1;
}


void MyCharacter::move_rightward() {
	position_y += 1;
}