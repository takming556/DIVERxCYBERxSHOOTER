#include "DxLib.h"
#include "class.h"
#include "extern.h"


//�v���g�^�C�v�錾����
void LoadAllGraph();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);            //�E�B���h�E�\�� ��/��
	SetMainWindowText("TUDCC-ShootingGame");
	SetGraphMode(Screen::SCREEN_RESOLUTION_X, Screen::SCREEN_RESOLUTION_Y, 32);  //��ʉ𑜓x, �F�[�x��ݒ�
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DxLib_Init();                      //DX���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK);     //�`���𗠉�ʂɐݒ�

	LoadAllGraph();


	AppSession app_session;


	while (true) {
		if (ProcessMessage() != 0)break; //�E�B���h�E�̕���{�^��������������while�������[�v�𔲂���

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