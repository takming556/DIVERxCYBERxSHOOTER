#pragma once
#include <string>
#include "Character/Character.h"

using std::string;

class MyCharacter : virtual public Character {
protected:
	string name;
	double shot_frequency;							//˜AŽË‘¬“x
	double move_speed;								//ˆÚ“®‘¬“x(pixel per second)
	int last_launch_ticked_clock;
	//LONGLONG last_updated_clock;
	MyCharacter(string character_name);
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
	bool is_collided_with_enemy_offensives();
};