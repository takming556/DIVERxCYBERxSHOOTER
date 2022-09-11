#include "DxLib.h"
#include "class.h"
#include "extern.h"


//プロトタイプ宣言
void LoadAllGraph(); //このゲームで使用するすべての画像ファイルを読み込む


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);            //ウィンドウ表示 入/切
	SetMainWindowText("TUDCC-ShootingGame");
	SetGraphMode(Screen::SCREEN_RESOLUTION_X, Screen::SCREEN_RESOLUTION_Y, 32);  //画面解像度, 色深度を設定
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DxLib_Init();                      //DXライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);     //描画先を裏画面に設定

	LoadAllGraph();


	AppSession app_session;
	//Field field;
	//Deziko deziko;

	while (true) {
		if (ProcessMessage() != 0)break; //ウィンドウの閉じるボタンが押下されるとwhile無限ループを抜ける

		ClearDrawScreen();

		app_session.update();
		//field.draw();

		ScreenFlip();

	}
}


void LoadAllGraph() {
	hFieldBackground = LoadGraph("image/field.png");
	hTestShooter = LoadGraph("image/test_shooter.png");
	hBlueMarble = LoadGraph("image/blue_marble.png");
	hRedMarble = LoadGraph("image/red_marble.png");
	hMajikichiSmile = LoadGraph("image/majikichi_smile.png");
	hHandPower = LoadGraph("image/hand_power.png");
	hPien = LoadGraph("image/pien.png");
	hHeart = LoadGraph("image/heart.png");
	hMeltingFace = LoadGraph("image/melting_face.png");
	hThinkingFace = LoadGraph("image/thinking_face.png");
	hSunGlassFace = LoadGraph("image/sun_glass_face.png");
}