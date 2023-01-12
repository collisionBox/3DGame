#include "BulletManager.h"

const float BulletManager::ShotIntervalTime = 1.0f;
BulletManager::BulletManager(int inputState):
	ObjectBase(ObjectTag::BulletManager)
{
	shotTime = 0.0f;
	for (int i = 0; i < bulletNum; i++)
	{
		bullet[i] = nullptr;
	}
	padInput = inputState;
}

BulletManager::~BulletManager()
{
	for (int i = 0; i < bulletNum; i++)
	{
		delete bullet[i];
		bullet[i] = nullptr;
	}
}

void BulletManager::Update(float deltaTime)
{

	shotTime -= deltaTime;
	Input();
	
	for (int i = 0; i < bulletNum; i++)
	{
		if (bullet[i] != nullptr)
		{
			VECTOR checkPos = bullet[i]->GetPos();
			if (ConvWorldPosToScreenPos(checkPos).x > 1920)
			{
				SetAlive(false);
				
			}
		}
	}
}

void BulletManager::Input()
{
	GetJoypadXInputState(padInput, &pad);
	if (shotTime < 0.0f)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			for (int i = 0; i < bulletNum; i++)
			{
				if (bullet[i] == nullptr)
				{
					bullet[i] = new Bullet();
					ObjectManager::Entry(bullet[i]);
					shotTime = shotIntervalTime;
					break;
				}
			}
		}

	}
	
}
