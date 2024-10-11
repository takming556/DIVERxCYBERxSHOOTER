#pragma once
#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "CollideRealm/CollideCircle.h"
#include "Position/InFieldPosition.h"

using std::unique_ptr;


class Character {
protected:
	LONGLONG last_updated_clock;
	Character(
		enum CharacterID given_id,
		double init_pos_x,
		double init_pos_y,
		int init_hp,
		unique_ptr<CollideCircle> given_collidant
	);
public:
	int hp;
	enum CharacterID id;
	unique_ptr<InFieldPosition> position;
	unique_ptr<CollideCircle> collidant;

	bool visible_flag = true; // キャラクターの表示/非表示を制御するフラグ
	bool blinking = false;    // 点滅中かどうかのフラグ
	int blink_interval_ms;    // 点滅の間隔
	int blink_end_time;       // 点滅が終了する時刻
	int next_blink_time;      // 次の点滅切り替え時刻
	void update();
	void draw_hp();
	bool is_dead();
	void blink(int interval_ms, int duration_ms);
	virtual void damaged() = 0;
	virtual void draw() = 0;
	~Character();
};