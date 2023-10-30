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
		printfDx("EnemyBodyを読み込めません");
	}
	MV1SetScale(modelHandle, MoveModelScale);

	// 位置・方向を初期化.
	this->initPos = initPos;
	this->initDir = initDir;
	Initialize();
	cannon = new EnemyCannon(pos, dir, ObjectTag::Enemy);
	//ObjectManager::Entry(cannon);
	
	// 当たり判定球セット.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = ColRadius;

}

void EnemyBody::Initialize()
{
	pos = initPos;
	dir = initDir;
	HP = MaxHP;

	// 変更の反映.
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
