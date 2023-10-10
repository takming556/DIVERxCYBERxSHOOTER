#include <string>
#include <numbers>
#include "SongNameDisplay.h"
#include "DxLib.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"
#include "FontHandles.h"

using std::wstring;
using std::numbers::pi;

const unsigned int SongNameDisplay::INIT_POS_X = 700;
const unsigned int SongNameDisplay::POS_Y = 50;
const double SongNameDisplay::INIT_ARG = 1.0 * pi;
const double SongNameDisplay::INIT_SCROLL_SPEED = 10;
// unsigned int SongNameDisplay::DURATION = 4000; // ミリ秒


SongNameDisplay::SongNameDisplay(wstring given_song_name):
	pos_x(INIT_POS_X),
	arg(INIT_ARG),
	scroll_speed(INIT_SCROLL_SPEED),
	song_name(given_song_name),
	generated_clock(DxLib::GetNowCount()),
	last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
}


void SongNameDisplay::draw() {
	int elapsed_time = DxLib::GetNowCount() - generated_clock;

	if (elapsed_time < 100 && elapsed_time < 2000) {
		scroll_speed = 200;
	}
	else if (elapsed_time > 2000 && elapsed_time < 4000) {
		scroll_speed = 0;
		arg = 0.0 * pi;
	}
	else if (elapsed_time > 4000) {
		scroll_speed = 200;
	}

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = update_delta_time * scroll_speed / 1000 / 1000;
	double distance_x = distance * cos(arg);
	pos_x += distance_x;
	Position draw_position = InFieldPosition(pos_x, POS_Y).get_draw_position();
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	// if (elapsed_time < DURATION) {
	DxLib::DrawFormatStringToHandle(
		draw_position.x,
		draw_position.y,
		Colors::WHITE,
		FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32,
		song_name.c_str()
	);
	//}

}