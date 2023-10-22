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

InFieldPosition NarrativePop::POS = InFieldPosition(Field::PIXEL_SIZE_X / 2 , 100);
InFieldPosition NarrativePop::PORTRAIT_POS = InFieldPosition(POS.x - 120, POS.y + 200);
InFieldPosition NarrativePop::TEXT_POS = InFieldPosition(POS.x - 290, POS.y + 30);
InFieldPosition NarrativePop::SPEAKER_NAME_POS = InFieldPosition(POS.x - 300, POS.y + 85);
InFieldPosition NarrativePop::AWAITING_INDICATOR_POS = InFieldPosition(POS.x + 280, POS.y - 70);

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


	int portrait_image_handle;
	double draw_extrate;
	switch (portrait_id) {
	case PortraitID::ICHIGO_CHAN_NORMAL:
		portrait_image_handle = ImageHandles::FULLBODY_ICHIGOCHAN_NORMAL;
		draw_extrate = 0.15;
		break;
	case PortraitID::ICHIGO_CHAN_AVATAR:
		portrait_image_handle = ImageHandles::FULLBODY_ICHIGOCHAN_AVATAR;
		draw_extrate = 0.15;
		break;
	case PortraitID::MOFU:
		portrait_image_handle = ImageHandles::FULLBODY_MOFU;
		draw_extrate = 0.15;
		break;
	case PortraitID::NEON:
		portrait_image_handle = ImageHandles::FULLBODY_NEON;
		draw_extrate = 0.15;
		break;
	case PortraitID::TOROI:
		portrait_image_handle = ImageHandles::FULLBODY_TOROI;
		draw_extrate = 0.15;
		break;
	case PortraitID::TEXTFILE:
		portrait_image_handle = ImageHandles::TEXT_FILE;
		draw_extrate = 1.0;
	}

	DxLib::DrawRotaGraph(
		PORTRAIT_POS.get_draw_position().x,
		PORTRAIT_POS.get_draw_position().y,
		draw_extrate,
		0,
		portrait_image_handle,
		TRUE
	);

	DxLib::DrawRotaGraph(
		POS.get_draw_position().x,
		POS.get_draw_position().y,
		1.0,
		0.0,
		ImageHandles::NARRATIVE_POP,
		TRUE
	);

	DxLib::DrawFormatStringToHandle(
		TEXT_POS.get_draw_position().x,
		TEXT_POS.get_draw_position().y,
		Colors::BLACK,
		FontHandles::NARRATIVE_POP_TEXT,
		displaying_text.c_str()
	);

	DxLib::DrawFormatStringToHandle(
		SPEAKER_NAME_POS.get_draw_position().x,
		SPEAKER_NAME_POS.get_draw_position().y,
		Colors::BLACK,
		FontHandles::NARRATIVE_POP_TEXT,
		speaker_name.c_str()
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
			indicator_image_handle = ImageHandles::GHOST_AQUA_FRONT;
			break;

		case PortraitID::TOROI:
			indicator_image_handle = ImageHandles::GHOST_GRAY_FRONT;
			break;
		}

		if (awaiting_indicator_lighting_flag == true) {
			DxLib::DrawRotaGraph(
				AWAITING_INDICATOR_POS.get_draw_position().x,
				AWAITING_INDICATOR_POS.get_draw_position().y,
				0.8,
				1.0 / 2.0 * pi,
				indicator_image_handle,
				TRUE
			);
		}

	}

}