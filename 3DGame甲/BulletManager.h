#pragma once
#include "DxLib.h"
#include "Bullet.h"
class BulletManager
{
public:
	BulletManager(ObjectTag usetTag);
	~BulletManager();
	void Init();
	void Generate(VECTOR pos, VECTOR dir);
private:
	const int MaxBulletNum = 5;
	Bullet* bullet[5];
};

