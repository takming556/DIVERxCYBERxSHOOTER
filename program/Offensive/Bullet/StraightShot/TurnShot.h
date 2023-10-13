#pragma once
#include "Offensive/Bullet/StraightShot/StraightShot.h"


class TurnShot : public StraightShot {
private:
	bool already_turned_flag;
	int generated_clock;
	const unsigned int TURN_POSTPONE_TIME;
	const double ADD_ARG;
public:
	TurnShot(
		double init_pos_x,					// 初期位置X座標
		double init_pos_y,					// 初期位置Y座標
		double init_arg,					// 初期偏角[ラジアン]
		double init_speed,					// 初速度[ピクセル/秒]
		unsigned int turn_postpone_time,	// 生成から折れ曲がるまでの時間[ミリ秒]
		double add_arg,						// 折れ曲がるの追加角度[ラジアン]
		unsigned int collidant_size,		// 当たり判定の大きさ
		unsigned int durability,			// 弾の耐久値(HP)ふつうは1を指定せよ
		SkinID given_skin_id				// スキンID
	);
	void update() override;

};