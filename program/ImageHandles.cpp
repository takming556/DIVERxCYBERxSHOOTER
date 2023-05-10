#include "DxLib.h"
#include "ImageHandles.h"


int ImageHandles::FULLBODY_ICHIGOCHAN_NORMAL;
int ImageHandles::FULLBODY_ICHIGOCHAN_AVATAR;
int ImageHandles::FULLBODY_MOFU;
int ImageHandles::FULLBODY_NEON;
int ImageHandles::FULLBODY_TOROI;

int ImageHandles::SPRITE_ICHIGOCHAN;
int ImageHandles::SPRITE_MOFU;
int ImageHandles::SPRITE_NEON;
int ImageHandles::SPRITE_TOROI;
int ImageHandles::SPRITE_ZKCHR_KURAGE;
int ImageHandles::SPRITE_ZKCHR_KUJIRA;
int ImageHandles::SPRITE_ZKCHR_GUARDIAN_DWARF;
int ImageHandles::SPRITE_ZKCHR_ATTACKER_NIGHT;
int ImageHandles::SPRITE_ZKCHR_GOD_OF_ABSOLUTE_LOVE;
int ImageHandles::SPRITE_ZKCHR_GOD_OF_MISSING_LOVE;

int ImageHandles::ANCHOR_BLACK;
int ImageHandles::ANCHOR_GRAY;
int ImageHandles::ANCHOR_SILVER;
int ImageHandles::ANCHOR_WHITE;
int ImageHandles::ANCHOR_BLUE;
int ImageHandles::ANCHOR_NAVY;
int ImageHandles::ANCHOR_TEAL;
int ImageHandles::ANCHOR_GREEN;
int ImageHandles::ANCHOR_LIME;
int ImageHandles::ANCHOR_AQUA;
int ImageHandles::ANCHOR_YELLOW;
int ImageHandles::ANCHOR_RED;
int ImageHandles::ANCHOR_FUCHSIA;
int ImageHandles::ANCHOR_OLIVE;
int ImageHandles::ANCHOR_PURPLE;
int ImageHandles::ANCHOR_MAROON;

int ImageHandles::BUBBLE_BLACK;
int ImageHandles::BUBBLE_GRAY;
int ImageHandles::BUBBLE_SILVER;
int ImageHandles::BUBBLE_WHITE;
int ImageHandles::BUBBLE_BLUE;
int ImageHandles::BUBBLE_NAVY;
int ImageHandles::BUBBLE_TEAL;
int ImageHandles::BUBBLE_GREEN;
int ImageHandles::BUBBLE_LIME;
int ImageHandles::BUBBLE_AQUA;
int ImageHandles::BUBBLE_YELLOW;
int ImageHandles::BUBBLE_RED;
int ImageHandles::BUBBLE_FUCHSIA;
int ImageHandles::BUBBLE_OLIVE;
int ImageHandles::BUBBLE_PURPLE;
int ImageHandles::BUBBLE_MAROON;

int ImageHandles::CRYSTAL_BLACK;
int ImageHandles::CRYSTAL_GRAY;
int ImageHandles::CRYSTAL_SILVER;
int ImageHandles::CRYSTAL_WHITE;
int ImageHandles::CRYSTAL_BLUE;
int ImageHandles::CRYSTAL_NAVY;
int ImageHandles::CRYSTAL_TEAL;
int ImageHandles::CRYSTAL_GREEN;
int ImageHandles::CRYSTAL_LIME;
int ImageHandles::CRYSTAL_AQUA;
int ImageHandles::CRYSTAL_YELLOW;
int ImageHandles::CRYSTAL_RED;
int ImageHandles::CRYSTAL_FUCHSIA;
int ImageHandles::CRYSTAL_OLIVE;
int ImageHandles::CRYSTAL_PURPLE;
int ImageHandles::CRYSTAL_MAROON;

int ImageHandles::STRAWBERRY_BLACK;
int ImageHandles::STRAWBERRY_GRAY;
int ImageHandles::STRAWBERRY_SILVER;
int ImageHandles::STRAWBERRY_WHITE;
int ImageHandles::STRAWBERRY_BLUE;
int ImageHandles::STRAWBERRY_NAVY;
int ImageHandles::STRAWBERRY_TEAL;
int ImageHandles::STRAWBERRY_GREEN;
int ImageHandles::STRAWBERRY_LIME;
int ImageHandles::STRAWBERRY_AQUA;
int ImageHandles::STRAWBERRY_YELLOW;
int ImageHandles::STRAWBERRY_RED;
int ImageHandles::STRAWBERRY_FUCHSIA;
int ImageHandles::STRAWBERRY_OLIVE;
int ImageHandles::STRAWBERRY_PURPLE;
int ImageHandles::STRAWBERRY_MAROON;


int ImageHandles::LOGO;
int ImageHandles::LOGO_NONSILHOUETTE;
int ImageHandles::ICHIGOCHAN_CONCEPTUAL;
int ImageHandles::SCREEN_BACKGROUND;
int ImageHandles::SCREEN_BACKGROUND_CROPPED;
int ImageHandles::FIELD_BACKGROUND_STAGE1;
int ImageHandles::DIGIT_CURSOR;


int ImageHandles::FIELD_BACKGROUND;
int ImageHandles::TEST_SHOOTER;
int ImageHandles::BLUE_MARBLE;
int ImageHandles::RED_MARBLE;
int ImageHandles::ORANGE_TRIANGLE;
int ImageHandles::MAJIKICHI_SMILE;
int ImageHandles::HAND_POWER;
int ImageHandles::PIEN;
int ImageHandles::HEART;
int ImageHandles::MELTING_FACE;
int ImageHandles::THINKING_FACE;
int ImageHandles::SUNGLASS_FACE;
int ImageHandles::KURAGE;
int ImageHandles::KUJIRA;


void ImageHandles::LOAD_ALL_IMAGE() {
	FULLBODY_ICHIGOCHAN_NORMAL = DxLib::LoadGraph("image/stand/1.png");
	FULLBODY_ICHIGOCHAN_AVATAR = DxLib::LoadGraph("image/stand/2.png");
	FULLBODY_MOFU = DxLib::LoadGraph("image/stand/3.png");
	FULLBODY_NEON = DxLib::LoadGraph("image/stand/4.png");
	FULLBODY_TOROI = DxLib::LoadGraph("image/stand/5.png");

	SPRITE_ICHIGOCHAN = DxLib::LoadGraph("image/sprite/character/6.png");
	SPRITE_MOFU = DxLib::LoadGraph("image/sprite/character/7.png");
	SPRITE_NEON = DxLib::LoadGraph("image/sprite/character/8.png");
	SPRITE_TOROI = DxLib::LoadGraph("image/sprite/character/9.png");
	SPRITE_ZKCHR_KURAGE = DxLib::LoadGraph("image/sprite/character/10.png");
	SPRITE_ZKCHR_KUJIRA = DxLib::LoadGraph("image/sprite/character/11.png");
	SPRITE_ZKCHR_GUARDIAN_DWARF = DxLib::LoadGraph("image/sprite/character/14.png");
	SPRITE_ZKCHR_ATTACKER_NIGHT = DxLib::LoadGraph("image/sprite/character/15.png");
	SPRITE_ZKCHR_GOD_OF_ABSOLUTE_LOVE = DxLib::LoadGraph("image/sprite/character/12.png");
	SPRITE_ZKCHR_GOD_OF_MISSING_LOVE = DxLib::LoadGraph("image/sprite/character/13.png");

	ANCHOR_BLACK = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor01black.png");
	ANCHOR_GRAY = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor02gray.png");
	ANCHOR_SILVER = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor03silver.png");
	ANCHOR_WHITE = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor04white.png");
	ANCHOR_BLUE = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor05blue.png");
	ANCHOR_NAVY = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor06navy.png");
	ANCHOR_TEAL = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor07teal.png");
	ANCHOR_GREEN = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor08green.png");
	ANCHOR_LIME = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor09lime.png");
	ANCHOR_AQUA = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor10aqua.png");
	ANCHOR_YELLOW = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor11yellow.png");
	ANCHOR_RED = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor12red.png");
	ANCHOR_FUCHSIA = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor13fuchsia.png");
	ANCHOR_OLIVE = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor14olive.png");
	ANCHOR_PURPLE = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor15purple.png");
	ANCHOR_MAROON = DxLib::LoadGraph("image/sprite/bullet/Anchor/Anchor16maroon.png");

	BUBBLE_BLACK = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble01black.png");
	BUBBLE_GRAY = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble02gray.png");
	BUBBLE_SILVER = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble03silver.png");
	BUBBLE_WHITE = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble04white.png");
	BUBBLE_BLUE = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble05blue.png");
	BUBBLE_NAVY = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble06navy.png");
	BUBBLE_TEAL = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble07teal.png");
	BUBBLE_GREEN = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble08green.png");
	BUBBLE_LIME = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble09lime.png");
	BUBBLE_AQUA = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble10aqua.png");
	BUBBLE_YELLOW = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble11yellow.png");
	BUBBLE_RED = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble12red.png");
	BUBBLE_FUCHSIA = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble13fuchsia.png");
	BUBBLE_OLIVE = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble14olive.png");
	BUBBLE_PURPLE = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble15purple.png");
	BUBBLE_MAROON = DxLib::LoadGraph("image/sprite/bullet/Bubble/Bubble16maroon.png");

	CRYSTAL_BLACK = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal01black.png");
	CRYSTAL_GRAY = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal02gray.png");
	CRYSTAL_SILVER = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal03silver.png");
	CRYSTAL_WHITE = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal04white.png");
	CRYSTAL_BLUE = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal05blue.png");
	CRYSTAL_NAVY = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal06navy.png");
	CRYSTAL_TEAL = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal07teal.png");
	CRYSTAL_GREEN = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal08green.png");
	CRYSTAL_LIME = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal09lime.png");
	CRYSTAL_AQUA = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal10aqua.png");
	CRYSTAL_YELLOW = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal11yellow.png");
	CRYSTAL_RED = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal12red.png");
	CRYSTAL_FUCHSIA = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal13fuchsia.png");
	CRYSTAL_OLIVE = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal14olive.png");
	CRYSTAL_PURPLE = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal15purple.png");
	CRYSTAL_MAROON = DxLib::LoadGraph("image/sprite/bullet/Crystal/Crystal16maroon.png");

	STRAWBERRY_BLACK = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry01black.png");
	STRAWBERRY_GRAY = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry02gray.png");
	STRAWBERRY_SILVER = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry03silver.png");
	STRAWBERRY_WHITE = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry04white.png");
	STRAWBERRY_BLUE = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry05blue.png");
	STRAWBERRY_NAVY = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry06navy.png");
	STRAWBERRY_TEAL = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry07teal.png");
	STRAWBERRY_GREEN = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry08green.png");
	STRAWBERRY_LIME = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry09lime.png");
	STRAWBERRY_AQUA = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry10aqua.png");
	STRAWBERRY_YELLOW = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry11yellow.png");
	STRAWBERRY_RED = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry12red.png");
	STRAWBERRY_FUCHSIA = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry13fuchsia.png");
	STRAWBERRY_OLIVE = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry14olive.png");
	STRAWBERRY_PURPLE = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry15purple.png");
	STRAWBERRY_MAROON = DxLib::LoadGraph("image/sprite/bullet/Strawberry/Strawberry16maroon.png");

	LOGO = DxLib::LoadGraph("image/DCSロゴ_シルエットあり.png");
	LOGO_NONSILHOUETTE = DxLib::LoadGraph("image/DCSロゴ.png");
	ICHIGOCHAN_CONCEPTUAL = DxLib::LoadGraph("image/いちごちゃん_タイトル画面.png");
	SCREEN_BACKGROUND = DxLib::LoadGraph("image/スクリーン背景.png");
	SCREEN_BACKGROUND_CROPPED = DxLib::LoadGraph("image/スクリーン背景_くりぬき.png");
	FIELD_BACKGROUND_STAGE1 = DxLib::LoadGraph("image/フィールド背景_ステージ1.png");
	DIGIT_CURSOR = DxLib::LoadGraph("image/DigitCursor.png");

	//FIELD_BACKGROUND = DxLib::LoadGraph("image/test/field.png");
	//TEST_SHOOTER = DxLib::LoadGraph("image/test/pink_triangle.png");
	//BLUE_MARBLE = DxLib::LoadGraph("image/test/blue_marble.png");
	//RED_MARBLE = DxLib::LoadGraph("image/test/red_marble.png");
	//ORANGE_TRIANGLE = DxLib::LoadGraph("image/test/orange_triangle.png");
	//MAJIKICHI_SMILE = DxLib::LoadGraph("image/test/majikichi_smile.png");
	//HAND_POWER = DxLib::LoadGraph("image/test/hand_power.png");
	//PIEN = DxLib::LoadGraph("image/test/pien.png");
	//HEART = DxLib::LoadGraph("image/test/heart.png");
	//MELTING_FACE = DxLib::LoadGraph("image/test/melting_face.png");
	//THINKING_FACE = DxLib::LoadGraph("image/test/thinking_face.png");
	//SUNGLASS_FACE = DxLib::LoadGraph("image/test/sun_glass_face.png");
	//KURAGE = DxLib::LoadGraph("image/test/kurage.png");
	//KUJIRA = DxLib::LoadGraph("image/test/kujira.png");
}