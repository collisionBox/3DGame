#pragma once
#include "foundation.h"
#include "EnemyBody.h"
#include "EnemyCannon.h"
#include "EnemyBulletManager.h"
class Enemy :
	public ObjectBase
{
public:
	Enemy(VECTOR initPos, VECTOR initDir);
	~Enemy();

	void Update(float deltaTime);
	void Draw();
	void OnCollisionEnter();

private:
	void Input();
	class EnemyBody* body;
	class EnemyCannon* cannon;

	VECTOR velocity;
	
};

