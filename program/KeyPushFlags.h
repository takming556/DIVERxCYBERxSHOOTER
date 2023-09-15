#pragma once

class KeyPushFlags {
private:
	KeyPushFlags() {}
public:
	static void INITIALIZE();
	//static char KEY_BUFFER[256];
	static bool Z;
	static bool X;
	static bool UP;
	static bool DOWN;
	static bool RIGHT;
	static bool LEFT;
	static bool F3;
	static bool F4;
	static bool ENTER;
};