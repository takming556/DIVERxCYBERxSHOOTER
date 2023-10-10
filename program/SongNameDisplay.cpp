#include <string>
#include "SongNameDisplay.h"
#include "DxLib.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"
#include "FontHandles.h"

using std::wstring;

unsigned int SongNameDisplay::POS_X = 700;
unsigned int SongNameDisplay::POS_Y = 50;
unsigned int SongNameDisplay::SCROLL_SPEED = 100;
unsigned int SongNameDisplay::DURATION = 4000; // ミリ秒


SongNameDisplay::SongNameDisplay(wstring given_song_name):
	song_name(given_song_name),
	generated_clock(DxLib::GetNowCount())
{
}


void SongNameDisplay::draw() {
	int elapsed_time = DxLib::GetNowCount() - generated_clock;
	int distance = elapsed_time * SCROLL_SPEED / 1000;
	int pos_x = POS_X - distance;
	Position draw_position = InFieldPosition(pos_x, POS_Y).get_draw_position();
	if (elapsed_time < DURATION) {
		DxLib::DrawFormatStringToHandle(
			draw_position.x,
			draw_position.y,
			Colors::WHITE,
			FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32,
			song_name.c_str()
		);
	}
}