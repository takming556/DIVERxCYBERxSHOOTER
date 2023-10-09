#pragma once
#include <string>
#include "DxLib.h"

using std::wstring;

class Scenario {
protected:
	int kept_clock;
	int music_name_generated_clock;
	wstring music_name;
	static unsigned int MUSIC_NAME_INIT_POS_X;
	static unsigned int MUSIC_NAME_INIT_POS_Y;
	static unsigned int MUSIC_NAME_SCROLL_SPEED;
public:
	Scenario(wstring given_music_name);
	Scenario() = default;
	virtual void update() = 0;	// Scenario 抽象クラスをインスタンス化できません。
	// virtual void update();	// 何も表示されず、進行しない
	// void update();	// Stage1::update オーバーライド指定子 override を伴うメソッドは、
						// 基底クラスメソッドをオーバーライドしませんでした
};