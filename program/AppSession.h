#pragma once
#include <memory>
#include <string>
#include "DxLib.h"
#include "enum.h"

#include "GameConductor.h"
#include "NicknameInput.h"

using std::wstring;
using std::unique_ptr;

//class GameConductor;
//class NicknameInput;

class AppSession {
private:
	Scene now_scene;
	TitleSceneState now_title_scene_state;
	MainMenuCursorPos now_main_menu_cursor_pos;
	MainMenuPracticeCursorPos now_main_menu_practice_cursor_pos;
	bool practice_selected_flag;
	unique_ptr<GameConductor> game_conductor;
	//unique_ptr<NicknameInput> nickname_input;
	LONGLONG last_screenflipped_clock;
	LONGLONG last_sleep_started_clock;
	LONGLONG last_sleep_ended_clock;
	int clock_keeper_for_measure_fps;
	unsigned int flip_count;
public:
	static void INITIALIZE();
	AppSession();
	void update();
	void get_keyinput_state();
	void respond_to_keyinput();
	//int send_sql(wstring nickname);
	static char KBD_BUFFER[256];
	static int PAD_BUFFER;
	//void output_playlog(wstring nickname);
	static bool WINDOW_CLOSE_FLAG;
};
