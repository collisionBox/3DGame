#include "PlayerBody.h"


PlayerBody::PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, PlayerTag myTag, const char* failName) :
	ObjectBase(ObjectTag::Player)
	, rotateNow(false)
	, accel()
{
	// �C�𐶐�.
	cannon = new PlayerCannon(initPos, initDir, inputState , ObjectTag::Player, failName);
	// HP�Q�[�W�𐶐�.
	hpGauge = new HPGauge(HP);

	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	string str = "playerBody.mv1";
	modelHandle = AssetManager::GetMesh(failName + str);
	if (modelHandle == -1)
	{
		printfDx("playerBody��ǂݍ��߂܂���");
	}
	MV1SetScale(modelHandle, MoveModelScale);

	// �ʒu�E������������.
	this->initPos = initPos;
	this->initDir = initDir;
	Initialize();

	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = 32.0f;


	// �ϐ��̏�����.
	padInput = inputState;
	//nameTag = myTag;
	winNum = 0;
}

PlayerBody::PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag myTag, const char* failName) :
	ObjectBase(myTag)
	, rotateNow(false)
	, accel()
{
	// �C�𐶐�.
	cannon = new PlayerCannon(initPos, initDir, inputState, ObjectTag::Player, failName);
	// HP�Q�[�W�𐶐�.
	hpGauge = new HPGauge(HP);

	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	string str = "playerBody.mv1";
	modelHandle = AssetManager::GetMesh(failName + str);
	if (modelHandle == -1)
	{
		printfDx("playerBody��ǂݍ��߂܂���");
	}
	MV1SetScale(modelHandle, MoveModelScale);

	// �ʒu�E������������.
	this->initPos = initPos;
	this->initDir = initDir;
	Initialize();

	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = 32.0f;


	// �ϐ��̏�����.
	padInput = inputState;
	winNum = 0;
	nameTag = myTag;
}

void PlayerBody::Initialize()
{
	// �l�̏�����.
	pos = initPos;
	prevPos = pos;
	dir = initDir;
	aimDir = dir;
	velocity = InitVec;
	HP = maxHP;

	// �I�u�W�F�N�g�̏�����.
	cannon->Initialize(pos, dir);
	hpGauge->Initialize(HP);

	// �ύX�̔��f.
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
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

	// �����x�N�g���ɉ����͂������ĉ����x�N�g���Ƃ���.
	velocity = VScale(dir, accel);

	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);

	// �\���|�W�V�����X�V.
	prevPos = VAdd(pos, VScale(velocity, deltaTime));

	// ��ʊO����.
	if (offscreenDicision(prevPos, colSphere.radius))
	{
		velocity = InitVec;
		prevPos = pos;
	}
	CollisionUpdate(prevPos);

	// �|�W�V�����X�V.
	pos = prevPos;
	cannon->Updateeeee(pos, deltaTime);
	hpGauge->Update(pos, HP, deltaTime);

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
			pos = VAdd(prevPos, poshBuckVec);

			// �R���W�������̉��.
			MV1CollResultPolyDimTerminate(colInfo);

			if (accel > 0)
			{
				accel = 0;
			}

			velocity = InitVec;
			CollisionUpdate();
		}

	
	}
	if (tag == ObjectTag::Bullet)
	{
		Sphere colSphere = other->GetCollisionSphere();
		if (CollisionPair(this->colSphere, colSphere))
		{
			HP -= DamagePoint;
		}
	}
	if (tag != nameTag && (tag == ObjectTag::Player1 || tag == ObjectTag::Player2))
	{
		Sphere colSphere = other->GetCollisionSphere();
		if (CollisionPair(this->colSphere, colSphere))
		{
			pos = prevPos;
		}
	}
	
}



void PlayerBody::Input(float deltaTime)
{
	// �L�[���͎擾.
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	GetJoypadXInputState(padInput, &pad);
	cannon->Input(deltaTime, pad);
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
	// ���񏈗�.
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

	if (pad.ThumbLX > 0)// �E����.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
	}
	else if (pad.ThumbLX < 0)// ������.
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
	// ���K��.
	dir = VNorm(dir);

	
	
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
