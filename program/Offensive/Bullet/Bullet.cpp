#include <memory>
#include <utility>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Offensive/Bullet/Bullet.h"
#include "Position/Position.h"
#include "Position/InFieldPosition.h"
#include "CollideRealm/CollideCircle.h"
#include "Colors.h"

using std::make_unique;
using std::move;


BulletID Bullet::NEXT_ID;


Bullet::Bullet(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	int init_durability,
	unsigned int collidant_size
):
	position(make_unique<InFieldPosition>(init_pos_x, init_pos_y)),
	arg(init_arg),
	speed(init_speed),
	collidant(make_unique<CollideCircle>(init_pos_x, init_pos_y, collidant_size)),
	durability(init_durability),
	now_frame(0)
{
}


Bullet::Bullet() = default;


void Bullet::INITIALIZE() {
	NEXT_ID = 0;
}


BulletID Bullet::GENERATE_ID() {
	unsigned int generated_id = NEXT_ID;
	++NEXT_ID;
	return generated_id;
}


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


void Bullet::add_arg(double given_arg) {
	arg += given_arg;
}


void Bullet::add_speed(double given_speed) {
	speed += given_speed;
}


void Bullet::change_skin_id(SkinID alt_skin_id) {
	skin_id = alt_skin_id;
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
		for (const auto& zako_character : *Field::ZAKO_CHARACTERS) {
			if (is_last_collided_with(zako_character->id) == false
				&& collidant->is_collided_with(zako_character->collidant) == true)
			{
				damaged();
			}
		}
		last_collided_character_ids.clear();
		for (const auto& zako_character : *Field::ZAKO_CHARACTERS) {
			if (collidant->is_collided_with(zako_character->collidant) == true) {
				last_collided_character_ids.push_back(zako_character->id);
			}
		}


		for (const auto& boss_character : *Field::BOSS_CHARACTERS) {
			if (is_last_collided_with(boss_character->id) == false
				&& collidant->is_collided_with(boss_character->collidant) == true)
			{
				damaged();
			}
		}
		last_collided_character_ids.clear();
		for (const auto& boss_character : *Field::BOSS_CHARACTERS) {
			if (collidant->is_collided_with(boss_character->collidant) == true) {
				last_collided_character_ids.push_back(boss_character->id);
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