#include "PlayerBody.h"

// 静的定数.
const float PlayerBody::Accel = 6.0f;// 通常の加速.
const float PlayerBody::Back = 5.0f;// 後退速度.
const float PlayerBody::MaxSpeed = 400.0f;// 最高前進速度.
const float PlayerBody::MinSpeed = -350.0f;// 最高後退速度.
const float PlayerBody::DefaultDecel = 0.97f;// なにもしない時の減速.
const float PlayerBody::BreakDecel = 0.5f;// ブレーキ時の減速.
const float PlayerBody::GripDecel = -5.0f;// グリップの減速.
const float PlayerBody::GripPower = 2.0f;// グリップ力.
const float PlayerBody::ColideDecelFac = 4.0f;// 障害物にぶつかったときの減速率.

PlayerBody::PlayerBody() :
	ObjectBase(ObjectTag::Body)
	, rotateNow(false)
	, accel()

{
	velocity = VGet(0.0f, 0.0f, 0.0f);
	// モデル読み込み.
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

	// 3Dモデルのポジション設定.
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

	// キー入力取得.
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	

	const VECTOR accelDir = VGet(0.0f,1.0f,0.0f);
	const VECTOR backDir = VScale(dir, -1);

	// 入力許可フラグ.
	bool input = false;

	// 加速処理.
	float dot = VDot(velocity, dir);// 内積.
	if (dot <= MaxSpeed)
	{
		// 上を押していたら加速.
		if (key & PAD_INPUT_UP)
		{
			accel += Accel;
		}
	
	}
	if (dot >= MinSpeed)
	{
		//下を押していたら減速.
		if (key & PAD_INPUT_DOWN)
		{
			accel += -Back;
		}
	}

	// 自然停止.
	if(!(key & PAD_INPUT_UP) && !(key & PAD_INPUT_DOWN))
	{
		accel *= DefaultDecel;
		if (VSize(velocity) <= 8.0f)
		{
			accel = 0;
		}
	}

	float onStopRotateSpeed = GripPower * 0.03f;
	
	if (key & PAD_INPUT_RIGHT)// 右旋回.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, onStopRotateSpeed));
		dir = VScale(dir, deltaTime);
	}
	if (key & PAD_INPUT_LEFT)// 左旋回.
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, onStopRotateSpeed));
		dir = VScale(dir, deltaTime);
	}
	// グリップ減速.
	if (key & PAD_INPUT_RIGHT || key & PAD_INPUT_LEFT)
	{
		if (VSize(velocity) >= 20)
		{
			velocity = VAdd(velocity, VScale(dir, GripDecel));
		}
	}
	dir = VNorm(dir);

	velocity = VScale(dir, accel);

	// 上下方向にいかないようにvelocityを整える.
	velocity = VGet(velocity.x, 0, velocity.z);

	// ポジション更新.
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
			//回転させる.
			VECTOR interPolateDir;
			interPolateDir = RotateForAimVecYAxis(dir, aimDir, 10.0f);
			
			// 回転が目標角を超えていないか.
			VECTOR cross1, cross2;
			cross1 = VCross(dir, aimDir);
			cross2 = VCross(interPolateDir, aimDir);

			// 目標角度を超えたら終了.
			if (cross1.y * cross2.y < 0.0f)
			{
				interPolateDir = aimDir;
				rotateNow = false;
			}
			// 目標ベクトルに１０度だけ近づけた角度
			dir = interPolateDir;
		}
	}
}
