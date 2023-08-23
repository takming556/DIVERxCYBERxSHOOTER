#pragma once
#include "Offensive/Bullet/StraightShot/StraightShot.h"


class TurnShot : public StraightShot {
private:
	bool already_turned_flag;
	int generated_clock;
	const unsigned int TURN_POSTPONE_TIME;
	const double ADD_ARG;
public:
	TurnShot(
		double init_pos_x,					// �����ʒuX���W
		double init_pos_y,					// �����ʒuY���W
		double init_arg,					// �����Ίp[���W�A��]
		double init_speed,					// �����x[�s�N�Z��/�b]
		unsigned int turn_postpone_time,	// ��������܂�Ȃ���܂ł̎���[�~���b]
		double add_arg,						// �܂�Ȃ���̒ǉ��p�x[���W�A��]
		unsigned int collidant_size,		// �����蔻��̑傫��
		unsigned int durability,			// �e�̑ϋv�l(HP)�ӂ���1���w�肹��
		enum SkinID given_skin_id			// �X�L��ID
	);
	void update() override;

};