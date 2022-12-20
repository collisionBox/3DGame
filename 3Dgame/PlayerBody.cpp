#include "PlayerBody.h"
#include "AssetManager.h"
#include "Math.h"

// �ÓI�萔.
const float PlayerBody::Accel = 10.0f;// �ʏ�̉���.
const float PlayerBody::MaxSpeed = 300.0f;// �ō����x.
const float PlayerBody::DefaultDecel = 3.0f;// �Ȃɂ����Ȃ����̌���.
const float PlayerBody::BreakDecel = -5.0f;// �u���[�L���̌���.
const float PlayerBody::GripDecel = -2.0f;// �O���b�v�̌���.
const float PlayerBody::GripPower = 2.0f;// �O���b�v��.
const float PlayerBody::ColideDecelFac = 4.0f;// ��Q���ɂԂ������Ƃ��̌�����.

PlayerBody::PlayerBody()
	:ObjectBase(ObjectTag::Player)
	,rotateNow(false)
	,decel()
{
	velocity = VGet(0.0f, 0.0f, 0.0f);
	// ���f���ǂݍ���.
	modelHandle = AssetManager::GetMesh("data/player/reconTankBody.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));
	pos = VGet(0.0f, 13.0f, 0.0f);
	dir = VGet(0.0f, 0.0f, 1.0f);
	aimDir = dir;
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
	/*if (CheckHitKey(KEY_INPUT_O))
	{
		pos = VAdd(pos, VGet(0.0f, 1.0f, 0.0f));
	}
	if (CheckHitKey(KEY_INPUT_L))
	{
		pos = VSub(pos, VGet(0.0f, 1.0f, 0.0f));
	}*/

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	VECTOR accelVec = VGet(0, 0, 0);
	VECTOR prevVel = VGet(0, 0, 0);
	
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
	if (VSize(velocity) > 0)
	{
		// �x���V�e�B�̑傫����GRIP_POWER��菬���������ꍇ�AGRIP_POWER�̑傫�����x���V�e�B�̑傫���Ɠ����ɂ���.
		// ����ɂ���ċȂ���Ƃ��̃x���V�e�B���ő�ł�45���ɂȂ�.
		float velSize = VSize(prevVel);
		float gripPower = GripPower;
		if (gripPower > velSize)
		{
			gripPower = velSize;
		}

		// �E�������Ă�����E�����ɗ͂�������
		if (key & PAD_INPUT_RIGHT)
		{
			VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
			accelVec = VAdd(accelVec, VScale(right, GripPower));
		}
		// ���������Ă����獶�����ɗ͂�������
		if (key & PAD_INPUT_LEFT)
		{
			VECTOR left = VCross(dir, VGet(0.0f, 1.0f, 0.0f));
			accelVec = VAdd(accelVec, VScale(left, GripPower));
		}
		
	}
	else
	{
		if (key & PAD_INPUT_RIGHT)
		{
			VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
			dir = VAdd(dir, VScale(right, GripPower)) * deltaTime;
		}
		if (key & PAD_INPUT_LEFT)
		{
			VECTOR left = VCross(dir, VGet(0.0f, 1.0f, 0.0f));
			dir = VAdd(dir, VScale(left, GripPower)) * deltaTime;
		}
	}
	// ���R��~����.
	if (VSize(velocity) > 0)
	{
		if (!key)
		{
			float dot = VDot(velocity, dir);
			if (dot > 0)
			{
				accelVec = VScale(dir, -DefaultDecel);
			}
			else
			{
				accelVec = VScale(dir, DefaultDecel);
			}

			if (abs(dot) <= 3)
			{
				accelVec = VGet(0, 0, 0);
				velocity = VGet(0, 0, 0);
			}

		}
		
	}
	�X�s�[�h���}�b�N�X�ɂȂ�ƍ��E�𔻒肵�Ȃ������C��
	prevVel = VAdd(velocity, accelVec);

	// �ō����x�ݒ�.
	if (VSize(prevVel) <= MaxSpeed && VSize(prevVel) > 0)
	{
		velocity = prevVel;
		
	}
	
	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);
	
	// �|�W�V�����X�V.
	pos = VAdd(pos, velocity * deltaTime);

	// �͂������I�����velocity�̕����Ƀf�B���N�V�����𒲐��E���K��.
	//if (VSize(dir) != 0)
	{
		dir = VNorm(dir);
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
