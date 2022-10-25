#include "DxLib.h"
#include "class.h"

int FontHandles::DSEG14;

void FontHandles::LOAD_ALL_FONT() {
	DSEG14 = LoadFontDataToHandle("font/DSEG14 Classic Mini_32.dft");
}