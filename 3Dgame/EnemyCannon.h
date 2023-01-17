#pragma once
#include "foundation.h"
#include "EnemyBody.h"
class EnemyCannon:
	public ObjectBase
{
public:
	EnemyCannon(class EnemyBody* body, ObjectTag userTag, ObjectTag myTag);
	~EnemyCannon();

	void Update(float deltaTime);
	void Draw();
private:
	void Rotate();
	VECTOR aimDir;
	bool rotateNow;
	ObjectTag tag;
};

