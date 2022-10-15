#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;

AppSession::AppSession() :
	now_scene(Scene::GAMING),
	game_conductor(make_unique<GameConductor>()),
	last_screenflipped_clock(1),		//0‚É‚æ‚éœŽZ‚ð–hŽ~‚·‚é‚½‚ßA‚ ‚¦‚Ä1‚Å‰Šú‰»
	clock_keeper_for_measure_fps(0),
	flip_count(0)
{
}


void AppSession::update() {

	get_keyinput_state();
	respond_to_keyinput();

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

	if (DebugParams::DEBUG_FLAG == true) DebugParams::DRAW();

	LONGLONG now_clock = DxLib::GetNowHiPerformanceCount();
	DebugParams::SLEEP_TIME = (last_screenflipped_clock + ((1.0 / SettingParams::LIMIT_FPS) * 1000 * 1000) - now_clock) / 1000;
	DxLib::WaitTimer(DebugParams::SLEEP_TIME);

	LONGLONG screenflip_postpone_time = 1.0 / SettingParams::LIMIT_FPS * 1000 * 1000;
	if (now_clock > last_screenflipped_clock + screenflip_postpone_time) {
		DxLib::ScreenFlip();		//— ‰æ–Ê‚Ì“à—e‚ð•\‰æ–Ê‚É”½‰f
		DxLib::ClearDrawScreen();	//— ‰æ–Ê‚ðƒNƒŠƒA
		LONGLONG delta_time = now_clock - last_screenflipped_clock;
		DebugParams::INSTANT_FPS = 1.0 * 1000 * 1000 / delta_time;
		flip_count++;
		last_screenflipped_clock = DxLib::GetNowHiPerformanceCount();
	}

	if (DxLib::GetNowCount() > clock_keeper_for_measure_fps + 1000) {
		DebugParams::ACTUAL_FPS = flip_count;
		flip_count = 0;
		clock_keeper_for_measure_fps = DxLib::GetNowCount();
	}
}


void AppSession::get_keyinput_state() {
	DxLib::GetHitKeyStateAll(KeyPushFlags::KEY_BUFFER);
}


void AppSession::respond_to_keyinput() {
	if (KeyPushFlags::F3 == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_F3] == 1) {
		KeyPushFlags::F3 = true;
		DebugParams::DEBUG_FLAG = !(DebugParams::DEBUG_FLAG);
	}
	if (KeyPushFlags::F3 == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_F3] == 0) {
		KeyPushFlags::F3 = false;
	}
}