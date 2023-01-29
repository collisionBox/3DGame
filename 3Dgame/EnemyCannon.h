#pragma once
#include "foundation.h"
#include "EnemyBody.h"
#include "EnemyBulletManager.h"
class EnemyCannon:
	public ObjectBase
{
public:
	EnemyCannon(VECTOR bodyPos, VECTOR bodyDir, const char* failName);
	~EnemyCannon();

	void Update(float deltaTime);// ���܂����p.
	void Updateeeee(VECTOR& bodyPos, float deltaTime);// ����ւ��Ă������̂��I
	void Draw();
private:
	void Rotate();
	class EnemyBulletManager* bulletManager;
	VECTOR aimDir;
	bool rotateNow;
	ObjectTag tag;
};

