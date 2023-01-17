#pragma once
#include "foundation.h"
#include "Bullet.h"
class EnemyBulletManager :
	public ObjectBase
{
public:
	EnemyBulletManager(ObjectTag tag);
	~EnemyBulletManager();
	void Update(float deltaTime);
private:
	ObjectTag userTag;
	//EnemyBullet* bullet[5];
	Bullet* bullet[5];
	const int bulletNum = 5;
	float shotTime;
	static const float ShotIntervalTime;
};

