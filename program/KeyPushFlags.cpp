#include "class.h"


char KeyPushFlags::KEY_BUFFER[256];
bool KeyPushFlags::Z;
bool KeyPushFlags::X;
bool KeyPushFlags::UP;
bool KeyPushFlags::DOWN;
bool KeyPushFlags::RIGHT;
bool KeyPushFlags::LEFT;


void KeyPushFlags::INITIALIZE() {
	for (int i = 0; i < 256; i++) {
		KeyPushFlags::KEY_BUFFER[i] = NULL;
	}
	KeyPushFlags::Z = false;
	KeyPushFlags::X = false;
	KeyPushFlags::UP = false;
	KeyPushFlags::DOWN = false;
	KeyPushFlags::RIGHT = false;
	KeyPushFlags::LEFT = false;
}