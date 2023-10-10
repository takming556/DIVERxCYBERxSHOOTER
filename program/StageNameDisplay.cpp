#include <string>
#include "DxLib.h"
#include "StageNameDisplay.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"
#include "FontHandles.h"

using std::wstring;

unsigned int StageNameDisplay::INIT_POS_X = 700;
unsigned int StageNameDisplay::INIT_POS_Y = 700;
unsigned int StageNameDisplay::SCROLL_SPEED = 150;
unsigned int StageNameDisplay::DURATION = 4000; // �~���b

StageNameDisplay::StageNameDisplay(wstring given_stage_name) :
	stage_name(given_stage_name),
	generated_clock(DxLib::GetNowCount())
{
}

void StageNameDisplay::draw() {
	int elapsed_time = DxLib::GetNowCount() - generated_clock;
	int distance = elapsed_time * SCROLL_SPEED / 1000;
	int pos_x = INIT_POS_X - distance;
	Position draw_positon = InFieldPosition(pos_x, INIT_POS_Y).get_draw_position();
	if (elapsed_time > DURATION) {
		DxLib::DrawFormatStringToHandle(
			draw_positon.x,
			draw_positon.y,
			Colors::CYAN,
			FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32,
			stage_name.c_str()
		);
	}
}