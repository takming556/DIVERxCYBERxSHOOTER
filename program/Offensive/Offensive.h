﻿#pragma once
#include <memory>
#include <vector>
#include "DxLib.h"
#include "CollideRealm/CollideRealm.h"
#include "Position/InFieldPosition.h"
#include "enum.h"

//using OffensiveID = unsigned int;

using std::unique_ptr;
using std::shared_ptr;
using std::vector;


class Offensive {
protected:
	SkinID skin_id;
	//static unsigned int NEXT_ID;
	LONGLONG last_updated_clock;
	int last_frame_updated_clock;	// 最後にフレームが変更された時刻
	Offensive() = default;
public:
	//static void INITIALIZE();
	//unique_ptr<CollideRealm> collidant;
	//virtual bool is_collided_with_my_character() = 0;
	//virtual bool is_collided_with_enemy_characters() = 0;
	Offensive(SkinID given_skin_id);
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual ~Offensive();
	//static OffensiveID GENERATE_ID();
};