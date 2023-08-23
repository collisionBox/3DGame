#include "EnemyBody.h"
#include "AssetManager.h"
#include "ObjectTag.h"
#include "SystemConstant.h"

EnemyBody::EnemyBody(VECTOR initPos, VECTOR initDir):ObjectBase(ObjectTag::Enemy)
{
	modelHandle = AssetManager::GetMesh("date/enemy/enemyBody.mv1");
	if (modelHandle == -1)
	{
		printfDx("EnemyBody��ǂݍ��߂܂���");
	}
	MV1SetScale(modelHandle, MoveModelScale);

	// �ʒu�E������������.
	pos = initPos;
	dir = initDir;
	HP = 1;
	//Initialize();

	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = ColRadius;

}

void EnemyBody::Initialize()
{
}

void EnemyBody::Update(float deltaTime)
{
}

void EnemyBody::Draw()
{
}
