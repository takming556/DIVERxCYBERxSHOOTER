#include "DxLib.h"
#include "class.h"

Stage1::Stage1() :
	stage1_progress(Stage1Progress::A)
{
}


void Stage1::update() {
	elapsed_time = DxLib::GetNowCount() - kept_clock;

	if (stage1_progress == Stage1Progress::A && elapsed_time > 5000) {
		stage1_progress=Stage1Progress::B;
		kept_clock = DxLib::GetNowCount();
	}
	else if (stage1_progress == Stage1Progress::B && elapsed_time > 1000) {
		stage1_progress = Stage1Progress::B_LEFT_1;
		kept_clock = DxLib::GetNowCount();

	}
}