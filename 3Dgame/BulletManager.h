#pragma once
#include "ObjectBase.h"
#include "Bullet.h"
class BulletManager :
	public ObjectBase
{
public:
	BulletManager(ObjectTag tag, int inputState);
	~BulletManager();
	void Update(float deltaTime);
	void Input();
private:
	Bullet* bullet[5];
	const int bulletNum = 5;
	const float shotIntervalTime = 1.0f;
	float shotTime;
	static const float ShotIntervalTime;
	int padInput;
	XINPUT_STATE pad;
	ObjectTag userTag;
};

