#include "DxLib.h"
#include "class.h"

int SoundHandles::CURSORMOVE;
int SoundHandles::FORWARD;
int SoundHandles::BACKWARD;
int SoundHandles::MYSHOT;
int SoundHandles::ENEMYSHOT;
int SoundHandles::MYHIT;
int SoundHandles::ENEMYHIT;
int SoundHandles::ZAKOCRASH;
int SoundHandles::BOSSCRASH;

int SoundHandles::STAGE1BGM;


void SoundHandles::LOAD_ALL_SOUNDS() {
	CURSORMOVE = DxLib::LoadSoundMem("sound/CursorMove2.mp3");
	FORWARD = DxLib::LoadSoundMem("sound/Forward2.mp3");
	BACKWARD = DxLib::LoadSoundMem("sound/Backward1.mp3");
	MYSHOT = DxLib::LoadSoundMem("sound/MyShot2.mp3");
	ENEMYSHOT = DxLib::LoadSoundMem("sound/EnemyShot3.mp3");
	MYHIT = DxLib::LoadSoundMem("sound/MyHit4.mp3");
	ENEMYHIT = DxLib::LoadSoundMem("sound/EnemyHit1.mp3");
	ZAKOCRASH = DxLib::LoadSoundMem("sound/ZakoCrash5.mp3");
	BOSSCRASH = DxLib::LoadSoundMem("sound/BossCrash3.mp3");

	STAGE1BGM = DxLib::LoadSoundMem("bgm/JellyCarnival0329.mp3");
}