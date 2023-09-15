#pragma once
class FontHandles {
private:
	FontHandles() {}
public:
	static void LOAD_ALL_FONT();
	static int DSEG14;
	static int HGP_SOUEIKAKU_GOTHIC_UB_64;
	static int HGP_SOUEIKAKU_GOTHIC_UB_48;
	static int HGP_SOUEIKAKU_GOTHIC_UB_32;
	static int HGP_SOUEIKAKU_GOTHIC_UB_24;
	static int HGP_SOUEIKAKU_GOTHIC_UB_16;
	static int CONSOLAS_64;
};