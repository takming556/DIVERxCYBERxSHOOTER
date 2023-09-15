#pragma once
#include <memory>
#include "Offensive/Offensive.h"
#include "CollideRealm/CollideRealm.h"

using std::unique_ptr;

class Bullet : virtual public Offensive {
protected:
	int last_frame_updated_clock;	// 最後にフレームが変更された時刻
	unsigned int now_frame;
	int durability;
public:
	double arg;						// 進行方向(ラジアン，右が0)
	double speed;					// 弾の速度(pixel per second)

	unique_ptr<InFieldPosition> position;
	Bullet(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double init_speed,
		int init_durability
	);
	Bullet();
	void draw_durability();
	bool is_broken() override;
	void damaged();
	void set_arg(double given_arg);
	void set_speed(double given_speed);
};