#include "DxLib.h"
#include "SoundHandles.h"

int SoundHandles::CURSORMOVE;
int SoundHandles::FORWARD;
int SoundHandles::BACKWARD;
int SoundHandles::MYSHOT;
int SoundHandles::ENEMYSHOT;
int SoundHandles::MYHIT;
int SoundHandles::ENEMYHIT;
// int SoundHandles::MYCRASH;
int SoundHandles::ZAKOCRASH;
int SoundHandles::BOSSCRASH;

int SoundHandles::STAGE1BGM;
int SoundHandles::STAGE2BGM;
int SoundHandles::STAGE3BGM;


void SoundHandles::LOAD_ALL_SOUNDS() {
	CURSORMOVE = DxLib::LoadSoundMem(L"sound/CursorMove2.mp3");
	FORWARD = DxLib::LoadSoundMem(L"sound/Forward2.mp3");
	BACKWARD = DxLib::LoadSoundMem(L"sound/Backward1.mp3");
	MYSHOT = DxLib::LoadSoundMem(L"sound/MyShot2.mp3");
	ENEMYSHOT = DxLib::LoadSoundMem(L"sound/EnemyShot3.mp3");
	MYHIT = DxLib::LoadSoundMem(L"sound/MyHit4.mp3");
	ENEMYHIT = DxLib::LoadSoundMem(L"sound/EnemyHit1.mp3");
	// MYCRASH = DxLib::LoadSoundMem(L"sound/MyCrash1.mp3");
	ZAKOCRASH = DxLib::LoadSoundMem(L"sound/ZakoCrash5.mp3");
	BOSSCRASH = DxLib::LoadSoundMem(L"sound/BossCrash3.mp3");

	STAGE1BGM = DxLib::LoadSoundMem(L"bgm/JellyCarnival0329.mp3");
	STAGE2BGM = DxLib::LoadSoundMem(L"bgm/gamic.mp3");
	STAGE3BGM = DxLib::LoadSoundMem(L"bgm/My_Song_6.mp3");
}