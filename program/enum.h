#pragma once

enum class Scene {
	TITLE,
	GAMING,
	NICKNAMEINPUT,
	RESULT,
	RANKING
};


enum class Stage {
	STAGE1
};


enum class TeamID {
	MY,
	ENEMY
};


enum class SkinID {
	NORMAL_BLUE,
	TERROR,
	ICHIGO_CHAN,
	MOFU,
	BUBBLE_GENERIC
};


enum class Stage1Progress {
	START,
	A_LEFT_1,
	A_LEFT_2,
	A_LEFT_3,
	A_RIGHT_1,
	A_RIGHT_2,
	A_RIGHT_3,
	B1,
	B2,
	C,
	D1,
	D2,
	D3,
	D4,
	E,
	MOFU,
	FINISH,
};


enum class MofuStatus {
	NORMAL1,
	SP1,
	NORMAL2,
	SP2,
	NORMAL3,
	SP3,
	FINISH
};


enum class FloatingTerrorShotMode {
	FLOATING,
	TERROR
};


enum class KurageAmeShotMode {
	STRAIGHT,
	FALL
};


enum class MofuNormal3Mode {
	RIGHTROLL,
	LEFTROLL
};


enum class CharacterID {
	ZKCHRSTG1WV5S_L,
	ZKCHRSTG1WV5S_R,
	ZKCHRSTG1WV5L,
	MOFU,
	ZKCHRSTG1BSSP3_A,
	ZKCHRSTG1BSSP3_B,
	ZKCHRSTG1BSSP3_C,
	ZKCHRSTG1BSSP3_D,
};

enum class TitleScreenState {
	INIT,
	SELECTABLE
};

enum class TitleScreenCursor {

};


enum class PortraitID {
	ICHIGO_CHAN_NORMAL,
	ICHIGO_CHAN_AVATAR,
	MOFU,
	NEON,
	TOROI
};


enum class NarrativePopState {
	READY,		// まだ画面に出現していない
	ROLLING,	// 現在テキスト流転中
	AWAITING	// テキスト表示完了
};