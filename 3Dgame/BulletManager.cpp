#include "BulletManager.h"

const float BulletManager::ShotIntervalTime = 1.0f;
BulletManager::BulletManager(ObjectTag tag, int inputState):
	ObjectBase(ObjectTag::BulletManager)
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
	Input();
	
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

void BulletManager::Input()
{
	GetJoypadXInputState(padInput, &pad);

		if (shotTime < 0.0f && (CheckHitKey(KEY_INPUT_SPACE) || pad.Buttons[6]))
		{
			for (int i = 0; i < bulletNum; i++)
			{
				if (bullet[i] == nullptr)
				{
					bullet[i] = new Bullet(userTag);
					ObjectManager::Entry(bullet[i]);
					shotTime = shotIntervalTime;
					break;
				}
			}
		}

	
	
}
