#pragma once
#include "StraightShot.h"

class ReflectShot : public StraightShot {
protected:

public:
	ReflectShot();
	void update() override;
	void draw() override;
};