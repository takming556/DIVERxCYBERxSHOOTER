#pragma once
#include "enum.h"
#include "Offensive/Bullet/Bullet.h"

class ParabolicShot : public Bullet {
private:
	enum SkinID skin_id;
	const double accel;
	const double accel_arg;
public:
	ParabolicShot(
		double init_pos_x,				// ��1���� �����ʒux
		double init_pos_y,				// ��2���� �����ʒuy
		double init_arg,				// ��3���� �����x�̕Ίp
		double init_speed,				// ��4���� �����x�̑傫��
		double init_accel,				// ��5���� �����x�̑傫��
		double init_accel_arg,			// ��6���� �����x�̕Ίp
		unsigned int collidant_size,	// ��7���� �����蔻��̉~�̔��a
		unsigned int durability,		// ��8���� �e�̑ϋv�l(�ʏ��1���w�肹��)
		enum SkinID given_skin_id		// ��9���� SkinID
	);
	void update() override;
	void draw() override;
};