#include "PlayerCannon.h"
#include "AssetManager.h"
#include "ObjectManager.h"
#include "PlayerBody.h"
#include "Math.h"

PlayerCannon::PlayerCannon() :
	modelHandle(-1)
	,pos()
	,dir()
	,a()
{
	modelHandle = AssetManager::GetMesh("data/player/reconTankCannon.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));
}

PlayerCannon::~PlayerCannon()
{
	AssetManager::DeleteMesh(modelHandle);
}

void PlayerCannon::Initialize(VECTOR pos, VECTOR dir)
{
	this->pos = pos;
	this->pos.y = 0.5f;
	this->dir = dir;
	
}


void PlayerCannon::Update(VECTOR pos, float deltaTime)
{
	

	if (CheckHitKey(KEY_INPUT_O))
	{
		a = VAdd(a, VGet(0.0f, 0.1f, 0.0f));
	}
	if (CheckHitKey(KEY_INPUT_L))
	{
		a = VSub(a, VGet(0.0f, 0.1f, 0.0f));
	}
	this->pos = pos;

	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void PlayerCannon::Draw()
{
	MV1DrawModel(modelHandle);
}

void PlayerCannon::Input()
{
}

