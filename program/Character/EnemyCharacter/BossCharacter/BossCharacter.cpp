#include <string>
#include "DxLib.h"
#include "GameConductor.h"
#include "Character/EnemyCharacter/BossCharacter/BossCharacter.h"
#include "Character/EnemyCharacter/BossCharacter/Mofu.h"
#include "SoundHandles.h"
#include "ImageHandles.h"

using std::wstring;

BossCharacter::BossCharacter(wstring character_name, unsigned int given_initial_hp, unsigned int given_crush_bonus) :
	name(character_name),
	initial_hp(given_initial_hp),
	crush_bonus(given_crush_bonus)
{
}


void BossCharacter::funeral() {
	DxLib::PlaySoundMem(SoundHandles::BOSSCRASH, DX_PLAYTYPE_BACK);
	GameConductor::TECHNICAL_SCORE += crush_bonus;
}

void BossCharacter::HPDonut() {
	Position draw_position = position->get_draw_position();
	DrawCircleGauge(		// 円グラフ的な描画を行う
		draw_position.x, 
		draw_position.y,
		(double)hp / initial_hp * 100,
		ImageHandles::HP_DONUT
	);
}