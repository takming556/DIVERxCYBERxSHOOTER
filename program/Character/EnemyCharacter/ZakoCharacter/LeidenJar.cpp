#include <numbers>
#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/EnemyCharacter/ZakoCharacter/LeidenJar.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "SoundHandles.h"
#include "DebugParams.h"

using std::make_unique;
using std::numbers::pi;

const double LeidenJar::INIT_SPEED = 400;
const unsigned int LeidenJar::COLLIDANT_SIZE = 10;
const double LeidenJar::INIT_SHOT_SPEED = 200;
const unsigned int LeidenJar::SHOT_COLLIDANT_SIZE = 5;
const unsigned int LeidenJar::SHOT_INTERVAL = 1000;
const unsigned int LeidenJar::INITIAL_HP = 30;
const double LeidenJar::DRAW_ARG_ROTATE_SPEED = 1.0 / 4.0 * pi;

LeidenJar::LeidenJar(double init_pos_x, double init_pos_y, CharacterID given_id) :
	Character(given_id, init_pos_x, init_pos_y, INITIAL_HP, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE)),
	arg(1.0 / 96.0 * pi * DxLib::GetRand(96)),
	speed(INIT_SPEED),
	shot_arg(0.0),
	shot_speed(INIT_SHOT_SPEED),
	shot_collidant_size(SHOT_COLLIDANT_SIZE),
	shot_nozzles(0),
	shot_last_generated_clock(DxLib::GetNowCount()),
	draw_arg(0.0),
	left_wall_last_collided_flag(true),
	right_wall_last_collided_flag(true),
	top_wall_last_collided_flag(true),
	bottom_wall_last_collided_flag(true),
	status(LeidenJarStatus::INITIAL)
{
}

void LeidenJar::reflect_on_rightline() {
	arg = atan(-tan(arg)) + pi;
}


void LeidenJar::reflect_on_leftline() {
	arg = atan(-tan(arg));
}


void LeidenJar::reflect_on_topline() {
	if (cos(arg) > 0) {
		arg = atan(-tan(arg));
	}
	else {
		arg = atan(-tan(arg)) + pi;
	}
}


void LeidenJar::reflect_on_bottomline() {
	if (cos(arg) > 0) {
		arg = atan(-tan(arg));
	}
	else {
		arg = atan(-tan(arg)) + pi;
	}
}



void LeidenJar::update() {
	if ( position->x < InFieldPosition::MIN_MOVABLE_BOUNDARY_X && left_wall_last_collided_flag == false ) {
		reflect_on_leftline();
		left_wall_last_collided_flag = true;
	}
	else if ( position->x > InFieldPosition::MIN_MOVABLE_BOUNDARY_X && left_wall_last_collided_flag == true ) {
		left_wall_last_collided_flag = false;
	}

	if ( position->x > InFieldPosition::MAX_MOVABLE_BOUNDARY_X && right_wall_last_collided_flag == false ) {
		reflect_on_rightline();
		right_wall_last_collided_flag = true;
	}
	else if ( position->x < InFieldPosition::MAX_MOVABLE_BOUNDARY_X && right_wall_last_collided_flag == true ) {
		right_wall_last_collided_flag = false;
	}

	if ( position->y < InFieldPosition::MIN_MOVABLE_BOUNDARY_Y && bottom_wall_last_collided_flag == false ) {
		reflect_on_bottomline();
		bottom_wall_last_collided_flag = true;
	}
	else if ( position->y > InFieldPosition::MIN_MOVABLE_BOUNDARY_Y && bottom_wall_last_collided_flag == true ) {
		bottom_wall_last_collided_flag = false;
	}

	if ( position->y > InFieldPosition::MAX_MOVABLE_BOUNDARY_Y && top_wall_last_collided_flag == false ) {
		reflect_on_topline();
		top_wall_last_collided_flag = true;
	}
	else if ( position->y < InFieldPosition::MAX_MOVABLE_BOUNDARY_Y && top_wall_last_collided_flag == true ) {
		top_wall_last_collided_flag = false;
	}

	switch (status)
	{
	case LeidenJarStatus::INITIAL:
		shot_nozzles = 0;
		break;
	case LeidenJarStatus::FIRST:
		shot_nozzles = 4;
		break;
	case LeidenJarStatus::SECOND:
		shot_nozzles = 8;
		break;
	case LeidenJarStatus::FINAL:
		shot_nozzles = 0;
		break;
	}

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	shot_arg = arg;

	int shot_generated_delta_time = DxLib::GetNowCount() - shot_last_generated_clock;
	if (shot_generated_delta_time > SHOT_INTERVAL && shot_nozzles >= 1) {
		for (int i = 0; i < shot_nozzles; ++i) {
			(*Field::ENEMY_BULLETS)[ Bullet::GENERATE_ID() ] = make_unique<StraightShot>(
										position->x,
										position->y,
										shot_arg,
										shot_speed,
										shot_collidant_size,
										1,
										SkinID::NEON_SP3_JAR_SHOT
			);
			shot_arg += 2.0 * pi / shot_nozzles * 1.0;
		}
		shot_last_generated_clock = DxLib::GetNowCount();
		DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
	}
	draw_arg += DRAW_ARG_ROTATE_SPEED * update_delta_time / 1000 / 1000;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

}


void LeidenJar::draw() {
	Position draw_pos = position->get_draw_position();

	switch ( status )
	{
	case LeidenJarStatus::INITIAL:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -draw_arg, ImageHandles::LEIDENJAR0, TRUE);
		break;
	case LeidenJarStatus::FIRST:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -draw_arg, ImageHandles::LEIDENJAR1, TRUE);
		break;
	case LeidenJarStatus::SECOND:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -draw_arg, ImageHandles::LEIDENJAR2, TRUE);
		break;
	case LeidenJarStatus::FINAL:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -draw_arg, ImageHandles::LEIDENJAR3, TRUE);
		break;
	}

	if ( DebugParams::DEBUG_FLAG == true ) collidant->draw();

}