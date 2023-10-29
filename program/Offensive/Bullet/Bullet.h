#pragma once
#include <memory>
#include "Offensive/Offensive.h"
#include "CollideRealm/CollideCircle.h"
#include "enum.h"

using std::unique_ptr;
using BulletID = unsigned int;

class Bullet : virtual public Offensive {
protected:
	static BulletID NEXT_ID;
	unsigned int now_frame;
	int durability;
	vector<CharacterID> last_collided_character_ids;
	Bullet(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		int init_durability,
		unsigned int collidant_size
	);
	Bullet();
	bool is_last_collided_with(CharacterID given_character_id);
	void damaged();
public:
	double arg;						// 進行方向(ラジアン，右が0)
	double speed;					// 弾の速度(pixel per second)
	unique_ptr<CollideCircle> collidant;
	unique_ptr<InFieldPosition> position;
	virtual ~Bullet() = default;
	static void INITIALIZE();
	void draw_durability();
	bool is_broken();
	void set_arg(double given_arg);
	void set_speed(double given_speed);
	void add_arg(double given_arg);
	void add_speed(double given_speed);
	void change_skin_id(SkinID alt_skin_id);
	void deal_collision(TeamID given_team_id);
	static BulletID GENERATE_ID();
	//virtual void update() = 0;
};