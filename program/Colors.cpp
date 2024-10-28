#include "DxLib.h"
#include "Colors.h"

int Colors::BLACK;
int Colors::RED;
int Colors::LIME;
int Colors::GREEN;
int Colors::BLUE;
int Colors::YELLOW;
int Colors::CYAN;
int Colors::MAZENTA;
int Colors::PURPLE;
int Colors::GRAY;
int Colors::WHITE;


void Colors::INITIALIZE() {
	BLACK = DxLib::GetColor(0, 0, 0);
	RED = DxLib::GetColor(255, 0, 0);
	LIME = DxLib::GetColor(0, 255, 0);
	GREEN = DxLib::GetColor(0, 128, 0);
	BLUE = DxLib::GetColor(0, 0, 255);
	YELLOW = DxLib::GetColor(255, 255, 0);
	CYAN = DxLib::GetColor(0, 255, 255);
	MAZENTA = DxLib::GetColor(255, 0, 255);
	PURPLE = DxLib::GetColor(128, 0, 128);
	GRAY = DxLib::GetColor (128, 128, 128);
	WHITE = DxLib::GetColor(255, 255, 255);
}