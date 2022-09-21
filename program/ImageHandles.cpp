#include "DxLib.h"
#include "class.h"


int ImageHandles::FIELD_BACKGROUND;
int ImageHandles::TEST_SHOOTER;
int ImageHandles::BLUE_MARBLE;
int ImageHandles::RED_MARBLE;
int ImageHandles::MAJIKICHI_SMILE;
int ImageHandles::HAND_POWER;
int ImageHandles::PIEN;
int ImageHandles::HEART;
int ImageHandles::MELTING_FACE;
int ImageHandles::THINKING_FACE;
int ImageHandles::SUNGLASS_FACE;


void ImageHandles::LOAD_ALL_IMAGE() {
	ImageHandles::FIELD_BACKGROUND = DxLib::LoadGraph("image/field.png");
	ImageHandles::TEST_SHOOTER = DxLib::LoadGraph("image/test_shooter.png");
	ImageHandles::BLUE_MARBLE = DxLib::LoadGraph("image/blue_marble.png");
	ImageHandles::RED_MARBLE = DxLib::LoadGraph("image/red_marble.png");
	ImageHandles::MAJIKICHI_SMILE = DxLib::LoadGraph("image/majikichi_smile.png");
	ImageHandles::HAND_POWER = DxLib::LoadGraph("image/hand_power.png");
	ImageHandles::PIEN = DxLib::LoadGraph("image/pien.png");
	ImageHandles::HEART = DxLib::LoadGraph("image/heart.png");
	ImageHandles::MELTING_FACE = DxLib::LoadGraph("image/melting_face.png");
	ImageHandles::THINKING_FACE = DxLib::LoadGraph("image/thinking_face.png");
	ImageHandles::SUNGLASS_FACE = DxLib::LoadGraph("image/sun_glass_face.png");
}