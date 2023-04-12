#pragma once

class SoundHandles {
private:
	SoundHandles() {}
public:
	static void LOAD_ALL_SOUNDS();
	static int CURSORMOVE;
	static int FORWARD;
	static int BACKWARD;
	static int MYSHOT;
	static int ENEMYSHOT;
	static int MYHIT;
	static int ENEMYHIT;
	static int ZAKOCRASH;
	static int BOSSCRASH;

	static int STAGE1BGM;
};