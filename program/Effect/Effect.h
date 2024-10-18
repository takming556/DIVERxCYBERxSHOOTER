#pragma once

using EffectID = unsigned int;

class Effect {
protected:
	static EffectID NEXT_ID;
public:
	Effect(
		double init_pos_x,
		double init_pos_y
	);
	static void INITIALIZE();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual ~Effect() = default;
	static EffectID GENERATE_ID();
};

