#include "EnemyBody.h"

// �ÓI�萔.

int EnemyBody::corner = 0;
EnemyBody::EnemyBody(VECTOR initPos, VECTOR initDir, const char* failName):
	ObjectBase(ObjectTag::Enemy)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	string str = "enemyBody.mv1";
	modelHandle = AssetManager::GetMesh(failName + str);
	MV1SetScale(modelHandle, moveModelScale);

	cannon = new EnemyCannon(initPos, initDir, failName);

	// �ʒu�E������������.
	// �����֔z�u.
	pos = initPos;// (�n�ʂɂ��܂邽��13�グ��.)����͖���
	// ���S������.
	dir = initDir;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.worldCenter.y = 0;
	colSphere.radius = 32.0f;

	// �ϐ��̏�����.
	velocity = initVec;
	rotateNow = false;
	accel = 0;
	time = 2;
	rand = GetRand(6);
}

EnemyBody::~EnemyBody()
{
	AssetManager::DeleteMesh(modelHandle);
	delete cannon;
}

void EnemyBody::Update(float deltaTime)
{
	
	MoveMethod(deltaTime);
	Rotate(10);

	dir = VNorm(dir);// ���K��.

	velocity = VScale(dir, accel);
	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);

	// �|�W�V�����X�V.
	pos = VAdd(pos, VScale(velocity, deltaTime));


	if (pos.x > 930.0f)//-885,13,159
	{
		pos = VGet(-920.0f, pos.y, pos.z);//920
	}
	if (pos.x < -930.0f)//882,13,88
	{
		pos = VGet(920.0f, pos.y, pos.z);
	}
	if (pos.z > 540)//540
	{
		pos = VGet(pos.x, pos.y, -530.0f);
	}
	if (pos.z < -540)//540
	{
		pos = VGet(pos.x, pos.y, 530.0f);
	}

	// 3D���f���̃|�W�V�����ݒ�.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	
	cannon->Updateeeee(pos, deltaTime);

	CollisionUpdate();
}



void EnemyBody::Draw()
{
	MV1DrawModel(modelHandle);
	cannon->Draw();
	DrawCollider();

}

void EnemyBody::OnCollisionEnter(const ObjectBase* other)
{

}

void EnemyBody::MoveMethod(float deltaTime)
{
	time -= deltaTime;
	if (time < 0 && !rotateNow)
	{
		rotateNow = true;
		aimDir = VScale(dir, -1);
	}
	if (time < 0)
	{
		rand = GetRand(6);
		time = 4;
	}

	if (VDot(velocity, dir) <= MaxSpeed && rand < 5)
	{
		accel += Accel;
	}
	if (rand == 5)
	{
		accel = 0;
	}
	if (VDot(velocity, dir) >= MinSpeed && rand == 6)
	{
		accel -= Back;
	}
	
}

void EnemyBody::Rotate(float degree)
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
			interPolateDir = RotateForAimVecYAxis(dir, aimDir, degree);

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
