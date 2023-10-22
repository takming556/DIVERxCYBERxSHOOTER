#include <string>
#include "DxLib.h"
#include "Scenario/Scenario.h"
#include "Position/InFieldPosition.h"
#include "Colors.h"
#include "FontHandles.h"

using std::wstring;

unsigned int Scenario::MUSIC_NAME_INIT_POS_X = 700;
unsigned int Scenario::MUSIC_NAME_INIT_POS_Y = 700;
unsigned int Scenario::MUSIC_NAME_SCROLL_SPEED = 150;

Scenario::Scenario() :
	kept_clock(DxLib::GetNowCount()),
	boss_advented_clock(0),
	boss_advented_flag(false),
	boss_crushed_flag(false)
{
}