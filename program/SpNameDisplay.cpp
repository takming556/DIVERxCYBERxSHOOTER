﻿#include <string>
#include "DxLib.h"
#include "SpNameDisplay.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"
#include "FontHandles.h"

using std::wstring;

unsigned int SpNameDisplay::INIT_POS_X = 700;
unsigned int SpNameDisplay::INIT_POS_Y = 700;
unsigned int SpNameDisplay::SCROLL_SPEED = 150;

SpNameDisplay::SpNameDisplay(wstring given_sp_name):
	sp_name(given_sp_name),
	generated_clock(DxLib::GetNowCount())
{
}

void SpNameDisplay::draw() {
	int elapsed_time = DxLib::GetNowCount() - generated_clock;
	int distance = elapsed_time * SCROLL_SPEED / 1000;
	int pos_x = INIT_POS_X - distance;
	Position draw_position = InFieldPosition(pos_x, INIT_POS_Y).get_draw_position();
	DxLib::DrawFormatStringToHandle(
		draw_position.x,
		draw_position.y,
		Colors::CYAN,
		FontHandles::SP_NAME_TEXT,
		sp_name.c_str()
	);
}