#include "DxLib.h"
#include "class.h"


double DebugParams::GAME_TIME;
unsigned int DebugParams::ACTUAL_FPS;
double DebugParams::INSTANT_FPS;
int DebugParams::SLEEP_TIME;
unsigned int DebugParams::OBJECTS;


void DebugParams::INITIALIZE() {
	GAME_TIME = 0.0;
	ACTUAL_FPS = 0U;
	INSTANT_FPS = 0.0;
	SLEEP_TIME = 0;
	OBJECTS = 0U;
}


void DebugParams::DRAW() {
	unsigned int y = 0;
	DxLib::DrawFormatString(670, y += 15, Colors::YELLOW, "GAME_TIME(s) = %lf", GAME_TIME);
	DxLib::DrawFormatString(670, y += 15, Colors::YELLOW, "LIMIT_FPS = %d", SettingParams::LIMIT_FPS);
	DxLib::DrawFormatString(670, y += 15, Colors::YELLOW, "ACTUAL_FPS = %d", ACTUAL_FPS);
	DxLib::DrawFormatString(670, y += 15, Colors::YELLOW, "INSTANT_FPS = %lf", INSTANT_FPS);
	DxLib::DrawFormatString(670, y += 15, Colors::YELLOW, "OBJECTS = %d", OBJECTS);
	DxLib::DrawFormatString(670, y += 15, Colors::YELLOW, "SLEEP_TIME(ms) = %d", DebugParams::SLEEP_TIME);

}