#pragma once
#include <vector>
#include <memory>
#include "Offensive/Offensive.h"

class Laser : public Offensive {
protected:
public:
	bool is_broken() override;
};