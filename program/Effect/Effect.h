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
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool IsExpired() = 0;
	virtual ~Effect() = default;
	static EffectID GENERATE_ID();
};

