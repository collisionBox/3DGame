#include "PlayerBody.h"
#include "AssetManager.h"
#include "Math.h"

PlayerBody::PlayerBody()
	:ObjectBase(ObjectTag::Player)
	,rotateNow(false)
{
	velocity = VGet(0, 0, 0);
	// ���f���ǂݍ���.
	modelHandle = AssetManager::GetMesh("data/player/reconTankBody.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));
	pos = VGet(0, 0, 0);
	dir = VGet(1, 0, 0);
	aimDir = dir;
}

PlayerBody::~PlayerBody()
{
	AssetManager::DeleteMesh(modelHandle);
	
}

void PlayerBody::Update(float deltaTime)
{
	Rotate();
	Input(deltaTime);

	pos += velocity;

	MV1SetPosition(modelHandle, pos);

	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	//collisionUpdate();
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
		
	}
}

void PlayerBody::Input(float deltaTime)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	VECTOR UP = { 0,0,1 };
	VECTOR DOWN = { 0,0,-1 };
	VECTOR LEFT = { -1,0,0 };
	VECTOR RIGHT = { 1,0,0 };

	VECTOR inputVec = VGet(0, 0, 0);

	bool input = false;
	if (key & PAD_INPUT_UP)
	{
		inputVec += UP;
		input = true;
	}

	if (key & PAD_INPUT_DOWN)
	{
		inputVec += DOWN;
		input = true;
	}

	if (key& PAD_INPUT_RIGHT)
	{
		inputVec += RIGHT;
		input = true;
	}

	if (key & PAD_INPUT_LEFT)
	{
		inputVec += LEFT;
		input = true;
	}

	// ���͂�������������E�Ȃ��Ƃ�����.
	if (input)
	{
		// ���E�E�㉺���������Ȃǂœ��̓x�N�g�����O�̎��͖���.
		if (VSquareSize(inputVec) < 0.5f)
		{
			return;
		}
		// �����𐳋K��
		inputVec = VNorm(inputVec);

		// ���͕����͌��݌����Ă�������ƈقȂ邩�H.
		if (IsNearAngle(inputVec, dir))
		{
			dir = inputVec;
		}
		else
		{
			rotateNow = true;
			aimDir = inputVec;
		}

		velocity = inputVec + (inputVec * deltaTime * 200.0f);

		
	}
	else
	{
		velocity *= 0.9f;
		
	}
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
