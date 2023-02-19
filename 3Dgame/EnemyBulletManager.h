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
	ObjectTag userTag;// ©•ª‚Ìƒ^ƒO.
	Bullet* bullet[5];
	const int bulletNum = 5;// Å‘å”­Ë”.
	float shotTime;
	static const float ShotIntervalTime;// ËŒ‚ŠÔŠu.
};

