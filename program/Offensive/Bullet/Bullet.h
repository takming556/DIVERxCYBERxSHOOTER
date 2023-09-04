#pragma once
#include "Offensive/Offensive.h"

class Bullet : virtual public Offensive {
protected:
	double arg;						// �i�s����(���W�A���C�E��0)
	double speed;					// �e�̑��x(pixel per second)
	int last_frame_updated_clock;	// �Ō�Ƀt���[�����ύX���ꂽ����
	unsigned int now_frame;
public:
	Bullet(double init_arg, double init_speed);
	Bullet() {}
	void draw_durability() override;
};