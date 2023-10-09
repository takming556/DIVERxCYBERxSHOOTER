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

Scenario::Scenario(wstring given_music_name) :
	kept_clock(DxLib::GetNowCount()),
	music_name(given_music_name),
	music_name_generated_clock(DxLib::GetNowCount())
{
}

void Scenario::update() {
	int music_name_elapsed_time = DxLib::GetNowCount() - music_name_generated_clock;
	int music_name_distance = music_name_elapsed_time * MUSIC_NAME_SCROLL_SPEED / 1000;
	int music_name_pos_x = MUSIC_NAME_INIT_POS_X - music_name_distance;
	Position music_name_draw_position = InFieldPosition(music_name_pos_x, MUSIC_NAME_INIT_POS_Y).get_draw_position();
	DxLib::DrawFormatStringToHandle(
		music_name_draw_position.x,
		music_name_draw_position.y,
		Colors::WHITE,
		FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32,
		music_name.c_str()
	);
}
