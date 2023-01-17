#include "EnemyCannon.h"

EnemyCannon::EnemyCannon(EnemyBody* body, ObjectTag userTag, ObjectTag myTag):
	ObjectBase(myTag)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/enemy/enemyCannon.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));

	// �ʒu�E������������.
	pos = body->GetPos();
	pos.y = 0.5f;
	dir = body->GetDir();
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// �ϐ��̏�����.
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

	// aimDir��Player���W���Q��
	ObjectBase* Player = ObjectManager::GetFirstObject(ObjectTag::Body);
	aimDir = VSub(Player->GetPos(), pos);
	aimDir.y = 0.0f;
	aimDir = VNorm(aimDir);

	Rotate();

	dir = VNorm(dir);
	pos = body->GetPos();
	// 3D���f���̃|�W�V�����ݒ�.
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
			//��]������.
			VECTOR interPolateDir;
			interPolateDir = RotateForAimVecYAxis(dir, aimDir, 0.5f);

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
