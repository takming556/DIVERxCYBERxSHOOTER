#include "DxLib.h"
#include "class.h"


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
int ImageHandles::DCS_LOGO;
int ImageHandles::ICHIGOCHAN_CONCEPTUAL;



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
	SPRITE_ICHIGOCHAN = DxLib::LoadGraph("image/sprite/6.png");
	SPRITE_MOFU = DxLib::LoadGraph("image/sprite/7.png");
	SPRITE_NEON = DxLib::LoadGraph("image/sprite/8.png");
	SPRITE_TOROI = DxLib::LoadGraph("image/sprite/9.png");
	SPRITE_ZKCHR_KURAGE = DxLib::LoadGraph("image/sprite/10.png");
	SPRITE_ZKCHR_KUJIRA = DxLib::LoadGraph("image/sprite/11.png");
	SPRITE_ZKCHR_GUARDIAN_DWARF = DxLib::LoadGraph("image/sprite/14.png");
	SPRITE_ZKCHR_ATTACKER_NIGHT = DxLib::LoadGraph("image/sprite/15.png");
	SPRITE_ZKCHR_GOD_OF_ABSOLUTE_LOVE = DxLib::LoadGraph("image/sprite/12.png");
	SPRITE_ZKCHR_GOD_OF_MISSING_LOVE = DxLib::LoadGraph("image/sprite/13.png");

	FIELD_BACKGROUND = DxLib::LoadGraph("image/test/field.png");
	TEST_SHOOTER = DxLib::LoadGraph("image/test/pink_triangle.png");
	BLUE_MARBLE = DxLib::LoadGraph("image/test/blue_marble.png");
	RED_MARBLE = DxLib::LoadGraph("image/test/red_marble.png");
	ORANGE_TRIANGLE = DxLib::LoadGraph("image/test/orange_triangle.png");
	MAJIKICHI_SMILE = DxLib::LoadGraph("image/test/majikichi_smile.png");
	HAND_POWER = DxLib::LoadGraph("image/test/hand_power.png");
	PIEN = DxLib::LoadGraph("image/test/pien.png");
	HEART = DxLib::LoadGraph("image/test/heart.png");
	MELTING_FACE = DxLib::LoadGraph("image/test/melting_face.png");
	THINKING_FACE = DxLib::LoadGraph("image/test/thinking_face.png");
	SUNGLASS_FACE = DxLib::LoadGraph("image/test/sun_glass_face.png");
	KURAGE = DxLib::LoadGraph("image/test/kurage.png");
	KUJIRA = DxLib::LoadGraph("image/test/kujira.png");
}