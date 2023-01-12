#pragma once
#include "ObjectBase.h"
#include "Bullet.h"
class BulletManager :
	public ObjectBase
{
public:
	BulletManager(int inputState);
	~BulletManager();
	void Update(float deltaTime);
	void Input();
private:
	bool aliveFlag;
	Bullet* bullet[5];
	const int bulletNum = 5;
	const float shotIntervalTime = 1.0f;
	float shotTime;
	static const float ShotIntervalTime;
	int padInput;
	XINPUT_STATE pad;
};

