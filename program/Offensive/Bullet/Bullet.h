#pragma once
#include <memory>
#include "Offensive/Offensive.h"
#include "CollideRealm/CollideRealm.h"

using std::unique_ptr;

class Bullet : virtual public Offensive {
protected:
	double arg;						// �i�s����(���W�A���C�E��0)
	double speed;					// �e�̑��x(pixel per second)
	int last_frame_updated_clock;	// �Ō�Ƀt���[�����ύX���ꂽ����
	unsigned int now_frame;
public:
	unique_ptr<InFieldPosition> position;
	Bullet(double init_pos_x, double init_pos_y, double init_arg, double init_speed);
	Bullet() {}
};