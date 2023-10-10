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

// unsigned int StageNameDisplay::SCROLL_SPEED = 150;
unsigned int StageNameDisplay::DURATION = 5000; // ミリ秒

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
	
	// スクロール
	/*int distance = elapsed_time * SCROLL_SPEED / 1000;
	int pos_x = INIT_POS_X - distance;
	Position draw_positon = InFieldPosition(pos_x, INIT_POS_Y).get_draw_position();*/

	// wstringを型変換して中央揃えにする
	//const char main_char = stage_name_main;		// wstring->charの型変換
	//const char sub_char = stage_name_sub;
	//size_t main_length = strlen(main_char);		// 文字列の長さを取得
	//size_t sub_length = strlen(sub_char);

	//const TCHAR main_tchar = stage_name_main;	// wstring->TCHARの型変換
	//const TCHAR sub_tchar = stage_name_sub;
	//int draw_width_main = GetDrawStringWidth(stage_name_main, main_length);		// 文字列の描画幅を取得
	//int draw_width_sub = GetDrawStringWidth(stage_name_sub, sub_length);

	//int main_left_pos_x = (InFieldPosition::MAX_MOVABLE_BOUNDARY_X - draw_width_main) / 2;		// (表示領域の横幅 - 文字列の幅) ÷ 2 = 領域中央に描画する文字列の左端の座標
	//int sub_left_pos_x = (InFieldPosition::MAX_MOVABLE_BOUNDARY_X - draw_width_sub) / 2;

	// ベタ打ち
	int main_left_pos_x = 125;
	int sub_left_pos_x = 200;

	if (stage_num == L"STAGE1") {
		main_left_pos_x = 125;
		sub_left_pos_x = 170;
	}
	else if (stage_num == L"STAGE2") {
		main_left_pos_x = 125;
		sub_left_pos_x = 200;
	}
	else if (stage_num == L"STAGE3") {
		main_left_pos_x = 125;
		sub_left_pos_x = 200;
	}

	Position draw_positon_stage_num = InFieldPosition(STAGE_NUM_INIT_POS_X, STAGE_NUM_INIT_POS_Y).get_draw_position();
	Position draw_positon_main = InFieldPosition(main_left_pos_x, MAIN_INIT_POS_Y).get_draw_position();
	Position draw_positon_sub = InFieldPosition(sub_left_pos_x, SUB_INIT_POS_Y).get_draw_position();
	if (elapsed_time < DURATION) {
		DxLib::DrawFormatStringToHandle(	// Stageナンバー
			draw_positon_stage_num.x,
			draw_positon_stage_num.y,
			Colors::CYAN,
			FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32,
			stage_num.c_str()
		);
		DxLib::DrawFormatStringToHandle(	// 曲のメインタイトル
			draw_positon_main.x,
			draw_positon_main.y,
			Colors::CYAN,
			FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_64,
			stage_name_main.c_str()
		);
		DxLib::DrawFormatStringToHandle(	// 曲のサブタイトル
			draw_positon_sub.x,
			draw_positon_sub.y,
			Colors::CYAN,
			FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32,
			stage_name_sub.c_str()
		);
	}
}