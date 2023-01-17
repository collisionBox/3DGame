#include "EnemyBulletManager.h"

const float EnemyBulletManager::ShotIntervalTime = 5.0f;
EnemyBulletManager::EnemyBulletManager(ObjectTag tag):
	ObjectBase(ObjectTag::EBulletManager)
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
	// ObjectManager::ReleseAllObj‚Å‰ð•ú.
}

void EnemyBulletManager::Update(float deltaTime)
{
	shotTime -= deltaTime;
	for (int i = 0; i < bulletNum; i++)
	{
		if (shotTime <= 0 && bullet[i] == nullptr)
		{
			bullet[i] = new Bullet(userTag);
			ObjectManager::Entry(bullet[i]);
			shotTime = ShotIntervalTime;
			break;
		}
	}

	for (int i = 0; i < bulletNum; i++)
	{
		if (bullet[i] != nullptr)
		{ 
			VECTOR checkPos = bullet[i]->GetPos();
			if (ConvWorldPosToScreenPos(checkPos).x < 0 || ConvWorldPosToScreenPos(checkPos).x > 1920 ||
				ConvWorldPosToScreenPos(checkPos).y < 0 || ConvWorldPosToScreenPos(checkPos).y > 1080)
			{
				SetVisible(false);
				bullet[i] = nullptr;
			}

		}
	}

}
