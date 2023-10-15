#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "CollideRealm/CollideCircle.h"
#include "Character/EnemyCharacter/ZakoCharacter/ZkChrStg2BsNm4.h"
#include "ImageHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const unsigned int ZkChrStg2BsNm4::INITIAL_HP = 20;
const unsigned int ZkChrStg2BsNm4::COLLIDANT_SIZE = 15;

const double ZkChrStg2BsNm4::DRAW_EXTRATE = 0.05;

bool ZkChrStg2BsNm4::ESCAPE_FLAG = false;

ZkChrStg2BsNm4::ZkChrStg2BsNm4(
	CharacterID given_id,
	double boss_pos_x,
	double boss_pos_y
) :
	Character(
		given_id,
		boss_pos_x,
		boss_pos_y,
		INITIAL_HP,
		make_unique<CollideCircle>(boss_pos_x, boss_pos_y, COLLIDANT_SIZE)
	),
	pos_x(boss_pos_x),
	pos_y(boss_pos_y),
	random_arg(3.0 / 2.0 * pi),
	random_speed(100),
	random_interval(1000),
	kept_clock(DxLib::GetNowCount()),
	last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
	position->x = pos_x;
	position->y = pos_y;
}

void ZkChrStg2BsNm4::update() {
	int random_judgement_clock = DxLib::GetNowCount() - kept_clock;
	bool in_field = position->x > InFieldPosition::MIN_MOVABLE_BOUNDARY_X 
					&& position->x < InFieldPosition::MAX_MOVABLE_BOUNDARY_X
					&& position->y > InFieldPosition::MIN_MOVABLE_BOUNDARY_Y
					&& position->y < InFieldPosition::MAX_MOVABLE_BOUNDARY_Y;
	
	if (random_judgement_clock > random_interval || in_field == false) {
		int random_arg_num = DxLib::GetRand(360);
		int random_speed_num = DxLib::GetRand(6);
		int random_interval_num = DxLib::GetRand(30);
		random_arg = 1.0 / 180.0 * random_arg_num * pi;
		random_speed = 100 + 50 * random_speed_num;
		random_interval = 100 * random_interval_num;

		if (ESCAPE_FLAG == true) {
			int in_field_quadrant = 1;
			if (position->x > Field::PIXEL_SIZE_X / 2 && position->y > Field::PIXEL_SIZE_Y / 2) {
				in_field_quadrant = 1;
			}
			if (position->x < Field::PIXEL_SIZE_X / 2 && position->y > Field::PIXEL_SIZE_Y / 2) {
				in_field_quadrant = 2;
			}
			if (position->x < Field::PIXEL_SIZE_X / 2 && position->y < Field::PIXEL_SIZE_Y / 2) {
				in_field_quadrant = 3;
			}
			if (position->x > Field::PIXEL_SIZE_X / 2 && position->y < Field::PIXEL_SIZE_Y / 2) {
				in_field_quadrant = 4;
			}
			int random_arg_num = DxLib::GetRand(90);
			int random_speed_num = DxLib::GetRand(6);
			random_arg = 1.0 / 180.0 * random_arg_num * pi + 1.0 / 2.0 * (in_field_quadrant - 1) * pi;
		}
		kept_clock = DxLib::GetNowCount();
	}

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = random_speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(random_arg);
	double distance_y = distance * sin(random_arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}

void ZkChrStg2BsNm4::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, DRAW_EXTRATE, 0, ImageHandles::SPRITE_ZKCHR_LIGHT_ELE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}