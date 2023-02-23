#include "EnemyBulletManager.h"

EnemyBulletManager::EnemyBulletManager(ObjectTag tag)
{
	shotTime = ShotIntervalTime;
	for (int i = 0; i < bulletNum; i++)
	{
		bullet[i] = nullptr;
	}

	userTag = tag;
}

EnemyBulletManager::~EnemyBulletManager()
{
	// ˆ—‚È‚µ.
}

void EnemyBulletManager::Update(VECTOR& pos, VECTOR& dir, float deltaTime)
{
	shotTime -= deltaTime;
	for (int i = 0; i < bulletNum; i++)
	{
		if (shotTime <= 0 && bullet[i] == nullptr)
		{
			bullet[i] = new Bullet(pos, dir, userTag);
			ObjectManager::Entry(bullet[i]);
			shotTime = ShotIntervalTime;
			break;
		}
	}


}
