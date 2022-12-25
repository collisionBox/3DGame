#include "PlayerBody.h"
#include "AssetManager.h"
#include "Math.h"

// �ÓI�萔.
const float PlayerBody::Accel = 6.0f;// �ʏ�̉���.
const float PlayerBody::Back = 5.0f;// ��ޑ��x.
const float PlayerBody::MaxSpeed = 400.0f;// �ō��O�i���x.
const float PlayerBody::MinSpeed = -350.0f;// �ō���ޑ��x.
const float PlayerBody::DefaultDecel = 0.97f;// �Ȃɂ����Ȃ����̌���.
const float PlayerBody::BreakDecel = 0.5f;// �u���[�L���̌���.
const float PlayerBody::GripDecel = -5.0f;// �O���b�v�̌���.
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

	// �L�[���͎擾.
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ��������.
	

	VECTOR accelDir = VGet(0.0f,1.0f,0.0f);

	VECTOR backDir = VScale(dir, -1);

	// ���͋��t���O.
	bool input = false;

#if 0
	// �ō����x�ݒ�.
	if (VSize(velocity) <= MaxSpeed && VSize(velocity) >= 0)
	{
		input = true;
	}

	// ���͋�����Ă�����.
	if (input)
	{
		// ��������Ă��������.
		if (key & PAD_INPUT_UP)
		{
			accelVec = VScale(dir, Accel);
		}
		
		//���������Ă����猸��.
		if (key & PAD_INPUT_DOWN)
		{
			accelVec = VScale(dir, -Back);
			
		}
	}

	// �~�܂��Ă��Ȃ���Ό���������.
	if (VSize(velocity) > 0)
	{
		// �O���b�v����.
		if (key & PAD_INPUT_RIGHT || key & PAD_INPUT_LEFT)
		{
			if (VSize(velocity) >= 20)
			{
				accelVec = VAdd(accelVec, VScale(dir, GripDecel));
			}
		}
		// �L�[���͂��������.
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

			if (abs(dot) <= 3)// ���x���O�ɂȂ�悤�ɕ␳.
			{
				accelVec = VGet(0, 0, 0);
				velocity = VGet(0, 0, 0);
			}

		}

	}
	// �~�܂��ċ��Ȃ�������.
	if (VSize(velocity) > 0)
	{
		// �x���V�e�B�̑傫����GRIP_POWER��菬���������ꍇ�AGRIP_POWER�̑傫�����x���V�e�B�̑傫���Ɠ����ɂ���.
		// ����ɂ���ċȂ���Ƃ��̃x���V�e�B���ő�ł�45���ɂȂ�.
		/*float velSize = VSize(velocity);
		float gripPower = GripPower;
		if (gripPower > velSize)
		{
			gripPower = velSize;
		}*/
		const VECTOR turningNum = VGet(0.0f, 1.0f, 0.0f);
		// �E�������Ă�����E�����ɗ͂�������
		if (key & PAD_INPUT_RIGHT)
		{
			VECTOR right = VCross(turningNum, dir);
			dir = VAdd(dir, VScale(right, GripPower*0.01));
		}
		// ���������Ă����獶�����ɗ͂�������
		if (key & PAD_INPUT_LEFT)
		{
			VECTOR left = VCross(dir, turningNum);
			dir = VAdd(dir, VScale(left, GripPower * 0.01));
		}
		dir = VNorm(dir);
	}
	// ���M�n����.
	if (VSize(velocity) <= 0)// �~�܂��Ă�����.
	{
		float onStopRotateSpeed = GripPower * 0.03;
		if (key & PAD_INPUT_RIGHT)// �E����.
		{
			VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
			dir = VAdd(dir, VScale(right, onStopRotateSpeed));
		}
		if (key & PAD_INPUT_LEFT)// ������.
		{
			VECTOR left = VCross(dir, VGet(0.0f, 1.0f, 0.0f));
			dir = VAdd(dir, VScale(left, onStopRotateSpeed));
		}
		dir = VNorm(dir);
	}

	velocity = VAdd(velocity, accelVec);
	
	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);
	
	// �|�W�V�����X�V.
	pos = VAdd(pos, velocity * deltaTime);

	// �͂������I�����velocity�̕����Ƀf�B���N�V�����𒲐��E���K��.
	if (VSize(velocity) != 0)
	{
		//dir = VNorm(velocity);
	}

#else

float dot = VDot(velocity, dir);// ����.
if (dot <= MaxSpeed)
{
	// ��������Ă��������.
	if (key & PAD_INPUT_UP)
	{
		accel += Accel;
	}

}
if (dot >= MinSpeed)
{
	//���������Ă����猸��.
	if (key & PAD_INPUT_DOWN)
	{
		accel += -Back;
	}
}
	

	// ���R��~.
	if(!(key & PAD_INPUT_UP) && !(key & PAD_INPUT_DOWN))
	{
		accel *= DefaultDecel;
		if (VSize(velocity) <= 1.1f)
		{
			accel = 0;
		}
	}

	float onStopRotateSpeed = GripPower * 0.03;
	
	if (key & PAD_INPUT_RIGHT)// �E����.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, onStopRotateSpeed));
	}
	if (key & PAD_INPUT_LEFT)// ������.
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, onStopRotateSpeed));
	}
	// �O���b�v����.
	if (key & PAD_INPUT_RIGHT || key & PAD_INPUT_LEFT)
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
	pos = VAdd(pos, velocity * deltaTime);
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
