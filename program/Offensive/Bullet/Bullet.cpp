﻿#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Offensive/Bullet/Bullet.h"
#include "Position/Position.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"

using std::make_unique;


Bullet::Bullet(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	int init_durability
):
	position(make_unique<InFieldPosition>(init_pos_x, init_pos_y)),
	arg(init_arg),
	speed(init_speed),
	durability(init_durability),
	last_frame_updated_clock(0),
	now_frame(0)
{
}


Bullet::Bullet() = default;


void Bullet::draw_durability() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::RED, L"%d", durability);
}


bool Bullet::is_broken() {
	return durability <= 0;
}

void Bullet::damaged() {
	durability += -1;
}


void Bullet::set_arg(double given_arg) {
	arg = given_arg;
}


void Bullet::set_speed(double given_speed) {
	speed = given_speed;
}


void Bullet::deal_collision(TeamID given_team_id) {

	if (given_team_id == TeamID::ENEMY) {
		if (is_last_collided_with(CharacterID::ICHIGO_CHAN) == false
			&& collidant->is_collided_with(Field::MY_CHARACTER->collidant) == true)
		{
			damaged();
		}
		last_collided_character_ids.clear();
		if (collidant->is_collided_with(Field::MY_CHARACTER->collidant) == true) {
			last_collided_character_ids.push_back(CharacterID::ICHIGO_CHAN);
		}
	}

	if (given_team_id == TeamID::MY) {
		for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
			if (is_last_collided_with(enemy_character->id) == false
				&& collidant->is_collided_with(enemy_character->collidant) == true)
			{
				damaged();
			}
		}
		last_collided_character_ids.clear();
		for (const auto& enemy_character : *Field::ENEMY_CHARACTERS) {
			if (collidant->is_collided_with(enemy_character->collidant) == true) {
				last_collided_character_ids.push_back(enemy_character->id);
			}
		}
	}

}


bool Bullet::is_last_collided_with(CharacterID given_character_id) {
	bool found = false;
	for (const auto& last_collided_character_id : last_collided_character_ids) {
		if (last_collided_character_id == given_character_id) found = true;
	}
	return found;
}