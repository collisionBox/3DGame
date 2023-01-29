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

	void Update(float deltaTime);// ごまかす用.
	void Updateeeee(VECTOR& bodyPos, float deltaTime);// すり替えておいたのさ！
	void Draw();
private:
	void Rotate();
	class EnemyBulletManager* bulletManager;
	VECTOR aimDir;
	bool rotateNow;
	ObjectTag tag;
};

