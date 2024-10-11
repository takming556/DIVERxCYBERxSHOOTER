#include <vector>
#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "Colors.h"
#include "Character/Character.h"
#include "CollideRealm/CollideCircle.h"

using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::move;


Character::Character(
	enum CharacterID given_id,
	double init_pos_x,
	double init_pos_y,
	int init_hp,
	unique_ptr<CollideCircle> given_collidant
) :
	hp(init_hp),
	id(given_id),
	position(make_unique<InFieldPosition>(init_pos_x, init_pos_y)),
	collidant(move(given_collidant)),
	last_updated_clock(DxLib::GetNowHiPerformanceCount()),
	blink_end_time(DxLib::GetNowCount()),
	blink_interval_ms(DxLib::GetNowCount()),
	next_blink_time(DxLib::GetNowCount())
{
}


Character::~Character() = default;

void Character::update() {
	if (blinking) {
		int current_time = DxLib::GetNowCount();

		// 点滅の終了時刻を過ぎていたら点滅終了
		if (current_time > blink_end_time) {
			blinking = false;
			visible_flag = true;  // 点滅が終わったら表示状態に戻す
		}
		// 次の点滅タイミングをチェック
		else if (current_time > next_blink_time) {
			visible_flag = !visible_flag;  // 表示/非表示を切り替える
			next_blink_time = current_time + blink_interval_ms;  // 次の点滅タイミングを設定
		}
	}
}

void Character::draw_hp() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::RED, L"%d", hp);
}

bool Character::is_dead() {
	return hp <= 0;
}

void Character::blink(int interval_ms, int duration_ms) {
	blink_interval_ms = interval_ms;
	blink_end_time = DxLib::GetNowCount() + duration_ms;
	next_blink_time = DxLib::GetNowCount() + interval_ms;
	blinking = true;
	visible_flag = true;  // 最初は見える状態からスタート
}
