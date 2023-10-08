#include <string>
#include "DxLib.h"
#include "Position/Position.h"
#include "NarrativePop.h"

using std::wstring;

const Position NarrativePop::DRAW_POS = Position(512.0, 600.0);


NarrativePop::NarrativePop(wstring text, wstring speaker_name, PortraitID portrait_id) :
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