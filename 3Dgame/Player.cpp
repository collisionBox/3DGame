#include "Player.h"

Player::Player() :
	ObjectBase(ObjectTag::Player)
{
	// �ԑ̐���.
	body = new PlayerBody;
	ObjectManager::Entry(body);

	// ��C����.
	cannon = new PlayerCannon(body);
	ObjectManager::Entry(cannon);

	shotTime = 0.0f;
	for (int i = 0; i < bulletNum; i++)
	{
		bullet[i] = nullptr;
	}
}

Player::~Player()
{
	// �����Ȃ�.
}


void Player::Update(float deltaTime)
{
	body->Update(deltaTime);
	cannon->Update(deltaTime);

	shotTime -= deltaTime;
	if (shotTime < 0.0f && CheckHitKey(KEY_INPUT_SPACE))
	{
		for (int i = 0; i < bulletNum; i++)
		{
			if (bullet[i] == nullptr)
			{
				bullet[i] = new Bullet(cannon);
				ObjectManager::Entry(bullet[i]);
				shotTime = shotIntervalTime;
				break;
			}
		}
	}
}

void Player::Draw()
{
	body->Draw();
	cannon->Draw();
	for (int i = 0; i < bulletNum; i++)
	{
		if (bullet[i] != nullptr)
		{
			bullet[i]->Draw();
		}
	}
}
