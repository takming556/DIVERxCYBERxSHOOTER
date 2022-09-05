#include "DxLib.h"
#include "class.h"
#include "extern.h"


//プロトタイプ宣言たち
void LoadAllGraph();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);            //ウィンドウ表示 入/切
	SetMainWindowText("TUDCC-ShootingGame");
	SetGraphMode(Screen::SCREEN_RESOLUTION_X, Screen::SCREEN_RESOLUTION_Y, 32);  //画面解像度, 色深度を設定
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DxLib_Init();                      //DXライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);     //描画先を裏画面に設定

	LoadAllGraph();


	AppSession app_session;


	while (true) {
		if (ProcessMessage() != 0)break; //ウィンドウの閉じるボタンが押下されるとwhile無限ループを抜ける

		ClearDrawScreen();

		app_session.update();

		ScreenFlip();

	}
}


void LoadAllGraph() {
	int hFieldBackground = LoadGraph("image/field.png");
	int hTestShooter = LoadGraph("image/test_shooter.png");
	int hBlueMarble = LoadGraph("image/blue_marble.png");
	int hRedMarble = LoadGraph("image/red_marble.png");
}