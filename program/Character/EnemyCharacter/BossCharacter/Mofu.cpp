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
const unsigned int Mofu::INITIAL_HP = 1000;
const unsigned int Mofu::COLLIDANT_SIZE = 60;
const double Mofu::DRAW_EXTRATE = 0.07;

const unsigned int Mofu::NORMAL1_AMOUNT = 15;
const unsigned int Mofu::NORMAL1_INTERVAL = 1000;
const unsigned int Mofu::NORMAL1_SCATTERING_Y = 100;
const double Mofu::NORMAL1_SHOT_SPEED = 200;
const unsigned int Mofu::NORMAL1_SHOT_COLLIDANT_SIZE = 20;
const unsigned int Mofu::NORMAL1_SHOT_DURABILITY = 1;

const unsigned int Mofu::SP1_AMOUNT = 20;
const unsigned int Mofu::SP1_INTERVAL = 2000;
const unsigned int Mofu::SP1_SCATTERING_Y = 30;


Mofu::Mofu() :
	Character(INITIAL_POS_X, INITIAL_POS_Y, make_unique<CollideCircle>(INITIAL_POS_X, INITIAL_POS_Y, COLLIDANT_SIZE)),
	EnemyCharacter(INITIAL_HP),
	BossCharacter(CHARACTER_NAME),
	status(MofuStatus::NORMAL1),
	last_status_changed_clock(DxLib::GetNowCount()),
	last_normal1_performed_clock(0),
	last_sp1_performed_clock(0)
{
}


void Mofu::update() {
	switch (status) {
	case MofuStatus::NORMAL1:
	{
		int delta_time_status_changed = DxLib::GetNowCount() - last_status_changed_clock;
		if (delta_time_status_changed < 20000) {
			int normal1_perform_delta_time = DxLib::GetNowCount() - last_normal1_performed_clock;
			if (normal1_perform_delta_time > NORMAL1_INTERVAL) {
				for (int i = 0; i < NORMAL1_AMOUNT; i++) {
					int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);
					int random_y = DxLib::GetRand(NORMAL1_SCATTERING_Y) + 600;
					Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(
						random_x,
						random_y,
						-(1.0 / 2.0) * pi,
						NORMAL1_SHOT_SPEED,
						NORMAL1_SHOT_COLLIDANT_SIZE,
						NORMAL1_SHOT_DURABILITY,
						SkinID::NORMAL_BLUE
						)
					);
				}
				last_normal1_performed_clock = DxLib::GetNowCount();
			}
		}
		else {
			status = MofuStatus::SP1;
			last_status_changed_clock = DxLib::GetNowCount();
		}
		break;
	}

	case MofuStatus::SP1:
		int sp1_perform_delta_time = DxLib::GetNowCount() - last_sp1_performed_clock;
		if (sp1_perform_delta_time > SP1_INTERVAL) {
			for (int i = 0; i < SP1_AMOUNT; i++) {
				int random_x = DxLib::GetRand(Field::PIXEL_SIZE_X);
				int random_y = DxLib::GetRand(SP1_SCATTERING_Y) - SP1_SCATTERING_Y;
				Field::ENEMY_OFFENSIVES->push_back(make_unique<FloatingTerrorShot>(random_x, random_y));
				last_sp1_performed_clock = DxLib::GetNowCount();
			}
		}
		break;
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
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_MOFU, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}