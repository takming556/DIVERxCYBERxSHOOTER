#include "DxLib.h"
#include "Colors.h"
#include "DebugParams.h"
#include "SettingParams.h"


bool DebugParams::DEBUG_FLAG;
double DebugParams::GAME_TIME;
double DebugParams::SURVIVAL_TIME;
unsigned int DebugParams::SURVIVAL_TIME_SCORE;
unsigned int DebugParams::ACTUAL_FPS;
double DebugParams::INSTANT_FPS;
int DebugParams::SLEEP_TIME;
unsigned int DebugParams::OBJECTS;
double DebugParams::MY_CHARACTER_INFIELD_X;
double DebugParams::MY_CHARACTER_INFIELD_Y;
double DebugParams::MY_CHARACTER_DRAW_X;
double DebugParams::MY_CHARACTER_DRAW_Y;


//double DebugParams::xC;
//double DebugParams::yC;
//double DebugParams::x1;
//double DebugParams::y1;
//double DebugParams::x2;
//double DebugParams::y2;
//double DebugParams::a;
//double DebugParams::b;
//double DebugParams::c;
//double DebugParams::upper;
//double DebugParams::lower;
//double DebugParams::distance;
//double DebugParams::r;
//bool DebugParams::distance_lessthan_r;
//double DebugParams::dot1;
//double DebugParams::dot2;
//bool DebugParams::eikaku1;
//bool DebugParams::eikaku2;
//double DebugParams::d1;
//double DebugParams::d2;
//bool DebugParams::d1_lessthan_r;
//bool DebugParams::d2_lessthan_r;
//double DebugParams::cross;
//bool DebugParams::is_circle_center_included;



void DebugParams::INITIALIZE() {
	DEBUG_FLAG = false;
	GAME_TIME = 0.0;
	SURVIVAL_TIME = 0.0;
	ACTUAL_FPS = 0U;
	INSTANT_FPS = 0.0;
	SLEEP_TIME = 0;
	OBJECTS = 0U;
	MY_CHARACTER_INFIELD_X = 0.0;
	MY_CHARACTER_INFIELD_Y = 0.0;
	MY_CHARACTER_DRAW_X = 0.0;
	MY_CHARACTER_DRAW_Y = 0.0;
	SURVIVAL_TIME_SCORE = 0;
}


void DebugParams::DRAW() {
	unsigned int y = 0;
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"GAME_TIME(s) = %lf", GAME_TIME);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"SURVIVAL_TIME(s) = %lf", SURVIVAL_TIME);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"SURVIVAL_TIME_SCORE = %u", DebugParams::SURVIVAL_TIME_SCORE);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"LIMIT_FPS = %d", SettingParams::LIMIT_FPS);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"ACTUAL_FPS = %d", ACTUAL_FPS);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"INSTANT_FPS = %lf", INSTANT_FPS);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"OBJECTS = %d", OBJECTS);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"SLEEP_TIME(ms) = %d", DebugParams::SLEEP_TIME);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"MY_FIELD_X = %lf", DebugParams::MY_CHARACTER_INFIELD_X);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"MY_FIELD_Y = %lf", DebugParams::MY_CHARACTER_INFIELD_Y);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"MY_DRAW_X = %lf", DebugParams::MY_CHARACTER_DRAW_X);
	DxLib::DrawFormatString(670, y += 16, Colors::YELLOW, L"MY_DRAW_Y = %lf", DebugParams::MY_CHARACTER_DRAW_Y);
	//y = 0;
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"xC = %lf", xC);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"yC = %lf", yC);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"x1 = %lf", x1);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"y1 = %lf", y1);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"x2 = %lf", x2);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"y2 = %lf", y2);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"a = %lf", a);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"b = %lf", b);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"c = %lf", c);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"upper = %lf", upper);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"lower = %lf", lower);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"distance = %lf", distance);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"r = %lf", r);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"distance < r = %s", distance_lessthan_r ? L"true" : L"false");
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"dot1 = %lf", dot1);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"dot2 = %lf", dot2);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"eikaku1 = %s", eikaku1 ? L"true" : L"false");
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"eikaku2 = %s", eikaku2 ? L"true" : L"false");
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"d1 = %lf", d1);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"d2 = %lf", d2);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"d1 < r = %s", d1_lessthan_r ? L"true" : L"false");
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"d2 < r = %s", d2_lessthan_r ? L"true" : L"false");
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"cross = %lf", cross);
	//DxLib::DrawFormatString(0, y += 16, Colors::CYAN, L"included = %s", is_circle_center_included ? L"true" : L"false");
}