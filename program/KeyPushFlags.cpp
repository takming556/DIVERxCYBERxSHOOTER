﻿#include "KeyPushFlags.h"


//char KeyPushFlags::KEY_BUFFER[256];
bool KeyPushFlags::Z;
bool KeyPushFlags::X;
bool KeyPushFlags::UP;
bool KeyPushFlags::DOWN;
bool KeyPushFlags::RIGHT;
bool KeyPushFlags::LEFT;
bool KeyPushFlags::F3;
bool KeyPushFlags::F4;
bool KeyPushFlags::ENTER;


void KeyPushFlags::INITIALIZE() {
	//for (int i = 0; i < 256; i++) {
	//	KEY_BUFFER[i] = NULL;
	//}
	Z = false;
	X = false;
	UP = false;
	DOWN = false;
	RIGHT = false;
	LEFT = false;
	F3 = false;
	F4 = false;
	ENTER = false;
}