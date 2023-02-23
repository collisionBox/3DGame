#pragma once
#include "ObjectBase.h"
#include "Bullet.h"
class BulletManager 
{
public:
	BulletManager(ObjectTag tag, int inputState);
	~BulletManager();
	void Update(VECTOR pos, VECTOR dir, float deltaTime);
	void Input(VECTOR pos, VECTOR dir);
private:
	Bullet* bullet[5];
	const int bulletNum = 5;// Å‘å”­Ë”.
	const float shotIntervalTime = 1.0f;// ËŒ‚ŠÔŠu.
	float shotTime;
	
	int padInput;
	XINPUT_STATE pad;
	ObjectTag userTag;
};

