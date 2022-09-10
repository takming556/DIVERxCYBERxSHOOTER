#include <memory>
#include "class.h"

using std::make_unique;

AppSession::AppSession() :
	now_scene(Scene::GAMING),
	game_conductor(make_unique<GameConductor>())
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
}