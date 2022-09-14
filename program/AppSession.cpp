#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;

AppSession::AppSession() :
	now_scene(Scene::GAMING),
	game_conductor(make_unique<GameConductor>()),
	fps_limit(60),
	clock_keeper_for_screenflip(0)
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

	LONGLONG screenflip_postpone_time = 1.0 / fps_limit * 1000 * 1000;
	if (DxLib::GetNowHiPerformanceCount() > clock_keeper_for_screenflip + screenflip_postpone_time) {
		DxLib::ScreenFlip();
		DxLib::ClearDrawScreen();
		clock_keeper_for_screenflip = GetNowHiPerformanceCount();
	}
}