#pragma once
#include "ObjectBase.h"
#include "Bullet.h"
#include "SparkEffect.h"
class BulletManager
{
public:
	BulletManager(ObjectTag tag, int inputState);
	~BulletManager();
	void Update(VECTOR pos, VECTOR dir, float deltaTime);
	void Input(VECTOR pos, VECTOR dir, XINPUT_STATE pad);
	void Initialize();
private:
	class Bullet* bullet[5];
	const int bulletNum = 5;
	const float shotIntervalTime = 1.0f;
	float shotTime;
	
	int padInput;
	ObjectTag userTag;


};

