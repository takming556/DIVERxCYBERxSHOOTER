#pragma once

enum class Scene {
	TITLE,
	GAMING,
	NICKNAMEINPUT,
	RESULT,
	RANKING
};


enum class Stage {
	STAGE1,
	STAGE2,
	STAGE3
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
	BUBBLE_GENERIC,
	GRAVITYSHOTTEST,
	HOMINGSHOTTEST,
	MAGNETIC_ARROW,
	TOROI_SP1_TRICK,
	TOROI_SP5_RAIN_SOU,
	TOROI_SP5_RAIN_UTU,
	TOROI_SP5_HEART_RED,
	TOROI_SP5_HEART_ORANGE,
	TOROI_SP5_HEART_YELLOW,
	TOROI_SP5_HEART_GREEN,
	TOROI_SP5_HEART_TEAL,
	TOROI_SP5_HEART_AQUA,
	TOROI_SP5_HEART_BLUE,
	TOROI_SP5_HEART_PURPLE,
	TOROI_SP5_HEART_FUCHSIA,
	TOROI_SP6_RAN_A_CHEESE,
	TOROI_SP6_RAN_B_LETUS,
	TOROI_SP6_RU_POTATO,
	TOROI_SP6_RU_TOMATO,
	TOROI_SP6_RAN_POSE
};


enum class Stage1Progress {
	//TEST,
	//DONOTHING,
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


enum class Stage2Progress {
	A,
	B,
};


enum class Stage3Progress {
	WAVE1,
	WAVE2,
	WAVE3,
	WAVE4,
	WAVE5,
	WAVE6,
	BOSS
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


enum class NeonStatus {
	NORMAL1,
	SP1,		// 東風飛梅
	NORMAL2,
	SP2,		// 天神さまの祟り
	NORMAL3,
	SP3,		// 狂気を帯びるライデンスパーク
	NORMAL4,
	SP4			// シャッフルトレイン
};


enum class ToroiStatus {
	NORMAL1,
	SP1,		// Trick or Treat or Trap?
	NORMAL2,
	SP2,		// 慈子欺瞞クリーナー
	SP3,		// 赤き怨みは稲穂を揺らす
	NORMAL3,
	SP4,		// 咲き誇れ、血染めの梅
	SP5,		// インターネット再興
	NORMAL4,
	SP6,		// Ex-tROiA.ru 4(D)
	SP7			// 限りなく降り注ぐ、嬰怨の涙
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


enum class ToroiSP1Mode {
	INITIAL,
	QUESTIONING,
	TRICK,
	TREAT,
	TRAP
};

enum class ToroiSP6Mode {
	RAN_A_INITIAL,
	RAN_A,
	RAN_B_INITIAL,	// RAN_A終了後のクリア処理のため
	RAN_B,
	RU_INITAL,
	RU
};

enum class CharacterID {
	ZKCHRSTG1WV5S_L,
	ZKCHRSTG1WV5S_R,
	ZKCHRSTG1WV5L,
	ZKCHRSTG1BSSP3_A,
	ZKCHRSTG1BSSP3_B,
	ZKCHRSTG1BSSP3_C,
	ZKCHRSTG1BSSP3_D,
	MOFU,
	NEON,
	TOROI
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