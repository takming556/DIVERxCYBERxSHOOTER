#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Character/EnemyCharacter/BossCharacter/Toroi.h"
#include "Offensive/Bullet/StraightShot/StraightShot.h"
#include "ImageHandles.h"
#include "DebugParams.h"

using std::sin;
using std::cos;
using std::numbers::pi;


StraightShot::StraightShot(
	double init_pos_x,
	double init_pos_y,
	double init_arg,
	double init_speed,
	unsigned int collidant_size,
	unsigned int durability,
	enum SkinID given_skin_id
) :
	Offensive(given_skin_id),
	Bullet(init_pos_x, init_pos_y, init_arg, init_speed, durability, collidant_size)
{
}


void StraightShot::update() {

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}


void StraightShot::draw() {
	int delta_time_frame_update = DxLib::GetNowCount() - last_frame_updated_clock;
	Position draw_pos = position->get_draw_position();

	switch (skin_id) {
	case SkinID::ICHIGO_CHAN:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::STRAWBERRY_RED, TRUE);
		break;

	case SkinID::NORMAL_BLUE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BLUE_MARBLE, TRUE);
		break;

	case SkinID::TERROR:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::ANCHOR_RED, TRUE);
		break;

	case SkinID::BUBBLE_GENERIC:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_AQUA, TRUE);
		break;
	case SkinID::STG3_WAVE1_R:
		DxLib::DrawRotaGraph(draw_pos.x,draw_pos.y,0.75,-arg,ImageHandles::BUBBLE_BLACK,TRUE);
		break;

	case SkinID::STG3_WAVE1_L:
		DxLib::DrawRotaGraph(draw_pos.x,draw_pos.y,0.75,-arg,ImageHandles::BUBBLE_BLACK,TRUE);
		break;

	case SkinID::STG2_WAVE5_L:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::ANCHOR_NAVY, TRUE);
		break;

	case SkinID::STG2_WAVE5_R:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::ANCHOR_YELLOW, TRUE);
		break;

	case SkinID::STG2_WAVE6_L:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::POTATO_RED, TRUE);
		break;

	case SkinID::STG2_WAVE6_R:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_BLUE, TRUE);
		break;

	case SkinID::STG2_WAVE7_L:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::CRYSTAL_YELLOW, TRUE);
		break;

	case SkinID::STG2_WAVE7_R:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::CRYSTAL_PURPLE, TRUE);
		break;

	case SkinID::STG2_WAVE8_L:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, 1.0 / 2.0 * pi, ImageHandles::GHOST_YELLOW.at(now_frame), TRUE);
		if (delta_time_frame_update > 200) {
			if (now_frame >= ImageHandles::GHOST_YELLOW.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}		
		break;

	case SkinID::STG2_WAVE8_R:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, 1.0 / 2.0 * pi, ImageHandles::GHOST_BLUE.at(now_frame), TRUE);
		if (delta_time_frame_update > 200) {
			if (now_frame >= ImageHandles::GHOST_BLUE.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}
		break;

	case SkinID::NEON_NM2_STRAIGHT:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.50, -arg, ImageHandles::OVAL_AQUA, TRUE);
		break;

	case SkinID::NEON_NM3_RED:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_RED, TRUE);
		break;

	case SkinID::NEON_NM3_ORANGE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_ORANGE, TRUE);
		break;

	case SkinID::NEON_NM3_YELLOW:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_YELLOW, TRUE);
		break;

	case SkinID::NEON_NM3_GREEN:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_GREEN, TRUE);
		break;

	case SkinID::NEON_NM3_TEAL:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_TEAL, TRUE);
		break;

	case SkinID::NEON_NM3_AQUA:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_AQUA, TRUE);
		break;

	case SkinID::NEON_NM3_BLUE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_BLUE, TRUE);
		break;

	case SkinID::NEON_NM3_PURPLE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_PURPLE, TRUE);
		break;

	case SkinID::NEON_NM3_FUCHSIA:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_FUCHSIA, TRUE);
		break;

	case SkinID::NEON_NM4_CRYSTAL_RED:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::CRYSTAL_RED, TRUE);
		break;

	case SkinID::NEON_NM4_CRYSTAL_BLUE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::CRYSTAL_BLUE, TRUE);
		break;

	case SkinID::NEON_SP4_SHUFFLE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.50, -arg, ImageHandles::CIRCLE_BLUE, TRUE);
		break;

	case SkinID::NEON_SP4_TRAIN:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::ANCHOR_RED, TRUE);
		break;

	case SkinID::STG3_WAVE2_R:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_BLACK, TRUE);
		break;

	case SkinID::STG3_WAVE2_L:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_BLACK, TRUE);
		break;

	case SkinID::STG3_WAVE3_C:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_BLUE, TRUE);
		break;

	case SkinID::STG3_WAVE3_LR:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_GREEN, TRUE);
		break;

	case SkinID::STG3_WAVE4_LR:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::BUBBLE_BLACK, TRUE);
		break;

	case SkinID::STG3_WAVE4_C_PORTAL:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::CIRCLE_GRAY, TRUE);
		break;

	case SkinID::STG3_WAVE5_T:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.40, -arg, ImageHandles::OVAL_SILVER, TRUE);
		break;

	case SkinID::STG3_WAVE5_B:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_GRAY, TRUE);
		break;

	case SkinID::STG3_WAVE6_C_ANCHOR:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::ANCHOR_MAROON, TRUE);
		break;

	case SkinID::STG3_WAVE6_LR_GHOST:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::GHOST_GRAY.at(now_frame), TRUE);
		if (delta_time_frame_update > 200) {
			if (now_frame >= ImageHandles::GHOST_GRAY.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}
		break;

	case SkinID::TOROI_NM3_DECOY:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_ORANGE, TRUE);
		break;
	
	case SkinID::TOROI_NM3_COY:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, -arg, ImageHandles::OVAL_GRAY, TRUE);
		break;

	case SkinID::TOROI_NM4_RED_BIG:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, 1.0 / 2.0 * pi, ImageHandles::GHOST_RED.at(now_frame), TRUE);
		if (delta_time_frame_update > 200) {
			if (now_frame >= ImageHandles::GHOST_RED.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}
		break;

	case SkinID::TOROI_NM4_RED_SMALL:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, 1.0 / 2.0 * pi, ImageHandles::GHOST_RED.at(now_frame), TRUE);
		if (delta_time_frame_update > 200) {
			if (now_frame >= ImageHandles::GHOST_RED.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}
		break;

	case SkinID::TOROI_NM4_BLUE_BIG:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, 1.0 / 2.0 * pi, ImageHandles::GHOST_BLUE.at(now_frame), TRUE);
		if (delta_time_frame_update > 200) {
			if (now_frame >= ImageHandles::GHOST_BLUE.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}
		break;

	case SkinID::TOROI_NM4_BLUE_SMALL:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.75, 1.0 / 2.0 * pi, ImageHandles::GHOST_BLUE.at(now_frame), TRUE);
		if (delta_time_frame_update > 200) {
			if (now_frame >= ImageHandles::GHOST_BLUE.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}
		break;

	case SkinID::TOROI_SP1_TRAP:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_FUCHSIA, TRUE);
		break;

	case SkinID::TOROI_SP3_GHOST:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, 1.0 / 2.0 * pi, ImageHandles::GHOST_BLUE.at(now_frame), TRUE);
		if (delta_time_frame_update > Toroi::SP3_GHOST_FRAMING_INTERVAL) {
			if (now_frame >= ImageHandles::GHOST_BLUE.size() - 1) {
				now_frame = 0;
			}
			else {
				++now_frame;
			}
			last_frame_updated_clock = DxLib::GetNowCount();
		}
		break;

	case SkinID::TOROI_SP3_BLOOD_SPLASH:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.5, -arg, ImageHandles::POTATO_RED, TRUE);
		break;

	case SkinID::TOROI_SP5_RAIN_SOU:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::POTATO_FUCHSIA, TRUE);
		break;

	case SkinID::TOROI_SP5_RAIN_UTU:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::POTATO_AQUA, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_RED:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_RED, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_ORANGE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_ORANGE, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_YELLOW:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_YELLOW, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_GREEN:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_GREEN, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_TEAL:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_TEAL, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_AQUA:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_AQUA, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_BLUE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_BLUE, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_PURPLE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_PURPLE, TRUE);
		break;

	case SkinID::TOROI_SP5_HEART_FUCHSIA:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::HEART_FUCHSIA, TRUE);
		break;
	
	case SkinID::TOROI_SP6_RAN_A_CHEESE:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.5, -arg, ImageHandles::BUBBLE_YELLOW, TRUE);
		break;

	case SkinID::TOROI_SP6_RAN_B_LETUS:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.5, -arg, ImageHandles::BUBBLE_LIME, TRUE);
		break;

	case SkinID::TOROI_SP6_RU_POTATO:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::POTATO_BASIC, TRUE);
		break;

	case SkinID::TOROI_SP6_RU_TOMATO:
		DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BUBBLE_RED, TRUE);
		break;

	}

	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}