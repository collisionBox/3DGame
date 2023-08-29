#include "EnemyCannon.h"
#include "AssetManager.h"
#include "SystemConstant.h"
EnemyCannon::EnemyCannon(VECTOR initPos, VECTOR initDir, ObjectTag userTag) :
	ObjectBase(ObjectTag::Enemy)
{
	modelHandle = AssetManager::GetMesh("data/enemy/enemyCannon");
	MV1SetScale(modelHandle, MoveModelScale);

	// �ʒu�E������������.
	Initialize(initPos, initDir);
	this->userTag = userTag;

}

void EnemyCannon::Initialize(VECTOR initPos, VECTOR initDir)
{
	// �l�̏�����.
	pos = initPos;
	pos.y = AdjustPos;
	dir = initDir;
	aimDir = InitVec;
	rotateNow = false;

	// �ύX�̔��f.
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

}

EnemyCannon::~EnemyCannon()
{
	AssetManager::DeleteMesh(modelHandle);
}

void EnemyCannon::Updateeeee(VECTOR bodyPos, float deltaTime)
{
	Rotate();
	dir = VNorm(dir);
	pos = bodyPos;

	MV1SetPosition(modelHandle, this->pos);
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
	if (rotateNow)
	{
		if (IsNearAngle(aimDir, dir))
		{
			dir = aimDir;
			rotateNow = false;
		}
		else
		{
			//��]������.
			VECTOR interPolateDir;
			interPolateDir = RotateForAimVecYAxis(dir, aimDir, Omega);

			// ��]���ڕW�p�𒴂��Ă��Ȃ���.
			VECTOR cross1, cross2;
			cross1 = VCross(dir, aimDir);
			cross2 = VCross(interPolateDir, aimDir);

			// �ڕW�p�x�𒴂�����I��.
			if (cross1.y * cross2.y < 0.0f)
			{
				interPolateDir = aimDir;
				rotateNow = false;
			}
			// �ڕW�x�N�g���ɂP�O�x�����߂Â����p�x
			dir = interPolateDir;
		}
	}
}

void EnemyCannon::Radar()
{
	MATRIX rightMat = MGetRotY(RadarRange / 2);
	VECTOR rightEnd = VTransform(dir, rightMat);
	MATRIX leftMat = MGetRotY(-RadarRange / 2);
	VECTOR leftEnd = VTransform(dir, leftMat);
	if (CalcRotationDirectionYAxis()<0 && CalcRotationDirectionYAxis() > 0)
	{
	https://procon.fun/code/fan-shape/
	}
}

void EnemyCannon::Fire()
{
}

