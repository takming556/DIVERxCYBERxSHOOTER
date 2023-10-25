#include <string>
#include "DxLib.h"
#include "StageNameDisplay.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"
#include "FontHandles.h"

using std::wstring;

unsigned int StageNameDisplay::STAGE_NUM_INIT_POS_X = 100;
unsigned int StageNameDisplay::STAGE_NUM_INIT_POS_Y = 600;
unsigned int StageNameDisplay::MAIN_INIT_POS_Y = 540;
unsigned int StageNameDisplay::SUB_INIT_POS_Y = 450;

unsigned int StageNameDisplay::DURATION = 5000;

StageNameDisplay::StageNameDisplay(
	wstring given_stage_num,
	wstring given_stage_name_main,
	wstring given_stage_name_sub
) :
	stage_num(given_stage_num),
	stage_name_main(given_stage_name_main),
	stage_name_sub(given_stage_name_sub),
	generated_clock(DxLib::GetNowCount())
{
}

void StageNameDisplay::draw() {
	int elapsed_time = DxLib::GetNowCount() - generated_clock;
	
	int main_left_pos_x = 125;
	int sub_left_pos_x = 200;

	if (stage_num == L"STAGE1") {
		main_left_pos_x = 180;
		sub_left_pos_x = 210;
	}
	else if (stage_num == L"STAGE2") {
		main_left_pos_x = 165;
		sub_left_pos_x = 250;
	}
	else if (stage_num == L"STAGE3") {
		main_left_pos_x = 35;
		sub_left_pos_x = 140;
	}

	Position draw_positon_stage_num = InFieldPosition(STAGE_NUM_INIT_POS_X, STAGE_NUM_INIT_POS_Y).get_draw_position();
	Position draw_positon_main = InFieldPosition(main_left_pos_x, MAIN_INIT_POS_Y).get_draw_position();
	Position draw_positon_sub = InFieldPosition(sub_left_pos_x, SUB_INIT_POS_Y).get_draw_position();
	if (elapsed_time < DURATION) {
		DxLib::DrawFormatStringToHandle(	// 第何ステージ
			draw_positon_stage_num.x,
			draw_positon_stage_num.y,
			Colors::CYAN,
			FontHandles::STAGE_NUM_TEXT,
			stage_num.c_str()
		);
		DxLib::DrawFormatStringToHandle(	// ステージのメインタイトル
			draw_positon_main.x,
			draw_positon_main.y,
			Colors::CYAN,
			FontHandles::STAGE_NAME_MAIN_TEXT,
			stage_name_main.c_str()
		);
		DxLib::DrawFormatStringToHandle(	// ステージのサブタイトル
			draw_positon_sub.x,
			draw_positon_sub.y,
			Colors::CYAN,
			FontHandles::STAGE_NAME_SUB_TEXT,
			stage_name_sub.c_str()
		);
	}
}