#include <memory>
#include "DxLib.h"
#include "class.h"
#include "extern.h"

using std::make_unique;

const string BossCharacter1::CHARACTER_NAME("ボス娘（仮）");

BossCharacter1::BossCharacter1() :
	BossCharacter(INITIAL_POS_X, INITIAL_POS_Y, INITIAL_HP, CHARACTER_NAME),
	clock_keeper_for_periodic_emission(0)
{
}


void BossCharacter1::update(vector<unique_ptr<Offensive>>& enemy_offensives) {
	if (DxLib::GetNowCount() > clock_keeper_for_periodic_emission + 1000) {
		StraightRadiation sr(position->x, position->y, 36);
		sr.perform(enemy_offensives);
		clock_keeper_for_periodic_emission = DxLib::GetNowCount();
	}
}


void BossCharacter1::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.4, 0, hPien, TRUE);
}