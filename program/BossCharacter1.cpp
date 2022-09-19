#include <string>
#include <memory>
#include "DxLib.h"
#include "class.h"
#include "extern.h"

using std::string;
using std::move;
using std::make_unique;

const string BossCharacter1::CHARACTER_NAME("ボス娘（仮）");

BossCharacter1::BossCharacter1() :
	Character(INITIAL_POS_X, INITIAL_POS_Y, make_unique<CollideCircle>(INITIAL_POS_X, INITIAL_POS_Y, COLLIDANT_SIZE)),
	EnemyCharacter(INITIAL_HP),
	BossCharacter(CHARACTER_NAME),
	clock_keeper_for_periodic_emission(0)
{
}


void BossCharacter1::update(list<unique_ptr<Offensive>>& enemy_offensives) {
	if (DxLib::GetNowCount() > clock_keeper_for_periodic_emission + 1000) {
		StraightRadiation sr(position->x, position->y, 36);
		sr.perform(enemy_offensives);
		clock_keeper_for_periodic_emission = DxLib::GetNowCount();
	}
	collidant->update(position);
}


void BossCharacter1::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.4, 0, hPien, TRUE);
	collidant->draw();
}