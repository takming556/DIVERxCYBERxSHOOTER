#include "DxLib.h"
#include "class.h"

int FontHandles::DSEG14;
int FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_64;
int FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_48;
int FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32;
int FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_24;
int FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_16;
int FontHandles::CONSOLAS_64;

void FontHandles::LOAD_ALL_FONT() {
	DSEG14 = DxLib::LoadFontDataToHandle("font/DSEG14 Classic Mini_32.dft");
	HGP_SOUEIKAKU_GOTHIC_UB_64 = DxLib::LoadFontDataToHandle("font/HGP�n�p�p�޼��UB_�T�C�Y64.dft");
	HGP_SOUEIKAKU_GOTHIC_UB_48 = DxLib::LoadFontDataToHandle("font/HGP�n�p�p�޼��UB_�T�C�Y48.dft");
	HGP_SOUEIKAKU_GOTHIC_UB_32 = DxLib::LoadFontDataToHandle("font/HGP�n�p�p�޼��UB_�T�C�Y32.dft");
	HGP_SOUEIKAKU_GOTHIC_UB_24 = DxLib::LoadFontDataToHandle("font/HGP�n�p�p�޼��UB_�T�C�Y24.dft");
	HGP_SOUEIKAKU_GOTHIC_UB_16 = DxLib::LoadFontDataToHandle("font/HGP�n�p�p�޼��UB_�T�C�Y16.dft");
	CONSOLAS_64 = DxLib::LoadFontDataToHandle("font/Consolas_�T�C�Y64.dft");
}