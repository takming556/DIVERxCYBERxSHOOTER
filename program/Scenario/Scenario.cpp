#include <string>
#include "DxLib.h"
#include "Scenario/Scenario.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"
#include "FontHandles.h"

using std::wstring;

unsigned int Scenario::MUSIC_NAME_INIT_POS_X = 700;
unsigned int Scenario::MUSIC_NAME_INIT_POS_Y = 700;
unsigned int Scenario::MUSIC_NAME_SCROLL_SPEED = 150;

Scenario::Scenario() :
	kept_clock(DxLib::GetNowCount())
{
	INITIALIZE();
}

void Scenario::INITIALIZE() {
	Scenario::MUSIC_NAME_LAST_APPENDED_CLOCK = DxLib::GetNowCount();
}

void Scenario::update() {
}

void Scenario::DISPLAY_MUSIC_NAME(wstring& given_music_name) {
	int music_name_elapsed_time = DxLib::GetNowCount() - MUSIC_NAME_LAST_APPENDED_CLOCK;
	int music_name_distance = music_name_elapsed_time * MUSIC_NAME_SCROLL_SPEED / 1000;
	int music_name_pos_x = MUSIC_NAME_INIT_POS_X - music_name_distance;
	Position music_name_draw_position = InFieldPosition(music_name_pos_x, MUSIC_NAME_INIT_POS_Y).get_draw_position();
	DxLib::DrawFormatStringToHandle(
		music_name_draw_position.x,
		music_name_draw_position.y,
		Colors::WHITE,
		FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32,
		given_music_name.c_str()
	);
}