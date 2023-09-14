#include "DxLib.h"
#include "AppSession.h"
#include "Screen/Screen.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "FontHandles.h"
#include "KeyPushFlags.h"
#include "DebugParams.h"
#include "SettingParams.h" 
#include "Colors.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	DxLib::ChangeWindowMode(TRUE);														//TRUEでウィンドウ表示、FALSEで全画面表示
	DxLib::SetMainWindowText("DIVER x CYBER x SHOOTER");								//ウィンドウのタイトルバーに表示される名前
	DxLib::SetAlwaysRunFlag(TRUE);														//非アクティブ時にも処理を続行する
	DxLib::SetGraphMode(Screen::SCREEN_RESOLUTION_X, Screen::SCREEN_RESOLUTION_Y, 32);	//画面解像度, 色深度を設定
	DxLib::SetDrawMode(DX_DRAWMODE_BILINEAR);
	DxLib::SetWaitVSyncFlag(FALSE);														//ScreenFlip()実行時に垂直同期信号を待機しない
	DxLib::DxLib_Init();																//DXライブラリ初期化処理
	DxLib::SetDrawScreen(DX_SCREEN_BACK);												//描画先を裏画面に設定

	AppSession::INITIALIZE();
	Colors::INITIALIZE();
	KeyPushFlags::INITIALIZE();
	DebugParams::INITIALIZE();
	SettingParams::INITIALIZE();
	ImageHandles::LOAD_ALL_IMAGE();
	SoundHandles::LOAD_ALL_SOUNDS();
	FontHandles::LOAD_ALL_FONT();


	AppSession app_session;


	while (true) {
		if (DxLib::ProcessMessage() != 0) break;	//ウィンドウの閉じるボタンが押下されるとwhile無限ループを抜ける

		app_session.update();

	}

	DxLib::DxLib_End();
	return 0;
}