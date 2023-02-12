#include "BulletManager.h"

BulletManager::BulletManager(ObjectTag tag, int inputState)
{
	shotTime = 0.0f;
	for (int i = 0; i < bulletNum; i++)
	{
		bullet[i] = nullptr;
	}
	padInput = inputState;
	userTag = tag;
}

BulletManager::~BulletManager()
{
	// ObjectManager::ReleseAllObj‚Å‰ð•ú.
}

void BulletManager::Update(float deltaTime)
{

	shotTime -= deltaTime;
	
}

void BulletManager::Input(VECTOR pos, VECTOR dir)
{
	GetJoypadXInputState(padInput, &pad);
	
		if ((CheckHitKey(KEY_INPUT_SPACE) || pad.Buttons[9]))
		{
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
