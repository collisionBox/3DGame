#include "EnemyBody.h"
#include "AssetManager.h"
#include "ObjectTag.h"
#include "SystemConstant.h"

EnemyBody::EnemyBody(VECTOR initPos, VECTOR initDir):ObjectBase(ObjectTag::Enemy)
{
	modelHandle = AssetManager::GetMesh("date/enemy/enemyBody.mv1");
	if (modelHandle == -1)
	{
		printfDx("EnemyBodyを読み込めません");
	}
	MV1SetScale(modelHandle, MoveModelScale);

	// 位置・方向を初期化.
	pos = initPos;
	dir = initDir;
	HP = 1;
	//Initialize();

	// 当たり判定球セット.
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
