#include "BulletManager.h"
#include "objectManager.h"
BulletManager::BulletManager(ObjectTag usetTag)
{
	for (int i = 0; i < MaxBulletNum; i++)
	{
		bullet[i] = new Bullet(usetTag);
		ObjectManager::Entry(bullet[i]);
	}
}

BulletManager::~BulletManager()
{
	for (auto* ver : bullet)
	{
		ver->~Bullet();
		ver = nullptr;
	}
}

void BulletManager::Init()
{
	for (auto* ver : bullet)
	{
		ver->Init();
	}
}

void BulletManager::Generate(VECTOR pos, VECTOR dir)
{
	for (int i = 0; i < MaxBulletNum; i++)
	{
		if (!bullet[i]->GetPermitUpdate())
		{
			bullet[i]->Generate(pos, dir);
			break;
		}
	}
}
