#pragma once
#include <vector>
#include <string>
#include <utility>

using std::vector;
using std::wstring;
using std::pair;


class FontHandles {
private:
	FontHandles() {}
	static const vector<pair<wstring, wstring>> FONTS;
public:
	static void LOAD_ALL_FONT();
	static void UNLOAD_ALL_FONT();
	static int DSEG14;
	static int HGP_SOUEIKAKU_GOTHIC_UB_64;
	static int HGP_SOUEIKAKU_GOTHIC_UB_48;
	static int HGP_SOUEIKAKU_GOTHIC_UB_32;
	static int HGP_SOUEIKAKU_GOTHIC_UB_24;
	static int HGP_SOUEIKAKU_GOTHIC_UB_16;
	static int CONSOLAS_64;
	static int NARRATIVE_POP_TEXT;
	static int NARRATIVE_POP_TEXT_NOSTALGIC;
	static int SCOREBOARD_VALUE;
	static int SCOREBOARD_TEXT;
	static int NAVIGATION_TEXT;
};