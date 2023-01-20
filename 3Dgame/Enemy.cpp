#include "Enemy.h"

Enemy::Enemy(VECTOR initPos, VECTOR initDir):
	ObjectBase(ObjectTag::Enemy)
{
	body = new EnemyBody(initPos, initDir);
	
	//cannon = new EnemyCannon(body, ObjectTag::EBody, ObjectTag::ECannon);
	
}

Enemy::~Enemy()
{
	delete body;
	delete cannon;
}

void Enemy::Update(float deltaTime)
{
	body->Update(deltaTime);
	cannon->Update(deltaTime);
}

void Enemy::Draw()
{
	body->Draw();
	cannon->Draw();

}

void Enemy::Input()
{
}

void Enemy::OnCollisionEnter()
{
	
}

