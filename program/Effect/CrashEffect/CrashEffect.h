#pragma once
#include "enum.h"
#include "Effect/Effect.h"

class CrashEffect : virtual public Effect{
public:
	CrashEffect(
		double init_pos_x,
		double init_pos_y
	);
	double emit_pos_x;
	double emit_pos_y;
	void update() override;
	void draw() override;
	void EmitPixel();
	void RandomColor();
};