#pragma once
#include "foundation.h"
#include "Bullet.h"
class EnemyBulletManager
{
public:
	EnemyBulletManager(ObjectTag tag);
	~EnemyBulletManager();
	void Update(VECTOR& pos, VECTOR& dir, float deltaTime);
private:
	ObjectTag userTag;
	Bullet* bullet[5];
	const int bulletNum = 5;
	float shotTime;
	const float ShotIntervalTime = 1.0f;// ŽËŒ‚ŠÔŠu.
};

