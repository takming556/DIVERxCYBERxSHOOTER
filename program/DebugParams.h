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

	//static double xC;
	//static double yC;
	//static double x1;
	//static double y1;
	//static double x2;
	//static double y2;
	//static double a;
	//static double b;
	//static double c;
	//static double upper;
	//static double lower;
	//static double distance;
	//static double r;
	//static bool distance_lessthan_r;
	//static double dot1;
	//static double dot2;
	//static bool eikaku1;
	//static bool eikaku2;
	//static double d1;
	//static double d2;
	//static bool d1_lessthan_r;
	//static bool d2_lessthan_r;
	//static double cross;
	//static bool is_circle_center_included;
};