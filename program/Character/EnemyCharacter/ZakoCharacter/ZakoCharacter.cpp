#include "DxLib.h"
#include "GameConductor.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZakoCharacter.h"
#include "SoundHandles.h"

const unsigned int ZakoCharacter::CRUSH_BONUS = 10000;


void ZakoCharacter::funeral() {
	DxLib::PlaySoundMem(SoundHandles::ZAKOCRASH, DX_PLAYTYPE_BACK);
	GameConductor::TECHNICAL_SCORE += ZakoCharacter::CRUSH_BONUS;
}