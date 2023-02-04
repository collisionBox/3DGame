#include "PlayerBody.h"
// �ÓI�萔.
const float PlayerBody::Accel = 6.0f;// �ʏ�̉���.
const float PlayerBody::Back = 5.0f;// ��ޑ��x.
const float PlayerBody::MaxSpeed = 300.0f;// �ō��O�i���x.
const float PlayerBody::MinSpeed = -200.0f;// �ō���ޑ��x.
const float PlayerBody::DefaultDecel = 0.97f;// �Ȃɂ����Ȃ����̌���.
const float PlayerBody::BreakDecel = 0.5f;// �u���[�L���̌���.
const float PlayerBody::GripDecel = -5.0f;// �O���b�v�̌���.
const float PlayerBody::GripPower = 2.0f;// �O���b�v��.
const float PlayerBody::ColideDecelFac = 4.0f;// ��Q���ɂԂ������Ƃ��̌�����.
const float PlayerBody::TurnPerformance = 5.0f;// ���񐫔\.
const float PlayerBody::OnShootingDownWaitTime = 5.0f;// �팂�Ď��ҋ@����.

PlayerBody::PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag myTag, const char* failName) :
	ObjectBase(myTag)
	, rotateNow(false)
	, accel()
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	string str = "playerBody.mv1";
	modelHandle = AssetManager::GetMesh(failName + str);
	if (modelHandle == -1)
	{
		printfDx("playerBody��ǂݍ��߂܂���");
	}
	MV1SetScale(modelHandle, moveModelScale);

	// �ʒu�E������������.
	// �����֔z�u.
	pos = initPos;// (�n�ʂɂ��܂邽��13�グ��.)����͖���
	prevPos = pos;
	// ���S���ۂ�����������.
	dir = initDir;
	aimDir = dir;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	cannon = new PlayerCannon(initPos, initDir, inputState, myTag, failName);

	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = 32.0f;

	// �ϐ��̏�����.
	velocity = initVec;
	padInput = inputState;
	HP = 100;
	hpGauge = new HPGauge(HP);
	deltaWaitTime = 0;
	
}

PlayerBody::~PlayerBody()
{
	AssetManager::DeleteMesh(modelHandle);
}

void PlayerBody::Update(float deltaTime)
{

	//if (HP > 0.0f)
	{
		Input(deltaTime);
	}
	//else
	{
		deltaWaitTime += deltaTime;
		// �����G�t�F�N�g�������.

		if (deltaWaitTime > OnShootingDownWaitTime)// �G�t�F�N�g�Đ����I�������ɂ����ύX.
		{
			// OVER�փV�[���J��.
		}
	}

	if (prevPos.x + colSphere.radius > windowSizeXMax ||
		prevPos.x - colSphere.radius < windowSizeXMin ||
		prevPos.z + colSphere.radius > windowSizeZMax ||
		prevPos.z - colSphere.radius < windowSizeZMin)//-885,13,159
	{
		velocity = initVec;
		prevPos = pos;
	}

	pos = prevPos;
	cannon->Updateeeee(pos, deltaTime);
	hpGauge->Update(pos, HP, deltaTime);
	CollisionUpdate();

	// 3D���f���̃|�W�V�����ݒ�.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void PlayerBody::Draw()
{
	MV1DrawModel(modelHandle);

	cannon->Draw();
	hpGauge->Draw();
	DrawCollider();
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

			velocity = initVec;
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
}

void PlayerBody::Input(float deltaTime)
{
	// �L�[���͎擾.
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	GetJoypadXInputState(padInput, &pad);

	// ��������.
	if (accel <= MaxSpeed)
	{
		// ��������Ă��������.
		if (CheckHitKey(KEY_INPUT_UP))
		{
			accel += Accel;
		}
		if (pad.RightTrigger != 0)
		{
			accel += Accel;
		}
	}
	if (accel >= MinSpeed)
	{
		//���������Ă����猸��.
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			accel -= Back;
		}
		if (pad.LeftTrigger)
		{
			accel -= Back;
		}
	}
	
	if (CheckHitKey(KEY_INPUT_RIGHT))// �E����.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
		//dir = VScale(dir, deltaTime);
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))// ������.
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
	}

	if (pad.ThumbLX > 0)
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
	}
	else if (pad.ThumbLX < 0)
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
	}

	// ���R��~.
	if (!(CheckHitKey(KEY_INPUT_UP)) && !(CheckHitKey(KEY_INPUT_UP)) && pad.LeftTrigger - pad.RightTrigger == 0)
	{
		accel *= DefaultDecel;
		if (abs(VSize(velocity)) <= 8.0f)
		{
			accel = 0;
		}
	}

	// �O���b�v����.
	if (key & PAD_INPUT_RIGHT || key & PAD_INPUT_LEFT || pad.ThumbLX != 0)
	{
		if (VSize(velocity) >= 20)
		{
			velocity = VAdd(velocity, VScale(dir, GripDecel));
		}
	}
	dir = VNorm(dir);// ���K��.

	velocity = VScale(dir, accel);// �����x�N�g���ɉ����͂������ĉ����x�N�g���Ƃ���.
	
	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);

	// �|�W�V�����X�V.
	prevPos = VAdd(pos, VScale(velocity, deltaTime));
	
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
