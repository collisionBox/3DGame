#include "PlayerCannon.h"

const float PlayerCannon::TurnPerformance = 3.50f;

#if 0
#else
PlayerCannon::PlayerCannon(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag userTag, const char* failName) :
	ObjectBase(ObjectTag::Cannon)
{

	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	string str = "playerCannon.mv1";
	modelHandle = AssetManager::GetMesh(failName + str);
	MV1SetScale(modelHandle, moveModelScale);

	
	
	// �ʒu�E������������.
	pos = initPos;
	pos.y = 0.5f;
	dir = initDir;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	
	bulletManager = new BulletManager(userTag, inputState);

	// �ϐ��̏�����.
	aimDir = initVec;
	rotateNow = false;
	padInput = inputState;
}

#endif
PlayerCannon::~PlayerCannon()
{
	AssetManager::DeleteMesh(modelHandle);
}


#if 1
void PlayerCannon::Update(float deltaTime)
{
	// ������deltaTime�ȊO�̂��̂��g����������s�g�p.
}
#else
void PlayerCannon::Update(float deltaTime)
{
	ObjectBase* camera = ObjectManager::GetFirstObject(ObjectTag::Camera);
	ObjectBase* body = ObjectManager::GetFirstObject(ObjectTag::Body);
	VECTOR cameraDir = camera->GetDir();

	if (VDot(dir, cameraDir) > 0.99f)
	{
		float rotRadianSpeed = ToRadian(10) * deltaTime;// �p���x.
		// ���Ȃ�p���x�𕉂�.
		if (VCross(dir, cameraDir).y < 0.0f)
		{
			rotRadianSpeed *= -1;
		}
		// Y����]�s����쐬.
		MATRIX rotMat = MGetRotY(rotRadianSpeed);

		// ��]������.
		VECTOR rotVec = VTransform(dir, rotMat);

		//�ڕW�p�𒴂��Ă��Ȃ���.
		VECTOR cross1, cross2;
		cross1 = VCross(dir, cameraDir);
		cross2 = VCross(rotVec, cameraDir);

		// �ڕW�p�x�𒴂�����I��.
		if (cross1.y * cross2.y < 0.01f)
		{
			rotVec = cameraDir;
		}
		rotVec.y = 0.0f;// �␳.
		rotVec = VNorm(rotVec);

		// �X�V.
		dir = rotVec;
	}

	pos = body->GetPos();
	// �ύX�𔽉f.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	monitorNum[0] = VDot(dir,cameraDir);
	
}

#endif
void PlayerCannon::Updateeeee(VECTOR bodyPos, float deltaTime)
{

	Input(deltaTime);
	Rotate();
	dir = VNorm(dir);
	pos = bodyPos;

	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	bulletManager->Update(deltaTime);
}
void PlayerCannon::Draw()
{
	MV1DrawModel(modelHandle);
	
}

void PlayerCannon::Input(float deltaTime)
{
	GetJoypadXInputState(padInput, &pad);
	if (CheckHitKey(KEY_INPUT_A))
	{

		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
	}
	VECTOR padVec = VGet(pad.ThumbRX, 0.0f, pad.ThumbRY);
	
	if (VectorSize(padVec) != 0.0f)
	{
		padVec = VNorm(padVec);
		if (IsNearAngle(padVec, dir))
		{
			dir = padVec;
		}
		else
		{
			rotateNow = true;
			aimDir = padVec;
		}
	}

	bulletManager->Input(pos, dir);
	
}

void PlayerCannon::Rotate()
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


