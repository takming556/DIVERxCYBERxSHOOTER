#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;

AppSession::AppSession() :
	now_scene(Scene::GAMING),
	game_conductor(make_unique<GameConductor>()),
	fps_limit(60),
	last_screenflipped_clock(1),		//0‚É‚æ‚éœŽZ‚ð–hŽ~‚·‚é‚½‚ßA‚ ‚¦‚Ä1‚Å‰Šú‰»
	clock_keeper_for_measure_fps(0),
	flip_count(0),
	actual_fps(0),
	instant_fps(0.0)
{
}


void AppSession::update() {

	switch (now_scene) {
	case Scene::TITLE:
		break;
	case Scene::GAMING:
		game_conductor->update();
		break;
	case Scene::RESULT:
		break;
	case Scene::RANKING:
		break;
	}

	DxLib::DrawFormatString(670, 15, Colors::YELLOW, "fps_limit = %d", fps_limit);
	DxLib::DrawFormatString(670, 30, Colors::YELLOW, "current_fps(actual) = %d", actual_fps);
	DxLib::DrawFormatString(670, 45, Colors::YELLOW, "current_fps(instant) = %lf", instant_fps);

	LONGLONG now_clock = DxLib::GetNowHiPerformanceCount();
	int sleep_time = (last_screenflipped_clock + ((1.0 / fps_limit) * 1000 * 1000) - now_clock) / 1000;
	DxLib::WaitTimer(sleep_time);
	DxLib::DrawFormatString(670, 60, Colors::YELLOW, "sleep_time(ms) = %d", sleep_time);

	LONGLONG screenflip_postpone_time = 1.0 / fps_limit * 1000 * 1000;
	if (now_clock > last_screenflipped_clock + screenflip_postpone_time) {
		DxLib::ScreenFlip();		//— ‰æ–Ê‚Ì“à—e‚ð•\‰æ–Ê‚É”½‰f
		DxLib::ClearDrawScreen();	//— ‰æ–Ê‚ðƒNƒŠƒA
		LONGLONG delta_time = now_clock - last_screenflipped_clock;
		instant_fps = 1.0 * 1000 * 1000 / delta_time;
		flip_count++;
		last_screenflipped_clock = DxLib::GetNowHiPerformanceCount();
	}

	if (DxLib::GetNowCount() > clock_keeper_for_measure_fps + 1000) {
		actual_fps = flip_count;
		flip_count = 0;
		clock_keeper_for_measure_fps = DxLib::GetNowCount();
	}
}