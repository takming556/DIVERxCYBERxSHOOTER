#include <string>
#include "DxLib.h"
#include "Position/Position.h"
#include "NarrativePop.h"

using std::u8string;

const Position NarrativePop::DRAW_POS = Position(512.0, 600.0);


NarrativePop::NarrativePop(u8string text, u8string speaker_name, PortraitID portrait_id) :
	text(text),
	speaker_name(speaker_name),
	portrait_id(portrait_id),
	state(NarrativePopState::AWAITING)
{
}


void NarrativePop::activate() {
	state = NarrativePopState::ROLLING;
}


void NarrativePop::update() {

}


void NarrativePop::draw() {

}