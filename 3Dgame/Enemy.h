#pragma once
#include "foundation.h"
#include "EnemyBody.h"
#include "EnemyCannon.h"
#include "EnemyBulletManager.h"
class Enemy
{
public:
	Enemy(VECTOR initPos, VECTOR initDir)
	{
		EnemyBody* body = new EnemyBody(initPos, initDir);
		ObjectManager::Entry(body);

		EnemyCannon* cannon = new EnemyCannon(body, ObjectTag::EBody, ObjectTag::ECannon);
		ObjectManager::Entry(cannon);

		EnemyBulletManager* bullet = new EnemyBulletManager(ObjectTag::ECannon);
		ObjectManager::Entry(bullet);
		
	}

	
};

