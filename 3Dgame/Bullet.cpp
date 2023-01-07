#include "Bullet.h"
#include "AssetManager.h"
#include "Math.h"


const float Bullet::speed = 300.0f;


Bullet::Bullet(ObjectBase* cannon) :
	ObjectBase(ObjectTag::Bullet)
{

	// モデルのロード.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));// サイズの変更.

	//alive = false;
	visible = false;
	pos = cannon->GetPos();
	dir = cannon->GetDir();
	velocity = initVec;
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

Bullet::~Bullet()
{
	AssetManager::DeleteMesh(modelHandle);

}

void Bullet::Update(float deltaTime)
{
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
}
