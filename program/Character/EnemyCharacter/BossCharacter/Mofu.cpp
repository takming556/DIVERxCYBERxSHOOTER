#include <string>
#include <memory>
#include "DxLib.h"
#include "class.h"
#include "extern.h"

using std::string;
using std::move;
using std::make_unique;

const string Mofu::CHARACTER_NAME("ŠCŒŽ‚à‚Ó");
const int Mofu::INITIAL_POS_X = 310;
const int Mofu::INITIAL_POS_Y = 620;
const unsigned int Mofu::INITIAL_HP = 100;
const unsigned int Mofu::COLLIDANT_SIZE = 60;


Mofu::Mofu() :
	Character(INITIAL_POS_X, INITIAL_POS_Y, make_unique<CollideCircle>(INITIAL_POS_X, INITIAL_POS_Y, COLLIDANT_SIZE)),
	EnemyCharacter(INITIAL_HP),
	BossCharacter(CHARACTER_NAME),
	status(MofuStatus::NORMAL1),
	last_status_updated_clock(DxLib::GetNowCount())
{
}


void Mofu::update() {
	switch (status) {
	case MofuStatus::NORMAL1:
		int normal1_perform_delta_time = DxLib::GetNowCount() - last_normal1_performed_clock;
		if (normal1_perform_delta_time > NORMAL1_INTERVAL) {
			for (int i = 0; i < 20; i++) {
				int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);
				int random_y = DxLib::GetRand();
			}
		}
	}
	//if (DxLib::GetNowCount() > clock_keeper_for_periodic_emission + 1000) {
	//	StraightSimpleRadiation ssr(position->x, position->y, 36, 50, 10, 1, TeamID::ENEMY, SkinID::MOFU);
	//	ssr.perform();
	//	clock_keeper_for_periodic_emission = DxLib::GetNowCount();
	//}
	collidant->update(position);
}


void Mofu::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.4, 0, ImageHandles::PIEN, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}