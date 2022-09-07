#pragma once

class AppSession;
class GameSession;


class Screen;
class TitleScreen;
class GameScreen;
class ResultScreen;
class RankingScreen;

class Character;
class MyCharacter;
class Deziko;
class EnemyCharacter;
class ZakoCharacter;
class BossCharacter;

class Bullet;
class MyBullet;
class EnemyBullet;

class Field;
class Scoreboard;




class AppSession {

};


class GameSession {

};


class Screen {
public:
	static const int SCREEN_RESOLUTION_X = 1024;	//��ʉ𑜓xX(�s�N�Z��)
	static const int SCREEN_RESOLUTION_Y = 768;		//��ʉ𑜓xY(�s�N�Z��)
};


class TitleScreen : public Screen {

};


class GameScreen : public Screen {

};


class ResultScreen : public Screen {

};


class RankingScreen : public Screen {

};





class Character {
private:
	int position_x;
	int position_y;
protected:
	Character();
public:
};


class MyCharacter : public Character{
private:
	unsigned int life;
};


class Deziko : public MyCharacter {

};


class EnemyCharacter : public Character{
private:
	unsigned int HP;
};


class ZakoCharacter : public EnemyCharacter {

};


class BossCharacter : public EnemyCharacter {

};


class Bullet {

};


class MyBullet : public Bullet {

};


class NormalShot : public MyBullet {

};


class EnemyBullet : public Bullet {

};


class Field {
public:
	Field();
	void draw();
	static const int FIELD_DRAW_POSITION_X = 350;	//�t�B�[���h�̕`��ʒu���SX���W(�s�N�Z��)
	static const int FIELD_DRAW_POSITION_Y = 384;	//�t�B�[���h�̕`��ʒu���SY���W(�s�N�Z��)
	static const int FIELD_PIXEL_SIZE_X = 620;		//�t�B�[���h�̕�(�s�N�Z��)
	static const int FIELD_PIXEL_SIZE_Y = 742;		//�t�B�[���h�̍���(�s�N�Z��)
	static const double FIELD_DRAW_EXTRATE;			
};


class Scoreboard {

};