#include "BulletManager.h"

BulletManager::BulletManager(ObjectTag tag, int inputState)
{
	shotTime = 0.0f;
	Initialize();
	padInput = inputState;
	userTag = tag;
}

void BulletManager::Initialize()
{
	for (int i = 0; i < bulletNum; i++)
	{
		bullet[i] = nullptr;
	}
}

BulletManager::~BulletManager()
{
	// ObjectManager::ReleseAllObj‚Å‰ð•ú.
}

void BulletManager::Update(VECTOR pos, VECTOR dir, float deltaTime)
{
	shotTime -= deltaTime;
	for (int i = 0; i < bulletNum; i++)
	{
		if (bullet[i] != nullptr && !bullet[i]->GetVisible())
		{
			bullet[i] = nullptr;
		}
	}
	
}

void BulletManager::Input(VECTOR pos, VECTOR dir, XINPUT_STATE pad)
{	
		if (shotTime < 0 && (CheckHitKey(KEY_INPUT_SPACE) || pad.Buttons[9]))
		{
			shotTime = shotIntervalTime;
			for (int i = 0; i < bulletNum; i++)
			{
				if (bullet[i] == nullptr)
				{
					bullet[i] = new Bullet(pos, dir, userTag);
					ObjectManager::Entry(bullet[i]);
					break;
				}
			}
		}

	
	
}


