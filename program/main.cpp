#include "DxLib.h"
#include "class.h"
#include "extern.h"


//プロトタイプ宣言
void LoadAllGraph();	//このゲームで使用するすべての画像ファイルを読み込む


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	DxLib::ChangeWindowMode(TRUE);														//ウィンドウ表示 入/切
	DxLib::SetMainWindowText("TUDCC-ShootingGame");
	DxLib::SetAlwaysRunFlag(TRUE);														//非アクティブ時にも処理を続行する
	DxLib::SetGraphMode(Screen::SCREEN_RESOLUTION_X, Screen::SCREEN_RESOLUTION_Y, 32);	//画面解像度, 色深度を設定
	DxLib::SetDrawMode(DX_DRAWMODE_BILINEAR);
	DxLib::SetWaitVSyncFlag(FALSE);														//ScreenFlip()実行時に垂直同期信号を待機しない
	DxLib::DxLib_Init();																//DXライブラリ初期化処理
	DxLib::SetDrawScreen(DX_SCREEN_BACK);												//描画先を裏画面に設定

	LoadAllGraph();


	AppSession app_session;
	//Field field;
	//Deziko deziko;

	while (true) {
		if (DxLib::ProcessMessage() != 0)break;	//ウィンドウの閉じるボタンが押下されるとwhile無限ループを抜ける

		app_session.update();
		//field.draw();
	}
}


void LoadAllGraph() {
	hFieldBackground = DxLib::LoadGraph("image/field.png");
	hTestShooter = DxLib::LoadGraph("image/test_shooter.png");
	hBlueMarble = DxLib::LoadGraph("image/blue_marble.png");
	hRedMarble = DxLib::LoadGraph("image/red_marble.png");
	hMajikichiSmile = DxLib::LoadGraph("image/majikichi_smile.png");
	hHandPower = DxLib::LoadGraph("image/hand_power.png");
	hPien = DxLib::LoadGraph("image/pien.png");
	hHeart = DxLib::LoadGraph("image/heart.png");
	hMeltingFace = DxLib::LoadGraph("image/melting_face.png");
	hThinkingFace = DxLib::LoadGraph("image/thinking_face.png");
	hSunGlassFace = DxLib::LoadGraph("image/sun_glass_face.png");
}