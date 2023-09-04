#pragma once
#include "Offensive/Offensive.h"

class Bullet : virtual public Offensive {
protected:
	double arg;						// 進行方向(ラジアン，右が0)
	double speed;					// 弾の速度(pixel per second)
	int last_frame_updated_clock;	// 最後にフレームが変更された時刻
	unsigned int now_frame;
public:
	Bullet(double init_arg, double init_speed);
	Bullet() {}
	void draw_durability() override;
};