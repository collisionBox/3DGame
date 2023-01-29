#include "EnemyCannon.h"

EnemyCannon::EnemyCannon(VECTOR bodyPos, VECTOR bodyDir, const char* failName)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	string str = "enemyCannon.mv1";
	modelHandle = AssetManager::GetMesh(failName + str);
	MV1SetScale(modelHandle, moveModelScale);

	bulletManager = new EnemyBulletManager(ObjectTag::Enemy);

	// �ʒu�E������������.
	pos = bodyPos;
	pos.y = 0.5f;
	dir = bodyDir;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// �ϐ��̏�����.
	rotateNow = false;
	aimDir = dir;
}

EnemyCannon::~EnemyCannon()
{
	AssetManager::DeleteMesh(modelHandle);
}

void EnemyCannon::Update(float deltaTime)
{
	
}

void EnemyCannon::Updateeeee(VECTOR& bodyPos, float deltaTime)
{
	// aimDir��Player���W���Q��
	ObjectBase* Player = ObjectManager::GetFirstObject(ObjectTag::Player);
	aimDir = VSub(Player->GetPos(), pos);
	aimDir.y = 0.0f;
	aimDir = VNorm(aimDir);

	Rotate();

	pos = bodyPos;
	dir = VNorm(dir);
	// 3D���f���̃|�W�V�����ݒ�.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	bulletManager->Update(pos, dir, deltaTime);
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
