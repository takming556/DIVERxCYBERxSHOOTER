#pragma once

class MyCharacter {
	
};


class EnemyCharacter {

};


class Screen {
public:
	static const int SCREEN_RESOLUTION_X = 1024;	//��ʉ𑜓xX(�s�N�Z��)
	static const int SCREEN_RESOLUTION_Y = 768;		//��ʉ𑜓xY(�s�N�Z��)
};


class Field {
public:
	Field();
	void draw();
	static const int FIELD_DRAW_POSITION_X = 400;	//�t�B�[���h�̕`��ʒu���SX���W(�s�N�Z��)
	static const int FIELD_DRAW_POSITION_Y = 384;	//�t�B�[���h�̕`��ʒu���SY���W(�s�N�Z��)
	static const int FIELD_PIXEL_SIZE_X = 620;		//�t�B�[���h�̕�(�s�N�Z��)
	static const int FIELD_PIXEL_SIZE_Y = 742;		//�t�B�[���h�̍���(�s�N�Z��)
	static const double FIELD_DRAW_EXTRATE;			
};


class AppSession {

};