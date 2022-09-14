#include "DxLib.h"
#include "class.h"
#include "extern.h"


//�v���g�^�C�v�錾
void LoadAllGraph();	//���̃Q�[���Ŏg�p���邷�ׂẲ摜�t�@�C����ǂݍ���


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	DxLib::ChangeWindowMode(TRUE);														//�E�B���h�E�\�� ��/��
	DxLib::SetMainWindowText("TUDCC-ShootingGame");
	DxLib::SetAlwaysRunFlag(TRUE);														//��A�N�e�B�u���ɂ������𑱍s����
	DxLib::SetGraphMode(Screen::SCREEN_RESOLUTION_X, Screen::SCREEN_RESOLUTION_Y, 32);	//��ʉ𑜓x, �F�[�x��ݒ�
	DxLib::SetDrawMode(DX_DRAWMODE_BILINEAR);
	DxLib::SetWaitVSyncFlag(FALSE);														//ScreenFlip()���s���ɐ��������M����ҋ@���Ȃ�
	DxLib::DxLib_Init();																//DX���C�u��������������
	DxLib::SetDrawScreen(DX_SCREEN_BACK);												//�`���𗠉�ʂɐݒ�

	LoadAllGraph();


	AppSession app_session;
	//Field field;
	//Deziko deziko;

	while (true) {
		if (DxLib::ProcessMessage() != 0)break;	//�E�B���h�E�̕���{�^��������������while�������[�v�𔲂���

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