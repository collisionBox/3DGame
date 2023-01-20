#include "EnemyBody.h"

// �ÓI�萔.
const float EnemyBody::Accel = 6.0f;// �ʏ�̉���.
const float EnemyBody::Back = 5.0f;// ��ޑ��x.
const float EnemyBody::MaxSpeed = 200.0f;// �ō��O�i���x.
const float EnemyBody::MinSpeed = -350.0f;// �ō���ޑ��x.
const float EnemyBody::DefaultDecel = 0.97f;// �Ȃɂ����Ȃ����̌���.
const float EnemyBody::BreakDecel = 0.5f;// �u���[�L���̌���.
const float EnemyBody::GripDecel = -5.0f;// �O���b�v�̌���.
const float EnemyBody::GripPower = 2.0f;// �O���b�v��.
const float EnemyBody::ColideDecelFac = 4.0f;// ��Q���ɂԂ������Ƃ��̌�����.
const float EnemyBody::TurnPerformance = 5.0f;// ���񐫔\.

EnemyBody::EnemyBody(VECTOR initPos, VECTOR initDir):
	ObjectBase(ObjectTag::Enemy)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/enemy/enemyBody.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));

	cannon = new EnemyCannon(initPos, initDir);

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
	time = 4;
}

EnemyBody::~EnemyBody()
{
	AssetManager::DeleteMesh(modelHandle);
	delete cannon;
}

void EnemyBody::Update(float deltaTime)
{
	/*if (VDot(velocity, dir) <= MaxSpeed)
	{
		accel += Accel;
	}*/

	time -= deltaTime;
	if (time < 0 && !rotateNow)
	{
		time = 3;
		rotateNow = true;
		aimDir = VScale(dir, -1);
	}

	Rotate(10);

	dir = VNorm(dir);// ���K��.

	velocity = VScale(dir, accel);
	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);

	// �|�W�V�����X�V.
	pos = VAdd(pos, VScale(velocity, deltaTime));

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
