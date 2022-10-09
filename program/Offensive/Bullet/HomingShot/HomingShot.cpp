#include <memory>
#include <cmath>
#include "DxLib.h"
#include "class.h"

using std::make_unique;
using std::floor;		//�����_�ȉ��؂�̂�
using std::ceil;		//�����_�ȉ��؂�グ
using std::atan2;		//�A�[�N�^���W�F���g�i�t���ځj

const double HomingShot::SUSPENSION_TIME = 1.0;

HomingShot::HomingShot(
	double init_x,
	double init_y,
	double init_arg,
	double init_speed,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID given_skin_id
) :
	Bullet(init_x, init_y, init_arg, init_speed),
	Offensive(make_unique<CollideCircle>(init_x, init_y, collidant_size),durability),
	skin_id(given_skin_id),
	last_arg_updated_clock(DxLib::GetNowCount())
{
}


void HomingShot::update() {
	//if (arg < 0) {
	//	arg = arg - (ceil(arg / pi) * pi);
	//}
	//else {
	//	arg = arg - (floor(arg / pi) * pi);
	//}

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
	double delta_x_mychr = my_chr_pos.x - center_pos->x;
	double delta_y_mychr = my_chr_pos.y - center_pos->y;
	double delta_arg_mychr = atan2(delta_y_mychr, delta_x_mychr) - arg;
	arg += delta_arg_mychr;
	//double suspended_delta_arg = delta_arg_mychr * (update_delta_time / (SUSPENSION_TIME * 1000 * 1000));
	//arg += suspended_delta_arg;

	double distance = speed * update_delta_time / 1000 / 1000;
	double delta_x = distance * cos(arg);
	double delta_y = distance * sin(arg);
	center_pos->x += delta_x;
	center_pos->y += delta_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(center_pos);

}


void HomingShot::draw() {
	Position draw_pos = center_pos->get_draw_position();

	if (skin_id == SkinID::ICHIGO_CHAN) {
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, 0, ImageHandles::HEART, TRUE);
	}
	else if (skin_id == SkinID::NORMAL_BLUE) {
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, 0, ImageHandles::BLUE_MARBLE, TRUE);
	}

	double piarg = arg / pi;
	DxLib::DrawFormatString(draw_pos.x + 50, draw_pos.y + 50, Colors::RED, "%lf", piarg);

	collidant->draw();
}