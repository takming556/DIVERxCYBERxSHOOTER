#include "DxLib.h"
#include "Colors.h"
#include "DebugParams.h"
#include "SettingParams.h"


bool DebugParams::DEBUG_FLAG;
double DebugParams::GAME_TIME;
unsigned int DebugParams::ACTUAL_FPS;
double DebugParams::INSTANT_FPS;
int DebugParams::SLEEP_TIME;
unsigned int DebugParams::OBJECTS;
double DebugParams::MY_CHARACTER_INFIELD_X;
double DebugParams::MY_CHARACTER_INFIELD_Y;
double DebugParams::MY_CHARACTER_DRAW_X;
double DebugParams::MY_CHARACTER_DRAW_Y;


void DebugParams::INITIALIZE() {
	DEBUG_FLAG = false;
	GAME_TIME = 0.0;
	ACTUAL_FPS = 0U;
	INSTANT_FPS = 0.0;
	SLEEP_TIME = 0;
	OBJECTS = 0U;
	MY_CHARACTER_INFIELD_X = 0.0;
	MY_CHARACTER_INFIELD_Y = 0.0;
	MY_CHARACTER_DRAW_X = 0.0;
	MY_CHARACTER_DRAW_Y = 0.0;
}


void DebugParams::DRAW() {
	unsigned int y = 0;
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, "GAME_TIME(s) = %lf", GAME_TIME);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, "LIMIT_FPS = %d", SettingParams::LIMIT_FPS);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, "ACTUAL_FPS = %d", ACTUAL_FPS);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, "INSTANT_FPS = %lf", INSTANT_FPS);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, "OBJECTS = %d", OBJECTS);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, "SLEEP_TIME(ms) = %d", DebugParams::SLEEP_TIME);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, "MY_FIELD_X = %lf", DebugParams::MY_CHARACTER_INFIELD_X);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, "MY_FIELD_Y = %lf", DebugParams::MY_CHARACTER_INFIELD_Y);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, "MY_DRAW_X = %lf", DebugParams::MY_CHARACTER_DRAW_X);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, "MY_DRAW_Y = %lf", DebugParams::MY_CHARACTER_DRAW_Y);
}