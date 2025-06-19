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
	Scene nowScene;
	TitleSceneState nowTitleSceneState;
	MainMenuCursorPos nowMainMenuCursorPos;
	MainMenuPracticeCursorPos nowMainMenuPracticeCursorPos;
	bool isPracticeSelected;
	unique_ptr<GameConductor> gameConductor;
	//unique_ptr<NicknameInput> nickname_input;
	LONGLONG lastScreenFlippedClock;
	LONGLONG lastSleepStartedClock;
	LONGLONG lastSleepEndedClock;
	int keptClockForMeasureFps;
	int lastCursorMovedUpClockForTitleScreen;
	int lastCursorMovedDownClockForTitleScreen;
	static const unsigned int KEY_REPEAT_FREQUENCY;
	unsigned int flipCount;
public:
	static void INITIALIZE();
	AppSession();
	void Update();
	void GetKeyInputState();
	void RespondToKeyInput();
	//int send_sql(wstring nickname);
	static char KBD_BUFFER[256];
	static int PAD_BUFFER;
	//void output_playlog(wstring nickname);
	static bool IS_WINDOW_CLOSE_REQUESTED;
};
