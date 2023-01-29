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

	void Update(float deltaTime);// Ç≤Ç‹Ç©Ç∑óp.
	void Updateeeee(VECTOR& bodyPos, float deltaTime);// Ç∑ÇËë÷Ç¶ÇƒÇ®Ç¢ÇΩÇÃÇ≥ÅI
	void Draw();
private:
	void Rotate();
	class EnemyBulletManager* bulletManager;
	VECTOR aimDir;
	bool rotateNow;
	ObjectTag tag;
};

