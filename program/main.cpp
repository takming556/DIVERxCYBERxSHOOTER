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
	DxLib::ChangeWindowMode(TRUE);														//TRUE�ŃE�B���h�E�\���AFALSE�őS��ʕ\��
	DxLib::SetMainWindowText("DIVER x CYBER x SHOOTER");								//�E�B���h�E�̃^�C�g���o�[�ɕ\������閼�O
	DxLib::SetAlwaysRunFlag(TRUE);														//��A�N�e�B�u���ɂ������𑱍s����
	DxLib::SetGraphMode(Screen::SCREEN_RESOLUTION_X, Screen::SCREEN_RESOLUTION_Y, 32);	//��ʉ𑜓x, �F�[�x��ݒ�
	DxLib::SetDrawMode(DX_DRAWMODE_BILINEAR);
	DxLib::SetWaitVSyncFlag(FALSE);														//ScreenFlip()���s���ɐ��������M����ҋ@���Ȃ�
	DxLib::DxLib_Init();																//DX���C�u��������������
	DxLib::SetDrawScreen(DX_SCREEN_BACK);												//�`���𗠉�ʂɐݒ�

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
		if (DxLib::ProcessMessage() != 0) break;	//�E�B���h�E�̕���{�^��������������while�������[�v�𔲂���

		app_session.update();

	}

	DxLib::DxLib_End();
	return 0;
}