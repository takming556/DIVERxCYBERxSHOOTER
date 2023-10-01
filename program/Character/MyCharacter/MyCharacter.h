#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "enum.h"
#include "Character/Character.h"
#include "Collision.h"

using std::vector;
using std::string;
using std::unordered_map;

class MyCharacter : virtual public Character {
protected:
	string name;
	double shot_frequency;							//連射速度
	double move_speed;								//移動速度(pixel per second)
	int last_launch_ticked_clock;
	vector<unsigned int> last_collided_enemy_bullet_ids;
	//unordered_map<CharacterID, int> last_damaged_clocks;
	vector<Collision> last_collisions_ec;
	//LONGLONG last_updated_clock;
	MyCharacter(string character_name);
	bool is_last_collided_with(unsigned int given_enemy_bullet_id);
	bool is_last_collided_with(CharacterID given_enemy_character_id);
	Collision& get_collision_ec(CharacterID given_enemy_character_id);
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
	void damaged() override;
	//bool is_collided_with_enemy_offensives();
	void deal_collision();
};