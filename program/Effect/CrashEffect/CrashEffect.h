#pragma once
#include "enum.h"
#include "Effect/Effect.h"

class CrashEffect : virtual public Effect{
private:
	double emit_pos_x;
	double emit_pos_y;
	double pixel_pos_x;
	double pixel_pos_y;
	double pixel_emit_arg;
	unsigned int pixel_color;
public:
	CrashEffect(
		double init_pos_x,
		double init_pos_y
	);
	void update() override;
	void draw() override;
	void EmitPixel();
};