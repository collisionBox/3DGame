#pragma once
#include "ObjectBase.h"
#include "Bullet.h"
class BulletManager 
{
public:
	BulletManager(ObjectTag tag, int inputState);
	~BulletManager();
	void Update(float deltaTime);
	void Input(VECTOR pos, VECTOR dir);
private:
	Bullet* bullet[5];
	const int bulletNum = 5;
	const float shotIntervalTime = 1.0f;
	float shotTime;
	
	int padInput;
	XINPUT_STATE pad;
	ObjectTag userTag;
};

