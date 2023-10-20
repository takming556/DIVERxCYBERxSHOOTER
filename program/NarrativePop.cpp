#include <string>
#include <numbers>
#include <utility>
#include "DxLib.h"
#include "Position/InFieldPosition.h"
#include "NarrativePop.h"
#include "Field.h"
#include "ImageHandles.h"
#include "Colors.h"
#include "FontHandles.h"

using std::wstring;
using std::numbers::pi;

const InFieldPosition NarrativePop::POS = InFieldPosition(Field::PIXEL_SIZE_X / 2 , 150.0);
const double NarrativePop::TEXT_ROLL_SPEED = 10.0;	// テキストの流転速度[文字/秒]
const unsigned int NarrativePop::AWAITING_INDICATOR_BLINK_WAIT = 250;


NarrativePop::NarrativePop(tuple<wstring, wstring, PortraitID> given_narration) :
	text(std::get<0>(given_narration)),
	speaker_name(std::get<1>(given_narration)),
	portrait_id(std::get<2>(given_narration)),
	state(NarrativePopState::READY),
	display_letter_count(0),
	activated_clock(0),
	awaiting_indicator_lighting_flag(false),
	awaiting_indicator_last_blinked_clock(0)
{
}


void NarrativePop::activate() {
	state = NarrativePopState::ROLLING;
	activated_clock = DxLib::GetNowCount();
}



void NarrativePop::update() {
	switch (state) {
	case NarrativePopState::READY:
		display_letter_count = 0;
		break;

	default:
		display_letter_count = (double)(DxLib::GetNowCount() - activated_clock) / 1000 * TEXT_ROLL_SPEED;
		break;

	}
	
	displaying_text = text.substr(0, display_letter_count);

	if (state == NarrativePopState::ROLLING) {
		if (display_letter_count >= text.length()) {
			state = NarrativePopState::AWAITING;
		}
	}

	if (state == NarrativePopState::AWAITING) {
		int elapsed_time_since_awaiting_indicator_last_blinked = DxLib::GetNowCount() - awaiting_indicator_last_blinked_clock;
		if (elapsed_time_since_awaiting_indicator_last_blinked > AWAITING_INDICATOR_BLINK_WAIT) {
			awaiting_indicator_lighting_flag = !awaiting_indicator_lighting_flag;
			awaiting_indicator_last_blinked_clock = DxLib::GetNowCount();
		}
	}

}



void NarrativePop::draw() {

	InFieldPosition portrait_draw_pos(POS.x - 150, POS.y + 200);

	int portrait_image_handle;
	switch (portrait_id) {
	case PortraitID::ICHIGO_CHAN_NORMAL:
		portrait_image_handle = ImageHandles::FULLBODY_ICHIGOCHAN_NORMAL;
		break;
	case PortraitID::ICHIGO_CHAN_AVATAR:
		portrait_image_handle = ImageHandles::FULLBODY_ICHIGOCHAN_AVATAR;
		break;
	case PortraitID::MOFU:
		portrait_image_handle = ImageHandles::FULLBODY_MOFU;
		break;
	case PortraitID::NEON:
		portrait_image_handle = ImageHandles::FULLBODY_NEON;
		break;
	case PortraitID::TOROI:
		portrait_image_handle = ImageHandles::FULLBODY_TOROI;
		break;
	}

	DxLib::DrawRotaGraph(
		portrait_draw_pos.get_draw_position().x,
		portrait_draw_pos.get_draw_position().y,
		0.15,
		0,
		portrait_image_handle,
		TRUE
	);

	Position draw_pos = InFieldPosition::GET_DRAW_POSITION(POS.x, POS.y);
	DxLib::DrawRotaGraph(
		draw_pos.x,
		draw_pos.y,
		1.0,
		0.0,
		ImageHandles::NARRATIVE_POP,
		TRUE
	);

	DxLib::DrawFormatStringToHandle(
		10,
		600,
		Colors::BLACK,
		FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32,
		displaying_text.c_str()
	);

	if (state == NarrativePopState::AWAITING) {

		int indicator_image_handle;
		switch (portrait_id) {
		case PortraitID::ICHIGO_CHAN_NORMAL:
			indicator_image_handle = ImageHandles::STRAWBERRY_FUCHSIA;
			break;

		case PortraitID::ICHIGO_CHAN_AVATAR:
			indicator_image_handle = ImageHandles::STRAWBERRY_RED;
			break;

		case PortraitID::MOFU:
			indicator_image_handle = ImageHandles::GHOST_YELLOW_FRONT;
			break;

		case PortraitID::NEON:
			indicator_image_handle = ImageHandles::ANCHOR_AQUA;
			break;

		case PortraitID::TOROI:
			indicator_image_handle = ImageHandles::GHOST_BLUE_FRONT;
			break;
		}

		if (awaiting_indicator_lighting_flag == true) {
			DxLib::DrawRotaGraph(
				InFieldPosition(600, 20).get_draw_position().x,
				InFieldPosition(600, 20).get_draw_position().y,
				0.8,
				1.0 / 2.0 * pi,
				indicator_image_handle,
				TRUE
			);
		}

	}

}