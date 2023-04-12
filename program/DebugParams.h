#pragma once

class DebugParams {
private:
	DebugParams() {}
public:
	static void INITIALIZE();
	static void DRAW();
	static bool DEBUG_FLAG;
	static unsigned int ACTUAL_FPS;
	static double INSTANT_FPS;
	static int SLEEP_TIME;
	static unsigned int OBJECTS;
	static double GAME_TIME;
	static double MY_CHARACTER_INFIELD_X;
	static double MY_CHARACTER_INFIELD_Y;
	static double MY_CHARACTER_DRAW_X;
	static double MY_CHARACTER_DRAW_Y;
};