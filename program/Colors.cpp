#include "DxLib.h"
#include "class.h"


int Colors::RED;
int Colors::GREEN;
int Colors::BLUE;
int Colors::YELLOW;
int Colors::CYAN;
int Colors::MAZENTA;


void Colors::INITIALIZE() {
	RED = DxLib::GetColor(255, 0, 0);
	GREEN = DxLib::GetColor(0, 255, 0);
	BLUE = DxLib::GetColor(0, 0, 255);
	YELLOW = DxLib::GetColor(255, 255, 0);
	CYAN = DxLib::GetColor(0, 255, 255);
	MAZENTA = DxLib::GetColor(255, 0, 255);
}