﻿#pragma once
#include <string>
#include <vector>
#include "enum.h"
#include "Character/Character.h"
#include "Collision.h"

using std::vector;
using std::wstring;
using BulletID = unsigned int;
using LaserID = unsigned int;

class MyCharacter : virtual public Character {
protected:
	wstring name;
	double shot_frequency;							//連射速度
	double move_speed;								//移動速度(pixel per second)
	int last_launch_ticked_clock;
	vector<Collision<BulletID>> last_collisions_with_enemy_bullet;
	vector<Collision<CharacterID>> last_collisions_with_zako_character;
	vector<Collision<CharacterID>> last_collisions_with_boss_character;
	vector<Collision<LaserID>> last_collisions_with_enemy_laser;
	MyCharacter(wstring character_name);
	bool is_last_collided_with_bullet(BulletID given_enemy_bullet_id);
	bool is_last_collided_with_laser(LaserID given_enemy_laser_id);
	bool is_last_collided_with_character(CharacterID given_enemy_character_id);
	Collision<CharacterID>& get_last_collision(CharacterID given_enemy_character_id);
	Collision<LaserID>& get_last_collision(LaserID given_enemy_laser_id);

	static const int INITIAL_POSITION_X;
	static const int INITIAL_POSITION_Y;
	static const int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double SLOW_MOVE_SPEED_EXTRATE;
public:
	static bool SLOWMOVE_FLAG;
	virtual ~MyCharacter() {}
	void update();
	void respond_to_keyinput();
	void move_upward();
	void move_downward();
	void move_rightward();
	void move_leftward();
	void move_uprightward();
	void move_downrightward();
	void move_upleftward();
	void move_downleftward();
	void regulate_position();
	void launch();
	virtual void damaged() override;
	void deal_collision();
};