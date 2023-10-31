#include "EnemyCannon.h"
#include "AssetManager.h"
#include "SystemConstant.h"
#include "ObjectManager.h"
#include "Bullet.h"
#include "MazzleFlashEffect.h"
#include "EffectManager.h"
#include "PlayerBody.h"
#include <cmath>

EnemyCannon::EnemyCannon(VECTOR initPos, VECTOR initDir, ObjectTag userTag) :
	ObjectBase(ObjectTag::Enemy)
{
	modelHandle = AssetManager::GetMesh("data/enemy/enemyCannon.mv1");
	if (modelHandle == -1)
	{
		printfDx("enemycannon == -1");
	}
	MV1SetScale(modelHandle, MoveModelScale);

	// �ʒu�E������������.
	Initialize(initPos, initDir);
	this->userTag = userTag;

	colType = CollisionType::Line;
	colLine.worldStart = pos;
	colLine.worldEnd = InitVec;
}

void EnemyCannon::Initialize(VECTOR initPos, VECTOR initDir)
{
	// �l�̏�����.
	pos = initPos;
	pos.y = AdjustPos;
	dir = initDir;
	aimDir = dir;
	rotateNow = false;
	jbPlayerPos = InitVec;
	// �ύX�̔��f.
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

}




EnemyCannon::~EnemyCannon()
{
	AssetManager::DeleteMesh(modelHandle);
}

/// <summary>
/// �X�V����.
/// </summary>
/// <param name="bodyPos">�ԑ̈ʒu.</param>
/// <param name="deltaTime"></param>
void EnemyCannon::Updateeeee(VECTOR bodyPos, float deltaTime)
{
	if (shotTime >= 0)
	{
		shotTime -= deltaTime;
	}
	
	DiviationValculation(deltaTime);
	dir = VNorm(dir);
	pos = bodyPos;
	Rotate(deltaTime);
	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	
}

void EnemyCannon::Draw()
{
	MV1DrawModel(modelHandle);
	DrawLine3D(pos, pos + a * 100, Green);
	DrawLine3D(pos, pos + dir*-100, Red);
	
	DrawFormatString(0, 100, Green, "%f %f", leftOrRight, a.x);
}

/// <summary>
/// ���񏈗�.
/// </summary>
/// <param name="deltaTime"></param>
void EnemyCannon::Rotate(float deltaTime)
{
	if (rotateNow)
	{
		if (IsNearAngle(aimDir, dir))
		{
			dir = aimDir;
			rotateNow = false;
		}
		//��]������.
		VECTOR interPolateDir;
		interPolateDir = RotateForAimVecYAxis(dir, aimDir, Omega * deltaTime);

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

/// <summary>
/// �v���C���[�Ƃ̊Ԃɏ�Q�����Ȃ���.
/// </summary>
/// <param name="playerPos">�v���C���[���W</param>
/// <returns>�����Ȃ����true</returns>
bool EnemyCannon::Search(VECTOR playerPos)
{
	colLine.localStart = pos;
	colLine.worldEnd = playerPos;
	for (int i = 0; i < ObjectManager::TagObjectSize(ObjectTag::BackGround); ++i)
	{
		ObjectBase* bgObj = ObjectManager::GetAllObjectsInTag(ObjectTag::BackGround, i);
		if (bgObj)
		{
			int colModel = bgObj->GetCollisionModel();
			MV1_COLL_RESULT_POLY colInfo;
			if (CollisionPair(colLine, colModel, colInfo))
			{
				return false;
			}
		}
	}
	leftOrRight = CalcRotationDirectionYAxis(dir, aimDir);
	Fire();
	if (!IsNearAngle(aimDir, dir))
	{
		rotateNow = true;
	}
	return true;
}

/// <summary>
/// �΍��ʒu�Z�o.
/// </summary>
/// <param name="deltaTime"></param>
void EnemyCannon::DiviationValculation(float deltaTime)
{
	ObjectBase* player = ObjectManager::GetFirstObject(ObjectTag::Player1);
	VECTOR nowPlayerPos = dir;
	if (player)
	{
		nowPlayerPos = player->GetPos();
		if (Search(nowPlayerPos))
		{
			// �v���C���[�Ǝ����̈ʒu����e�����Ԃ��Z�o.
			float length = VSize(nowPlayerPos - pos);
			float time2Inpact = length / (BulletSpeed * deltaTime);

			//�΍��ʒu�̎Z�o.
			VECTOR distanceTraveled = nowPlayerPos - jbPlayerPos;// �ړ���������.
			VECTOR deviationPos = nowPlayerPos + (distanceTraveled * time2Inpact);

			aimDir = VNorm(deviationPos - pos) * -1;

		}

	}
	jbPlayerPos = nowPlayerPos;
}

void EnemyCannon::Fire()
{
	/*VECTOR enemyDir = VNorm(colLine.worldEnd - pos);
	float dot = VDot(enemyDir, dir);
	float range = FOVDegree * DX_PI_F;
	float rad = cosf(range / 2.0f);
	a.x = rad; a.z =dot;*/
	//if (rad <= dot)
	VECTOR enemyDir = VNorm(colLine.worldEnd - pos);
	MATRIX mat = MGetRotY(ToRadian(FOVDegree) * -leftOrRight);
	VECTOR rot = VTransform(dir, mat) * -1;
	float dot1 = VDot(dir, enemyDir);
	float dot2 = VDot(dir, rot);
	if(dot1 < dot2)
	{
		if (shotTime < 0)
		{
			shotTime = ShotIntervalTime;
			/*ObjectBase* bullet = new Bullet(pos, dir * -1, userTag);
			ObjectManager::Entry(bullet);*/
			EffectBase* mazzleFlash = new MazzleFlashEffect(pos, dir * -1);
			EffectManager::Entry(mazzleFlash);

		}
	}
	
}

