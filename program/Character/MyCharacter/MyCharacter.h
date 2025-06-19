#pragma once
#include <string>
#include <vector>
//#include <unordered_map>
#include "enum.h"
#include "Character/Character.h"
#include "Collision.h"

using std::vector;
using std::wstring;
//using std::unordered_map;
using BulletID = unsigned int;
using LaserID = unsigned int;
using EffectID = unsigned int;


class MyCharacter : virtual public Character {
protected:
	wstring name;
	double shotFrequency;							//連射速度
	double moveSpeed;								//移動速度(pixel per second)
	int lastLaunchTickedClock;
	int invincibleEndClock;
	EffectID crashEffectId;
	int lastCrashedClock;
	bool isThereMyCrashEffect;
	int lastBlinkStartedClock;	// 最後に点滅を始めた時刻
	int lastBlinkSwitchedClock;	// 最後に点と滅を切り替えた時刻
	bool isVisible;				// キャラクター表示/非表示フラグ
	bool isBlinking;			// 点滅中フラグ

	vector<Collision<BulletID>> lastCollisionsWithEnemyBullet;
	//unordered_map<CharacterID, int> last_damaged_clocks;
	//vector<Collision<CharacterID>> last_collisions_with_enemy_character;
	vector<Collision<CharacterID>> lastCollisionsWithZakoCharacter;
	vector<Collision<CharacterID>> lastCollisionsWithBossCharacter;
	vector<Collision<LaserID>> lastCollisionsWithEnemyLaser;
	//LONGLONG lastUpdatedClock;
	MyCharacter(wstring character_name);
	void StartBlinking();
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void MoveUpRight();
	void MoveDownRight();
	void MoveUpLeft();
	void MoveDownLeft();
	void RegulatePosition();
	void LaunchShot();
	//bool is_last_collided_with(OffensiveID given_enemy_bullet_id);
	bool IsLastCollidedWithBullet(BulletID given_enemy_bullet_id);
	bool IsLastCollidedWithLaser(LaserID given_enemy_laser_id);
	bool IsLastCollidedWithCharacter(CharacterID given_enemy_character_id);
	Collision<CharacterID>& GetLastCollision(CharacterID given_enemy_character_id);
	Collision<LaserID>& GetLastCollision(LaserID given_enemy_laser_id);

	static const int INITIAL_POSITION_X;
	static const int INITIAL_POSITION_Y;
	static const int INITIAL_HP;
	static const unsigned int COLLIDANT_SIZE;
	static const double SLOW_MOVE_SPEED_EXTRATE;
	static const unsigned int BLINK_LIGHT_ON_DURATION;	// 被ダメージ時の点滅の点灯時間長
	static const unsigned int BLINK_LIGHT_OFF_DURATION;	// 被ダメージ時の点滅の消灯時間長
	static const unsigned int BLINK_DURATION;			// 被ダメージ時の点滅時間長
	static const unsigned int INVINCIBLE_DURATION;		// 被ダメージ時の無敵猶予時間長
public:
	bool isInvincible;
	static bool LAUNCH_SUSPENDED_FLAG;
	static bool SLOWMOVE_FLAG;
	virtual ~MyCharacter() {}
	void Update();
	void RespondToKeyInput();
	virtual void GetDamaged() override;
	//bool is_collided_with_enemy_offensives();
	void DealCollision();
	void InitializePosition();
	void ReserveInvincible(int invincible_time);
	void Crash();
	static const unsigned int CRASH_EFFECT_VISIBLE_DURATION; // ミリ秒
};