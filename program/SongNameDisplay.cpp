#include "SongNameDisplay.h"
#include "DxLib.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"
#include "FontHandles.h"


unsigned int SongNameDisplay::POS_X = 700;
unsigned int SongNameDisplay::POS_Y = 700;
unsigned int SongNameDisplay::DURATION = 7000; // ミリ秒


SongNameDisplay::SongNameDisplay(wstring given_song_name):
	song_name(given_song_name),
	generated_clock(DxLib::GetNowCount())
{
}


void SongNameDisplay::draw() {
	int elapsed_time = DxLib::GetNowCount() - generated_clock;
	if (elapsed_time < DURATION) {
		DxLib::DrawFormatStringToHandle(
			POS_X,
			POS_Y,
			Colors::WHITE,
			FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32,
			song_name.c_str()
		);
	}
}