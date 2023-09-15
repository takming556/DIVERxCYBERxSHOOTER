#pragma once
#include <memory>
#include <string>
#include "DxLib.h"
#include "enum.h"

#include "GameConductor.h"
#include "NicknameInput.h"

using std::string;
using std::unique_ptr;

//class GameConductor;
//class NicknameInput;

class AppSession {
private:
	Scene now_scene;
	unique_ptr<GameConductor> game_conductor;
	//unique_ptr<NicknameInput> nickname_input;
	LONGLONG last_screenflipped_clock;
	int clock_keeper_for_measure_fps;
	unsigned int flip_count;
public:
	static void INITIALIZE();
	AppSession();
	void update();
	void get_keyinput_state();
	void respond_to_keyinput();
	//int send_sql(string nickname);
	static char KEY_BUFFER[256];
	//void output_playlog(string nickname);
};
