#include <string>
#include "DxLib.h"
#include "GameConductor.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "SoundHandles.h"
#include "Colors.h"
#include "FontHandles.h"

using std::wstring;

BossCharacter::BossCharacter(string character_name, unsigned int given_crush_bonus) :
	name(character_name),
	crush_bonus(given_crush_bonus)
{
}


void BossCharacter::funeral() {
	DxLib::PlaySoundMem(SoundHandles::BOSSCRASH, DX_PLAYTYPE_BACK);
	GameConductor::TECHNICAL_SCORE += crush_bonus;
}