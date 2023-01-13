#include "PlayerBody.h"
#include "PlayerCannon.h"
// �ÓI�萔.
const float PlayerBody::Accel = 6.0f;// �ʏ�̉���.
const float PlayerBody::Back = 5.0f;// ��ޑ��x.
const float PlayerBody::MaxSpeed = 200.0f;// �ō��O�i���x.
const float PlayerBody::MinSpeed = -350.0f;// �ō���ޑ��x.
const float PlayerBody::DefaultDecel = 0.97f;// �Ȃɂ����Ȃ����̌���.
const float PlayerBody::BreakDecel = 0.5f;// �u���[�L���̌���.
const float PlayerBody::GripDecel = -5.0f;// �O���b�v�̌���.
const float PlayerBody::GripPower = 2.0f;// �O���b�v��.
const float PlayerBody::ColideDecelFac = 4.0f;// ��Q���ɂԂ������Ƃ��̌�����.
const float PlayerBody::TurnPerformance = 5.0f;// ���񐫔\.

PlayerBody::PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag myTag) :
	ObjectBase(myTag)
	, rotateNow(false)
	, accel()
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/player/reconTankBody.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));
	
	// �ʒu�E������������.
	// �����֔z�u.
	pos = initPos;// (�n�ʂɂ��܂邽��13�グ��.)����͖���
	// ���S������.
	dir = initDir;
	aimDir = dir;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// �ϐ��̏�����.
	velocity = initVec;
	padInput = inputState;
}
PlayerBody::~PlayerBody()
{
	AssetManager::DeleteMesh(modelHandle);
}



void PlayerBody::Update(float deltaTime)
{
	//Rotate();
	Input(deltaTime);

	//pos += velocity;
	
	MV1SetPosition(modelHandle, pos);

	// 3D���f���̃|�W�V�����ݒ�.
	//MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	//tmpMat = MMult(tmpMat, rotYMat);
	VECTOR negativeVec = VTransform(dir, rotYMat);
	////MV1SetRotationMatrix(modelHandle, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	////collisionUpdate();

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
}

void PlayerBody::Draw()
{
	MV1DrawModel(modelHandle);

}

void PlayerBody::OnCollisionEnter(const ObjectBase* other)
{
	ObjectTag tag = other->GetTag();

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
		}

		// �w�i�Ƒ������������蔻��.
		MV1_COLL_RESULT_POLY colInfoLine;
		if (CollisionPair(colLine, colModel, colInfoLine))
		{
			// �������Ă���ꍇ�͑������Փ˓X�ɍ��킹��.
			pos = colInfoLine.HitPosition;

			CollisionUpdate();
		}
	}
	if (tag == ObjectTag::Bullet)
	{

	}
}

void PlayerBody::Input(float deltaTime)
{
	// �L�[���͎擾.
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	GetJoypadXInputState(padInput, &pad);
	const VECTOR accelDir = VGet(0.0f,1.0f,0.0f);
	const VECTOR backDir = VScale(dir, -1);
	// ���͋��t���O.
	bool input = false;

	// ��������.
	float dot = VDot(velocity, dir);// ����.
	if (dot <= MaxSpeed)
	{
		// ��������Ă��������.
		if (key & PAD_INPUT_UP || pad.RightTrigger != 0)
		{
			accel += Accel;
		}

	}
	if (dot >= MinSpeed)
	{
		//���������Ă����猸��.
		if (key & PAD_INPUT_DOWN || pad.LeftTrigger)
		{
			accel -= Back;
		}
	}
	// ���R��~.
	if(!(key & PAD_INPUT_UP) && !(key & PAD_INPUT_DOWN) && pad.LeftTrigger - pad.RightTrigger == 0)
	{
		accel *= DefaultDecel;
		if (VSize(velocity) <= 8.0f)
		{
			accel = 0;
		}
		if (accel <= 0.1f)
		{
			accel = 0;
		}
	}
	
	if (key & PAD_INPUT_RIGHT && !(key & PAD_INPUT_LEFT) || pad.ThumbLX > 0)// �E����.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
		//dir = VScale(dir, deltaTime);
	}
	else if (key & PAD_INPUT_LEFT && !(key & PAD_INPUT_RIGHT) || pad.ThumbLX < 0)// ������.
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
		//dir = VScale(dir, deltaTime);
	}
	// �O���b�v����.
	if (key & PAD_INPUT_RIGHT || key & PAD_INPUT_LEFT || pad.ThumbLX)
	{
		if (VSize(velocity) >= 20)
		{
			velocity = VAdd(velocity, VScale(dir, GripDecel));
		}
	}
	dir = VNorm(dir);

	velocity = VScale(dir, accel);
	
	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);

	// �|�W�V�����X�V.
	pos = VAdd(pos, VScale(velocity, deltaTime));
	
}

void PlayerBody::Rotate()
{
	if (rotateNow)
	{

		if (IsNearAngle(aimDir,dir))
		{
			dir = aimDir;
			rotateNow = false;
		}
		else
		{
			//��]������.
			VECTOR interPolateDir;
			interPolateDir = RotateForAimVecYAxis(dir, aimDir, 10.0f);
			
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
