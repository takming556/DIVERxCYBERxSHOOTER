﻿#include <vector>
#include <string>
#include <utility>
#include "DxLib.h"
#include "FontHandles.h"

using std::vector;
using std::wstring;
using std::make_pair;


int FontHandles::DSEG14;
int FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_64;
int FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_48;
int FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_32;
int FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_24;
int FontHandles::HGP_SOUEIKAKU_GOTHIC_UB_16;
int FontHandles::CONSOLAS_64;

int FontHandles::NARRATIVE_POP_TEXT;
int FontHandles::NARRATIVE_POP_TEXT_NOSTALGIC;
int FontHandles::SCOREBOARD_TEXT;
int FontHandles::SCOREBOARD_VALUE;
int FontHandles::NAVIGATION_TEXT;
int FontHandles::STAGE_NUM_TEXT;
int FontHandles::STAGE_NAME_MAIN_TEXT;
int FontHandles::STAGE_NAME_SUB_TEXT;
int FontHandles::SONG_NAME_TEXT;
int FontHandles::SP_NAME_TEXT;


const vector<pair<wstring, wstring>> FontHandles::FONTS = {
	make_pair<wstring, wstring>(L"源ノ角ゴシック ExtraLight", L"font/SourceHanSans-ExtraLight.ttc"),	// 0
	make_pair<wstring, wstring>(L"源ノ角ゴシック Heavy", L"font/SourceHanSans-Heavy.ttc"),			// 1
	make_pair<wstring, wstring>(L"KHドット日比谷32", L"font/KH-Dot-Hibiya-32.ttf"),					// 2
	make_pair<wstring, wstring>(L"DSEG14 Classic Mini", L"font/DSEG14ClassicMini-Regular.ttf"),		// 3
	make_pair<wstring, wstring>(L"ロンド B スクエア", L"font/Ronde-B_square.otf"),					// 4
	make_pair<wstring, wstring>(L"コーポレート明朝 ver3 Medium", L"font/Corporate-Mincho-ver3.otf"),	// 5
	make_pair<wstring, wstring>(L"Nautilus Pompilius", L"font/Nautilus.otf")						// 6
};



void FontHandles::LOAD_ALL_FONT() {

	for (const auto& font : FONTS) {
		int result = AddFontResourceEx(font.second.c_str(), FR_PRIVATE, NULL);
		if (result == 0) {
			MessageBox(NULL, L"フォント読込失敗", L"", MB_OK);
			exit(EXIT_FAILURE);
		}

	}

	NARRATIVE_POP_TEXT = DxLib::CreateFontToHandle(FONTS.at(0).first.c_str(), 24, 1, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_UTF8);
	NARRATIVE_POP_TEXT_NOSTALGIC = DxLib::CreateFontToHandle(FONTS.at(2).first.c_str(), 24, -1, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_UTF8);
	SCOREBOARD_TEXT = DxLib::CreateFontToHandle(FONTS.at(1).first.c_str(), 16, -1, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_UTF8);
	SCOREBOARD_VALUE = DxLib::CreateFontToHandle(FONTS.at(3).first.c_str(), 32, -1, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_UTF8);
	NAVIGATION_TEXT = DxLib::CreateFontToHandle(FONTS.at(1).first.c_str(), 48, -1, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_UTF8);
	STAGE_NUM_TEXT = DxLib::CreateFontToHandle(FONTS.at(4).first.c_str(), 32, -1, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_UTF8);
	STAGE_NAME_MAIN_TEXT = DxLib::CreateFontToHandle(FONTS.at(5).first.c_str(), 48, -1, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_UTF8);
	STAGE_NAME_SUB_TEXT = DxLib::CreateFontToHandle(FONTS.at(6).first.c_str(), 32, -1, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_UTF8);
	SONG_NAME_TEXT = DxLib::CreateFontToHandle(FONTS.at(4).first.c_str(), 32, -1, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_UTF8);
	SP_NAME_TEXT = DxLib::CreateFontToHandle(FONTS.at(5).first.c_str(), 32, -1, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_UTF8);
	DSEG14 = DxLib::LoadFontDataToHandle(L"font/DSEG14 Classic Mini_32.dft");
	HGP_SOUEIKAKU_GOTHIC_UB_64 = DxLib::LoadFontDataToHandle(L"font/HGP創英角ｺﾞｼｯｸUB_サイズ64.dft");
	HGP_SOUEIKAKU_GOTHIC_UB_48 = DxLib::LoadFontDataToHandle(L"font/HGP創英角ｺﾞｼｯｸUB_サイズ48.dft");
	HGP_SOUEIKAKU_GOTHIC_UB_32 = DxLib::LoadFontDataToHandle(L"font/HGP創英角ｺﾞｼｯｸUB_サイズ32.dft");
	HGP_SOUEIKAKU_GOTHIC_UB_24 = DxLib::LoadFontDataToHandle(L"font/HGP創英角ｺﾞｼｯｸUB_サイズ24.dft");
	HGP_SOUEIKAKU_GOTHIC_UB_16 = DxLib::LoadFontDataToHandle(L"font/HGP創英角ｺﾞｼｯｸUB_サイズ16.dft");
	CONSOLAS_64 = DxLib::LoadFontDataToHandle(L"font/Consolas_サイズ64.dft");
}


void FontHandles::UNLOAD_ALL_FONT() {
	DxLib::InitFontToHandle();
	for (const auto& font : FONTS) {
		int result = RemoveFontResourceEx(font.second.c_str(), FR_PRIVATE, NULL);
		if (result == 0) {
			MessageBox(NULL, L"フォント除去失敗", L"", MB_OK);
			exit(EXIT_FAILURE);
		}
	}
}