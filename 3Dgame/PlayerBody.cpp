#include "PlayerBody.h"

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

PlayerBody::PlayerBody() :
	ObjectBase(ObjectTag::Body)
	, rotateNow(false)
	, accel()

{
	velocity = VGet(0.0f, 0.0f, 0.0f);
	// ���f���ǂݍ���.
	modelHandle = AssetManager::GetMesh("data/player/reconTankBody.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));
	pos = VGet(0.0f, 13.0f, 0.0f);
	dir = VGet(0.0f, 0.0f, 1.0f);
	aimDir = dir;
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
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
	ObjectBase* camera = ObjectManager::GetFirstObject(ObjectTag::Camera);


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

	

	const VECTOR accelDir = VGet(0.0f,1.0f,0.0f);
	const VECTOR backDir = VScale(dir, -1);

	// ���͋��t���O.
	bool input = false;

	// ��������.
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
		if (VSize(velocity) <= 8.0f)
		{
			accel = 0;
		}
	}

	float onStopRotateSpeed = GripPower * 0.03f;
	
	if (key & PAD_INPUT_RIGHT)// �E����.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, onStopRotateSpeed));
		dir = VScale(dir, deltaTime);
	}
	if (key & PAD_INPUT_LEFT)// ������.
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, onStopRotateSpeed));
		dir = VScale(dir, deltaTime);
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
	//ObjectBase* bullet = ObjectManager::GetFirstObject(ObjectTag::Bullet);
	
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
