﻿#pragma once

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
	STAGE3,
	FINISH
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
	KURAGE_AME,
	BUBBLE_GENERIC,
	BUBBLE_GENERIC_10,
	GRAVITYSHOTTEST,
	HOMINGSHOTTEST,
	MAGNETIC_ARROW,
	STG2_WAVE5_L,
	STG2_WAVE5_R,
	STG2_WAVE6_L,
	STG2_WAVE6_R,
	STG2_WAVE7_L,
	STG2_WAVE7_R,
	STG2_WAVE8_L,
	STG2_WAVE8_R,
	NEON_NM2_STRAIGHT,
	NEON_NM2_LASER,
	NEON_NM3_RED,
	NEON_NM3_ORANGE,
	NEON_NM3_YELLOW,
	NEON_NM3_GREEN,
	NEON_NM3_TEAL,
	NEON_NM3_AQUA,
	NEON_NM3_BLUE,
	NEON_NM3_PURPLE,
	NEON_NM3_FUCHSIA,
	NEON_NM4_CRYSTAL_RED,
	NEON_NM4_CRYSTAL_BLUE,
	NEON_SP2_GHOST,
	NEON_SP2_LASER,
	NEON_SP3_LASER,
	NEON_SP3_LEIDEN_JAR,
	NEON_SP3_EXPLOSION,
	NEON_SP4_SHUFFLE,
	NEON_SP4_TRAIN,
	STG3_WAVE3_C,
	STG3_WAVE3_LR,
	STG3_WAVE1_R,
	STG3_WAVE1_L,
	STG3_WAVE2_R,
	STG3_WAVE2_L,
	STG3_WAVE4_LR,
	STG3_WAVE4_C_PORTAL,
	STG3_WAVE4_C_LASER,
	STG3_WAVE5_T,
	STG3_WAVE5_B,
	STG3_WAVE6_C_ANCHOR,
	STG3_WAVE6_LR_GHOST,
	TOROI_NM1_MULTIPLY,
	TOROI_NM2,
	TOROI_NM2LASER_RED,
	TOROI_NM3_REFLECT,
	TOROI_NM3_DECOY,
	TOROI_NM3_COY,
	TOROI_NM3_PARASOL_RAIN,
	TOROI_NM4_RED_BIG,
	TOROI_NM4_RED_SMALL,
	TOROI_NM4_BLUE_BIG,
	TOROI_NM4_BLUE_SMALL,
	TOROI_SP1_TRICK,
	TOROI_SP1_TREAT,
	TOROI_SP1_TRAP,
	TOROI_SP2_SURROUNDED,
	TOROI_SP2_STING,
	TOROI_SP2_RAIN,
	TOROI_SP3_SLASH,
	TOROI_SP3_BESIEGE,
	TOROI_SP3_GHOST,
	TOROI_SP3_BLOOD_SPLASH,
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
	TOROI_SP6_RAN_POSE,
	LASER_TEST
};


enum class Stage1Progress {
	LASER_TEST_BEGIN,
	LASER_TEST_END,
	NARRATIVE_POP_TEST_BEGIN,
	NARRATIVE_POP_TEST_END,
	REFLECT_SHOT_TEST_BEGIN,
	REFLECT_SHOT_TEST_END,
	PREPARE,
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
	PREPARE,
	START,
	WAVE1,
	WAVE2,
	WAVE3,
	WAVE4,
	WAVE5,
	WAVE6,
	WAVE7,
	WAVE8,
	BOSS,
	EPILOGUE,
	END
};


enum class Stage3Progress {
	PREPARE,
	START,
	WAVE1,
	WAVE2,
	WAVE3,
	WAVE4,
	WAVE5,
	WAVE6,
	BOSS,
	YES_NO_SELECT,
	EPILOGUE,
	END
};


enum class MofuStatus
{
	STANDBY,
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
	PREPARE,
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

enum class Stg1WAVE3SMode {
	ENTER,
	STAY,
	EXIT
};

enum class Stg1WAVE3LMode {
	ENTER,
	STAY,
	EXIT
};

enum class Stg1WAVE4Mode {
	ENTER,
	STAY,
	EXIT
};

enum class Stg1WAVE5SMode {
	ENTER,
	STAY,
	EXIT
};

enum class Stg1WAVE5LMode {
	ENTER,
	STAY,
	EXIT
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

enum class Stg2WAVE5MoveFlag {
	ENTER,
	STAY,
	EXIT
};

enum class Stg2WAVE7TurnFlag{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	EXIT
};

enum class Stg2WAVE8MoveFlag {
	RAISE,
	LINE_UP,
	WAIT,
	LOWER
};

enum class Stg2WAVE8WaitFlag {
	WAIT,
	GO
};

enum class NeonNormal2LaserStatus {
	AWAIT,
	NOTIFY,
	EMIT
};

enum class NeonNormal4CrystalMode {
	RED,
	BLUE
};

enum class NeonSp2LaserStatus {
	AWAIT,
	NOTIFY,
	EMIT
};

enum class NeonSp3Status {
	FLOATING,

};

//enum class Stg3WAVE3LRType {
//	LEFT,
//	RIGHT
//};

enum class Stg3WAVE3MoveFlag {
	ENTER,
	STAY,
	EXIT
};

enum class Stg3WAVE1Mode {
	DOWN,
	CURVE,
	CIRCLE,
	EXIT
};

enum class Stg3WAVE2Mode{
	Straight,
	CURVE,
	EXIT
};

//enum class Stg3WAVE3LRType {
//	LEFT,
//	RIGHT
//};

enum class Stg3WAVE4LR {
	LEFT,
	RIGHT
};

enum class Stg3WAVE4LRMode {
	ENTER,
	ROLL,
	EXIT
};

enum class Stg3WAVE4CMode {
	ENTER,
	PORTAL,
	NOTIFY,
	LASER,
	EXIT
};

enum class Stg3WAVE5TLR {
	LEFT,
	RIGHT
};

enum class Stg3WAVE5BMode {
	ENTER,
	ROLL,
	EXIT
};

enum class Stg3WAVE5BLR {
	LEFT,
	RIGHT
};

enum class Stg3WAVE6CMoveFlag {
	ENTER,
	STAY,
	EXIT
};

enum class Stg3WAVE6CGenerateFlag {
	UP,
	DOWN
};

//enum class Stg3WAVE6LRType {
//	LEFT,
//	RIGHT
//};

enum class ToroiNM2Mode {
	WARNING,
	NOTIFY,
	SHOT
};

enum class ToroiNm3Status {
	INITIAL,
	WAIT
};

enum class ToroiNM4ColorFlag {
	RED,
	BLUE
};

enum class ToroiSP1Mode {
	INITIAL,
	QUESTIONING,
	TRICK,
	TREAT,
	TRAP_INIT,
	TRAP_ACROSS_INIT,
	TRAP
};

enum class ToroiSP3Status {
	STEP1_INIT,
	STEP1,
	STEP2,
	STEP3_INIT,
	STEP3,
	STEP4_INIT,
	STEP4,
	STEP5
};

enum class ToroiSP6Mode {
	RAN_A_INITIAL,
	RAN_A,
	RAN_B_INITIAL,	// RAN_A終了後のクリア処理のため
	RAN_B,
	RU_INITAL,
	RU
};

enum class Y_N {
	YES,
	NO
};

enum class CharacterID {
	ICHIGO_CHAN,
	ZKCHRSTG1WV1_L1,
	ZKCHRSTG1WV1_L2,
	ZKCHRSTG1WV1_L3,
	ZKCHRSTG1WV1_R1,
	ZKCHRSTG1WV1_R2,
	ZKCHRSTG1WV1_R3,
	ZKCHRSTG1WV2_1U,
	ZKCHRSTG1WV2_1L,
	ZKCHRSTG1WV2_2U,
	ZKCHRSTG1WV2_2L,
	ZKCHRSTG1WV3S_1,
	ZKCHRSTG1WV3S_2,
	ZKCHRSTG1WV3S_3,
	ZKCHRSTG1WV3S_4,
	ZKCHRSTG1WV3L_1,
	ZKCHRSTG1WV3L_2,
	ZKCHRSTG1WV4_A,
	ZKCHRSTG1WV4_B,
	ZKCHRSTG1WV4_C,
	ZKCHRSTG1WV4_D,
	ZKCHRSTG1WV5S_L,
	ZKCHRSTG1WV5S_R,
	ZKCHRSTG1WV5L,
	ZKCHRSTG1BSSP3_A,
	ZKCHRSTG1BSSP3_B,
	ZKCHRSTG1BSSP3_C,
	ZKCHRSTG1BSSP3_D,
	ZKCHRSTG2WV4_L,
	ZKCHRSTG2WV4_R,
	ZKCHRSTG2WV5_L,
	ZKCHRSTG2WV5_R,
	ZKCHRSTG2WV6_L1,
	ZKCHRSTG2WV6_L2,
	ZKCHRSTG2WV6_L3,
	ZKCHRSTG2WV6_L4,
	ZKCHRSTG2WV6_L5,
	ZKCHRSTG2WV6_R1,
	ZKCHRSTG2WV6_R2,
	ZKCHRSTG2WV6_R3,
	ZKCHRSTG2WV6_R4,
	ZKCHRSTG2WV6_R5,
	ZKCHRSTG2WV7_L1,
	ZKCHRSTG2WV7_L2,
	ZKCHRSTG2WV7_L3,
	ZKCHRSTG2WV7_L4,
	ZKCHRSTG2WV7_L5,
	ZKCHRSTG2WV7_R1,
	ZKCHRSTG2WV7_R2,
	ZKCHRSTG2WV7_R3,
	ZKCHRSTG2WV7_R4,
	ZKCHRSTG2WV7_R5,
	ZKCHRSTG2WV8_L1,
	ZKCHRSTG2WV8_L2,
	ZKCHRSTG2WV8_L3,
	ZKCHRSTG2WV8_L4,
	ZKCHRSTG2WV8_L5,
	ZKCHRSTG2WV8_L6,
	ZKCHRSTG2WV8_L7,
	ZKCHRSTG2WV8_L8,
	ZKCHRSTG2WV8_R1,
	ZKCHRSTG2WV8_R2,
	ZKCHRSTG2WV8_R3,
	ZKCHRSTG2WV8_R4,
	ZKCHRSTG2WV8_R5,
	ZKCHRSTG2WV8_R6,
	ZKCHRSTG2WV8_R7,
	ZKCHRSTG2WV8_R8,
	ZKCHRSTG2BSNM4_1,
	ZKCHRSTG2BSNM4_2,
	ZKCHRSTG2BSNM4_3,
	ZKCHRSTG2BSNM4_4,
	ZKCHRSTG2BSNM4_5,
	ZKCHRSTG3WV1_L1,
	ZKCHRSTG3WV1_L2,
	ZKCHRSTG3WV1_L3,
	ZKCHRSTG3WV1_L4,
	ZKCHRSTG3WV1_L5,
	ZKCHRSTG3WV1_R1,
	ZKCHRSTG3WV1_R2,
	ZKCHRSTG3WV1_R3,
	ZKCHRSTG3WV1_R4,
	ZKCHRSTG3WV1_R5,
	ZKCHRSTG3WV2_L1,
	ZKCHRSTG3WV2_L2,
	ZKCHRSTG3WV2_L3,
	ZKCHRSTG3WV2_L4,
	ZKCHRSTG3WV2_L5,
	//ZKCHRSTG3WV2_L6,
	//ZKCHRSTG3WV2_L7,
	ZKCHRSTG3WV2_R1,
	ZKCHRSTG3WV2_R2,
	ZKCHRSTG3WV2_R3,
	ZKCHRSTG3WV2_R4,
	ZKCHRSTG3WV2_R5,
	//ZKCHRSTG3WV2_R6,
	//ZKCHRSTG3WV2_R7,
	ZKCHRSTG3WV3_C,
	ZKCHRSTG3WV3_L,
	ZKCHRSTG3WV3_R,
	ZKCHRSTG3WV4_L1,
	ZKCHRSTG3WV4_L2,
	ZKCHRSTG3WV4_L3,
	ZKCHRSTG3WV4_L4,
	ZKCHRSTG3WV4_L5,
	ZKCHRSTG3WV4_R1,
	ZKCHRSTG3WV4_R2,
	ZKCHRSTG3WV4_R3,
	ZKCHRSTG3WV4_R4,
	ZKCHRSTG3WV4_R5,
	ZKCHRSTG3WV4_C,
	ZKCHRSTG3WV5_T_L1,
	ZKCHRSTG3WV5_T_L2,
	ZKCHRSTG3WV5_T_L3,
	ZKCHRSTG3WV5_T_L4,
	ZKCHRSTG3WV5_T_L5,
	ZKCHRSTG3WV5_T_L6,
	ZKCHRSTG3WV5_T_L7,
	ZKCHRSTG3WV5_T_L8,
	ZKCHRSTG3WV5_T_L9,
	ZKCHRSTG3WV5_T_L10,
	ZKCHRSTG3WV5_T_R1,
	ZKCHRSTG3WV5_T_R2,
	ZKCHRSTG3WV5_T_R3,
	ZKCHRSTG3WV5_T_R4,
	ZKCHRSTG3WV5_T_R5,
	ZKCHRSTG3WV5_T_R6,
	ZKCHRSTG3WV5_T_R7,
	ZKCHRSTG3WV5_T_R8,
	ZKCHRSTG3WV5_T_R9,
	ZKCHRSTG3WV5_T_R10,
	ZKCHRSTG3WV5_B_L1,
	ZKCHRSTG3WV5_B_L2,
	ZKCHRSTG3WV5_B_L3,
	ZKCHRSTG3WV5_B_L4,
	ZKCHRSTG3WV5_B_L5,
	ZKCHRSTG3WV5_B_R1,
	ZKCHRSTG3WV5_B_R2,
	ZKCHRSTG3WV5_B_R3,
	ZKCHRSTG3WV5_B_R4,
	ZKCHRSTG3WV5_B_R5,
	ZKCHRSTG3WV6_L,
	ZKCHRSTG3WV6_R,
	ZKCHRSTG3WV6_C,
	MOFU,
	NEON,
	TOROI
};

enum class TitleScreenState {
	INIT,
	SELECTABLE
};


enum class MainMenuCursorPos {
	DIVE,
	GALLERY,
	CREDIT,
	CONFIG,
	EXIT
};


enum class TitleScreenCursor {

};


enum class PortraitID {
	ICHIGO_CHAN_NORMAL,
	ICHIGO_CHAN_AVATAR,
	TEXTFILE,
	MOFU,
	NEON,
	TOROI,
	NONE
};


enum class NarrativePopState {
	READY,		// まだ画面に出現していない
	ROLLING,	// 現在テキスト流転中
	AWAITING	// テキスト表示完了
};


enum class CollideJudgeTraceSide {
	INNER,
	OUTER
};