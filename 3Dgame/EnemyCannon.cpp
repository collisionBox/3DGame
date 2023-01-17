#include "EnemyCannon.h"

EnemyCannon::EnemyCannon(EnemyBody* body, ObjectTag userTag, ObjectTag myTag):
	ObjectBase(myTag)
{
	// アセットマネージャーからモデルをロード.
	modelHandle = AssetManager::GetMesh("data/enemy/enemyCannon.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));

	// 位置・方向を初期化.
	pos = body->GetPos();
	pos.y = 0.5f;
	dir = body->GetDir();
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// 変数の初期化.
	rotateNow = false;
	aimDir = dir;
	tag = userTag;
}

EnemyCannon::~EnemyCannon()
{
	AssetManager::DeleteMesh(modelHandle);
}

void EnemyCannon::Update(float deltaTime)
{
	ObjectBase* body = ObjectManager::GetFirstObject(tag);

	// aimDirにPlayer座標を参照
	ObjectBase* Player = ObjectManager::GetFirstObject(ObjectTag::Body);
	aimDir = VSub(Player->GetPos(), pos);
	aimDir.y = 0.0f;
	aimDir = VNorm(aimDir);

	Rotate();

	dir = VNorm(dir);
	pos = body->GetPos();
	// 3Dモデルのポジション設定.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void EnemyCannon::Draw()
{
	MV1DrawModel(modelHandle);
}

void EnemyCannon::Rotate()
{
	if (IsNearAngle(aimDir,dir))
	{
		dir = aimDir;
	}
	else
	{
		rotateNow = true;
	}

	if (rotateNow)
	{

		if (IsNearAngle(aimDir, dir))
		{
			dir = aimDir;
			rotateNow = false;
		}
		else
		{
			//回転させる.
			VECTOR interPolateDir;
			interPolateDir = RotateForAimVecYAxis(dir, aimDir, 0.5f);

			// 回転が目標角を超えていないか.
			VECTOR cross1, cross2;
			cross1 = VCross(dir, aimDir);
			cross2 = VCross(interPolateDir, aimDir);

			// 目標角度を超えたら終了.
			if (cross1.y * cross2.y < 0.0f)
			{
				interPolateDir = aimDir;
				rotateNow = false;
			}
			// 目標ベクトルに１０度だけ近づけた角度
			dir = interPolateDir;
		}
	}
}
