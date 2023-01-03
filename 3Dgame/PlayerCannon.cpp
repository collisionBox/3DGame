#include "PlayerCannon.h"
#include "AssetManager.h"
#include "ObjectManager.h"
#include "ObjectBase.h"
#include "PlayerBody.h"
#include "Camera.h"
#include "Math.h"
#if 0
PlayerCannon::PlayerCannon() :
	modelHandle(-1)
{
	modelHandle = AssetManager::GetMesh("data/player/reconTankCannon.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));
	
}
#else
PlayerCannon::PlayerCannon() :
	ObjectBase(ObjectTag::Cannon)
{
	modelHandle = AssetManager::GetMesh("data/player/reconTankCannon.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));

}
#endif
PlayerCannon::~PlayerCannon()
{
	AssetManager::DeleteMesh(modelHandle);
}

void PlayerCannon::CreateInstance()
{
	if (!instance)
	{
		instance = new PlayerCannon;
	}
}

void PlayerCannon::DereteInstance()
{
	delete instance;
	instance = nullptr;
}

void PlayerCannon::Initialize(VECTOR bodyPos, VECTOR bodyDir)
{
	pos = bodyPos;
	pos.y = 0.5f;
	dir = bodyDir;
	
}

#if 0
void PlayerCannon::Update(VECTOR bodyPos,VECTOR camDir, float deltaTime)
{
	
	/*if (CheckHitKey(KEY_INPUT_A))
	{
		
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, 0.3));
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, 0.3));
	}*/
	
	VECTOR cameraFront = camDir;
	cameraFront.y = 0.0f;
	/*if (GetRightDir(cameraFront))
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		
		dir = VAdd(dir, VScale(right, 0.1));
	}
	else
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, 0.3));
	}*/
	dir = cameraFront;
	VNorm(dir);

	pos = bodyPos;

	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}
#else
void PlayerCannon::Update(float deltaTime)
{
	VECTOR cameraFront = camDir;
	cameraFront.y = 0.0f;
	dir = cameraFront;
	VNorm(dir);

	pos = bodyPos;

	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

#endif
void PlayerCannon::Draw()
{
	MV1DrawModel(modelHandle);
}

void PlayerCannon::Input()
{
}


bool PlayerCannon::GetRightDir(VECTOR camDir)
{
	float cross = (dir.x - camDir.x) - (dir.z - camDir.z);
	return cross > 0.0f;
}

