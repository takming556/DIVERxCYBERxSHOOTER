#include "DxLib.h"
#include "class.h"
#include "extern.h"


//�v���g�^�C�v�錾
void LoadAllGraph(); //���̃Q�[���Ŏg�p���邷�ׂẲ摜�t�@�C����ǂݍ���


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);            //�E�B���h�E�\�� ��/��
	SetMainWindowText("TUDCC-ShootingGame");
	SetGraphMode(Screen::SCREEN_RESOLUTION_X, Screen::SCREEN_RESOLUTION_Y, 32);  //��ʉ𑜓x, �F�[�x��ݒ�
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	DxLib_Init();                      //DX���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK);     //�`���𗠉�ʂɐݒ�

	LoadAllGraph();


	AppSession app_session;
	//Field field;
	//Deziko deziko;

	while (true) {
		if (ProcessMessage() != 0)break; //�E�B���h�E�̕���{�^��������������while�������[�v�𔲂���

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