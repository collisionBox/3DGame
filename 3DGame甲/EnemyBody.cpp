#include "EnemyBody.h"
#include "AssetManager.h"
#include "ObjectTag.h"
#include "SystemConstant.h"
#include "ObjectManager.h"
EnemyBody::EnemyBody(VECTOR initPos, VECTOR initDir):ObjectBase(ObjectTag::Enemy)
{
	modelHandle = AssetManager::GetMesh("data/enemy/enemyBody.mv1");
	if (modelHandle == -1)
	{
		printfDx("EnemyBody��ǂݍ��߂܂���");
	}
	MV1SetScale(modelHandle, MoveModelScale);

	// �ʒu�E������������.
	this->initPos = initPos;
	this->initDir = initDir;
	Initialize();
	cannon = new EnemyCannon(pos, dir, ObjectTag::Enemy);
	//ObjectManager::Entry(cannon);
	
	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = ColRadius;

}

void EnemyBody::Initialize()
{
	pos = initPos;
	dir = initDir;
	HP = MaxHP;

	// �ύX�̔��f.
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

}

void EnemyBody::Update(float deltaTime)
{
	cannon->Updateeeee(pos, deltaTime);
}

void EnemyBody::Draw()
{
	MV1DrawModel(modelHandle);
	cannon->Draw();
}
