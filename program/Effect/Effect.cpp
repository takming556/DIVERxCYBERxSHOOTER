#include "DxLib.h"
#include "Field.h"
#include "Effect.h"

EffectID Effect::NEXT_ID;

Effect::Effect(
	double init_emit_pos_x,
	double init_emit_pos_y
)
{
}


void Effect::INITIALIZE() {
	NEXT_ID = 0;
}


EffectID Effect::GENERATE_ID() {
	unsigned int generated_id = NEXT_ID;
	++NEXT_ID;
	return generated_id;
}