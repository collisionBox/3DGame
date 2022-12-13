#include "PlayerBody.h"
#include "AssetManager.h"
#include "Math.h"

// �ÓI�萔.
const float PlayerBody::Accel = 0.03f;// �ʏ�̉���.
const float PlayerBody::MaxSeed = 0.8f;// �ō����x.
const float PlayerBody::DefaultDecel = -0.01f;// �Ȃɂ����Ȃ����̌���.
const float PlayerBody::BreakDecel = -0.05f;// �u���[�L���̌���.
const float PlayerBody::GripDecel = -0.025f;// �O���b�v�̌���.
const float PlayerBody::GripPower = 0.1f;// �O���b�v��.
const float PlayerBody::ColideDecelFac = 0.4f;// ��Q���ɂԂ������Ƃ��̌�����.

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

	//pos += velocity;

	MV1SetPosition(modelHandle, pos);

	// 3D���f���̃|�W�V�����ݒ�.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	tmpMat = MMult(tmpMat, rotYMat);
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationMatrix(modelHandle, rotYMat);
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
#if 0
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
#else
	// ��������.
	VECTOR accelVec = VGet(0, 0, 0);

	// ��������Ă��������.
	if (key & PAD_INPUT_UP)
	{
		accelVec = VScale(dir, Accel);
	}

	//���������Ă����猸��.
	if (key & PAD_INPUT_DOWN)
	{
		accelVec = VScale(dir, BreakDecel);
	}

	// �~�܂��Ă���ꍇ�͌������Ȃ�.
	if (VSize(velocity) > 0)
	{
		// �E�����������Ă�����O���b�v�ɂ�錸��.
		if (key & PAD_INPUT_RIGHT || key & PAD_INPUT_LEFT)
		{
			accelVec = VAdd(accelVec, VScale(dir, GripDecel));
		}
		// ���������Ȃ���Ό���.
		if (key == 0)
		{
			accelVec = VScale(dir, DefaultDecel);
		}
	}

	// velocity�����v�Z.
	velocity = VAdd(velocity, accelVec);

	// ���Ε����ɐi�ޏ�ԂɂȂ��Ă�����~�߂�.
	if (VDot(velocity, dir) < 0)
	{
		velocity = VGet(0, 0, 0);
	}
	// �~�܂��Ă����獶�E�ړ����Ȃ�.
	if (VSize(velocity) > 0)
	{
		// velocity�̑傫����GRIP_POWER��菬���������ꍇ�AGrip_Power�̑傫����velocity�̑傫���Ɠ����ɂ���.
		// ����ɂ���ċȂ���Ƃ���velocity���ő�ł�45���ɂȂ�. 
		float velSize = VSize(velocity);
		float gripPower = GripPower;
		if (gripPower > velSize)
		{
			gripPower = velSize;
		}

		// �E�������Ă�����E�����ɗ͂�������.
		if (key & PAD_INPUT_RIGHT)
		{
			VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
			velocity = VAdd(velocity, VScale(right, GripPower));
		}
		if (key & PAD_INPUT_LEFT)
		{
			VECTOR left = VCross(dir, VGet(0.0f, 1.0f, 0.0f));
			velocity = VAdd(velocity, VScale(left, GripPower));
		}

	}

	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = (VGet(velocity.x, 0, velocity.z));

	// �|�W�V�����X�V.
	pos = VAdd(pos, velocity);

	// �͂������I�����velocity�̕����Ƀf�B���N�V�����𒲐�.
	if (VSize(velocity) != 0)
	{
		dir = VNorm(velocity);
	}


#endif
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
