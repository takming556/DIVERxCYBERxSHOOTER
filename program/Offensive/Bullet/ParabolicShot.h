#pragma once
#include "enum.h"
#include "Offensive/Bullet/Bullet.h"

class ParabolicShot : public Bullet {
private:
	enum SkinID skin_id;
	const double accel;
	const double accel_arg;
public:
	ParabolicShot(
		double init_pos_x,				// 第1引数 初期位置x
		double init_pos_y,				// 第2引数 初期位置y
		double init_arg,				// 第3引数 初速度の偏角
		double init_speed,				// 第4引数 初速度の大きさ
		double init_accel,				// 第5引数 加速度の大きさ
		double init_accel_arg,			// 第6引数 加速度の偏角
		unsigned int collidant_size,	// 第7引数 当たり判定の円の半径
		unsigned int durability,		// 第8引数 弾の耐久値(通常は1を指定せよ)
		enum SkinID given_skin_id		// 第9引数 SkinID
	);
	void update() override;
	void draw() override;
};