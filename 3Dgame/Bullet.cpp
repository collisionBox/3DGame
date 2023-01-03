#include "Bullet.h"
#include "AssetManager.h"
#include "Math.h"

PlayerCannon* PlayerCannon::instance = nullptr;

const float Bullet::speed = 300.0f;


Bullet::Bullet() :
	ObjectBase(ObjectTag::Bullet)
	
{
	// モデルのロード.
	modelHandle = MV1LoadModel("data/beam.mv1");
	duplicateModel = MV1DuplicateModel(modelHandle);
	MV1SetScale(duplicateModel, VGet(0.1f, 0.1f, 0.1f));// サイズの変更.
	visible = false;

	PlayerCannon::CreateInstance();
}

Bullet::~Bullet()
{
	MV1DeleteModel(duplicateModel);
	AssetManager::DeleteMesh(modelHandle);
	PlayerCannon::DereteInstance();
}

void Bullet::Initialize(class PlayerCannon* cannon)
{
	visible = true;
	pos = cannon->GetPos();
	dir = cannon->GetDir();
}

void Bullet::Update(float deltaTime)
{
	Input();
}

void Bullet::Draw()
{
	MV1DrawModel(duplicateModel);
}

void Bullet::Input()
{
	
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		visible = true;
		pos = PlayerCannon::Instance().GetPos();
		dir = PlayerCannon::Instance().GetDir();
		
	}
}

