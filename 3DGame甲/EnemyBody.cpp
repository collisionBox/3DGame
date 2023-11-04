#include "EnemyBody.h"
#include "AssetManager.h"
#include "ObjectTag.h"
#include "SystemConstant.h"
#include "ObjectManager.h"
#include "BreakExplosion.h"
#include "EffectManager.h"

EnemyBody::EnemyBody(VECTOR initPos, VECTOR initDir, int enemyNo):ObjectBase(ObjectTag::Enemy)
{
	modelHandle = AssetManager::GetMesh("data/enemy/enemyBody.mv1");
	if (modelHandle == -1)
	{
		printfDx("EnemyBody��ǂݍ��߂܂���");
	}
	MV1SetScale(modelHandle, MoveModelScale);

	// �ʒu�E������������.
	this->initPos = initPos;
	this->initDir = initDir;
	Initialize();
	cannon = new EnemyCannon(pos, dir, ObjectTag::Enemy);
	
	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = ColRadius;
	number = enemyNo;
}

void EnemyBody::Initialize()
{
	pos = initPos;
	dir = initDir;
	
	HP = MaxHP;
	velocity = InitVec;
	aimDir = dir;
	rotateNow = false;
	breakEffect = nullptr;
	hitBgObj = false;
	// �ύX�̔��f.
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

}

void EnemyBody::Update(float deltaTime)
{
	switch (number)
	{
	case 1:
		Behavioral1(deltaTime);
		break;
	case 2:
		Behavioral2(deltaTime);
		break;
	case 3:
		Begavioral3(deltaTime);
		break;
	default:
		Behavioral1(deltaTime);
		break;
	}
	
	Rotate(deltaTime);
	
	if (HP <= 0.0f)
	{
		if (breakEffect == nullptr)
		{
			breakEffect = new BreakExplosion(pos, dir);
			EffectManager::Entry(breakEffect);
			visible = false;
		}
		else if (!breakEffect->IsPlayNow())
		{
			SetAlive(false);
			breakEffect->DeletionPermission();
		}
	}
	else
	{
		cannon->Updateeeee(pos, deltaTime);
	}
	// �ύX�̔��f.
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir , VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void EnemyBody::Draw()
{
	MV1DrawModel(modelHandle);
	cannon->Draw();
	//DrawCollider();
}

void EnemyBody::Rotate(float deltaTIme)
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
			interPolateDir = RotateForAimVecYAxis(dir, aimDir, Omega * deltaTIme);

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

void EnemyBody::OnCollisionEnter(const ObjectBase* other)
{
	ObjectTag tag = other->GetTag();
	// �w�i
	if (tag == ObjectTag::BackGround)
	{
		int colModel = other->GetCollisionModel();

		MV1_COLL_RESULT_POLY_DIM colInfo;
		if (CollisionPair(colSphere, colModel, colInfo))
		{
			// �������Ă���ꍇ�͉����ʂ��v�Z.
			VECTOR poshBuckVec = CalcSpherePushBackVecFromMesh(colSphere, colInfo);
			pos = VAdd(pos, poshBuckVec);

			// �R���W�������̉��.
			MV1CollResultPolyDimTerminate(colInfo);

			CollisionUpdate();
			hitBgObj = true;
		}
		else
		{
			hitBgObj = false;
		}
	}
	// �e.
	if (tag == ObjectTag::Bullet)
	{
		Sphere colSphere = other->GetCollisionSphere();
		if (CollisionPair(this->colSphere, colSphere))
		{
			HP = 0;
		}
	}


}
void EnemyBody::Behavioral1(float deltaTime)
{
	// �����Ȃ����ߏ����Ȃ�.
}
void EnemyBody::Behavioral2(float deltaTime)
{
	// �����x�N�g���ɉ����͂������ĉ����x�N�g���Ƃ���.
	velocity = VScale(dir * -1, accel);

	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);

	// �\���|�W�V�����X�V.
	prevPos = VAdd(pos, VScale(velocity, deltaTime));

	// ��ʊO����.
	if (offscreenDicision(prevPos, colSphere.radius))
	{
		if (!rotateNow)
		{
			
			aimDir *= -1;
			
			rotateNow = true;
		}

		velocity = InitVec;
		CollisionUpdate();
		prevPos = pos;
	}
	// �����蔻�苅�̈ʒu�X�V.
	CollisionUpdate(prevPos);

	// �|�W�V�����X�V.
	pos = prevPos;

	// ��������.
	if (accel <= MaxSpeed)
	{
		accel += Accel;
	
	}
	if (hitBgObj)
	{
		if (accel > 0)
		{
			accel = 0;
		}
		if (!rotateNow)
		{
			MATRIX rotYMat = MGetRotY(ToRadian(rollingDegree));
			aimDir = VTransform(aimDir, rotYMat);
			if (GetRand(2) == 0)
			{
				aimDir *= -1;
			}
			rotateNow = true;
		}

		velocity = InitVec;
	}
}

void EnemyBody::Begavioral3(float deltaTime)
{
	// �����x�N�g���ɉ����͂������ĉ����x�N�g���Ƃ���.
	velocity = VScale(dir * -1, accel);

	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);

	// �\���|�W�V�����X�V.
	prevPos = VAdd(pos, VScale(velocity, deltaTime));

	// ��ʊO����.
	if (offscreenDicision(prevPos, colSphere.radius))
	{
		accel = 0;
		if (!rotateNow)
		{
			aimDir *= -1;
			rotateNow = true;
		}

		velocity = InitVec;
		CollisionUpdate();
		prevPos = pos;
	}
	// �����蔻�苅�̈ʒu�X�V.
	CollisionUpdate(prevPos);

	// �|�W�V�����X�V.
	pos = prevPos;

	// ��������.

	if (accel <= MaxSpeed && !rotateNow)
	{
		accel += Accel;

	}
	if (hitBgObj)
	{
		if (accel > 0)
		{
			accel = 0;
		}
		if (!rotateNow)
		{
			MATRIX rotYMat = MGetRotY(ToRadian(rollingDegree));
			aimDir = VTransform(aimDir, rotYMat);
			if (GetRand(2) == 0)
			{
				aimDir *= -1;
			}
			rotateNow = true;
		}

		velocity = InitVec;
	}
}
