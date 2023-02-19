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
	ObjectTag userTag;// �����̃^�O.
	Bullet* bullet[5];
	const int bulletNum = 5;// �ő唭�ː�.
	float shotTime;
	static const float ShotIntervalTime;// �ˌ��Ԋu.
};

