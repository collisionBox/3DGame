#include "EnemyCannon.h"
#include "AssetManager.h"
#include "SystemConstant.h"
#include "ObjectManager.h"
#include "Bullet.h"
#include "PlayerBody.h"
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

	dir = VNorm(dir);
	pos = bodyPos;
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
	Rotate(deltaTime);
	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	jbPlayerPos = nowPlayerPos;
}

void EnemyCannon::Draw()
{
	MV1DrawModel(modelHandle);
	DrawFormatString(0, 100, Green, "%f %f", colLine.worldEnd.x, colLine.worldEnd.z);
	//DrawFormatString(0, 200, Green, "%f %f", dir.x, dir.z);
	DrawLine3D(colLine.worldStart, colLine.worldEnd, Green);
}

void EnemyCannon::Rotate(float deltaTime)
{
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
	return true;
}

void EnemyCannon::DiviationValculation(float deltaTime)
{
}

void EnemyCannon::Fire()
{
}

void EnemyCannon::OnCollisionEnter(ObjectBase* other)
{

}