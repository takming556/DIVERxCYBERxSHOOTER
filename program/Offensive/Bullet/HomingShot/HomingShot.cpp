#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "Offensive/Bullet/HomingShot/HomingShot.h"
#include "ImageHandles.h"
#include "DebugParams.h"
#include "Colors.h"

using std::floor;		//小数点以下切り捨て
using std::ceil;		//小数点以下切り上げ
using std::atan2;		//アークタンジェント（逆正接）
using std::numbers::pi;

HomingShot::HomingShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	double homing_intensity,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID given_skin_id
) :
	Offensive(given_skin_id),
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability, collidant_size),
	//skin_id(given_skin_id),
	last_arg_updated_clock(DxLib::GetNowCount()),
	suspension_time(1.0 / homing_intensity)
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
	double delta_x_mychr = position->x - my_chr_pos.x;
	double delta_y_mychr = position->y - my_chr_pos.y;
	double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
	if (delta_x_mychr > 0) {
		arg_toward_mychr += 0;
	}
	else if (delta_x_mychr < 0 && delta_y_mychr >= 0) {
		arg_toward_mychr = 1.0 / 2.0 * pi - arg_toward_mychr;
	}
	else if (delta_x_mychr < 0 && delta_y_mychr < 0) {
		arg_toward_mychr = -1.0 / 2.0 * pi - arg_toward_mychr;
	}
	double delta_arg_mychr = arg_toward_mychr - arg;
	arg += delta_arg_mychr * update_delta_time / 1000 / 1000 / suspension_time;
	//double suspended_delta_arg = delta_arg_mychr * (update_delta_time / (suspension_time * 1000 * 1000));
	//arg += suspended_delta_arg;

	double distance = speed * update_delta_time / 1000 / 1000;
	double delta_x = distance * cos(arg);
	double delta_y = distance * sin(arg);
	position->x += delta_x;
	position->y += delta_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

}


void HomingShot::draw() {
	Position draw_pos = position->get_draw_position();

	switch (skin_id) {
	//case SkinID::ICHIGO_CHAN:
	//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, -arg, ImageHandles::HEART, TRUE);
	//	break;

	//case SkinID::NORMAL_BLUE:
	//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BLUE_MARBLE, TRUE);
	//	break;

	case SkinID::NEON_SP4_TRAIN:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::ANCHOR_RED, TRUE);
		break;
	}

	
	if (DebugParams::DEBUG_FLAG == true) {
		double piarg = arg / pi;
		DxLib::DrawFormatString(draw_pos.x + 50, draw_pos.y + 50, Colors::RED, L"%lf", piarg);

		collidant->draw();
	}
}