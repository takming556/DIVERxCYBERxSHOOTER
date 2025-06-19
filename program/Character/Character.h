#pragma once
#include <memory>
#include "DxLib.h"
#include "enum.h"
#include "CollideRealm/CollideCircle.h"
#include "Position/InFieldPosition.h"

using std::unique_ptr;


class Character {
protected:
	LONGLONG lastUpdatedClock;
	Character(
		enum CharacterID givenId,
		double initPosX,
		double initPosY,
		int initHp,
		unique_ptr<CollideCircle> givenCollidant
	);
public:
	int hp;
	enum CharacterID id;
	unique_ptr<InFieldPosition> position;
	unique_ptr<CollideCircle> collidant;
	virtual void Update() = 0;
	void DrawHp();
	bool IsDead() const;
	virtual void GetDamaged() = 0;
	virtual void Draw() = 0;
	~Character();
};