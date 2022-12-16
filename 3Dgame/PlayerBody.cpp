#include "PlayerBody.h"
#include "AssetManager.h"
#include "Math.h"

// 静的定数.
const float PlayerBody::Accel = 3.0f;// 通常の加速.
const float PlayerBody::MaxSeed = 8.0f;// 最高速度.
const float PlayerBody::DefaultDecel = -1.0f;// なにもしない時の減速.
const float PlayerBody::BreakDecel = -5.0f;// ブレーキ時の減速.
const float PlayerBody::GripDecel = -2.5f;// グリップの減速.
const float PlayerBody::GripPower = 1.0f;// グリップ力.
const float PlayerBody::ColideDecelFac = 4.0f;// 障害物にぶつかったときの減速率.

PlayerBody::PlayerBody()
	:ObjectBase(ObjectTag::Player)
	,rotateNow(false)
{
	velocity = VGet(0.0f, 0.0f, 0.0f);
	// モデル読み込み.
	modelHandle = AssetManager::GetMesh("data/player/reconTankBody.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));
	pos = VGet(0.0f, 13.0f, 0.0f);
	dir = VGet(1.0f, 0.0f, 100.0f);
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

	// 3Dモデルのポジション設定.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
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
	//if (CheckHitKey(KEY_INPUT_O))
	//{
	//	pos = VAdd(pos, VGet(0.0f, 1.0f, 0.0f));
	//}
	//if (CheckHitKey(KEY_INPUT_L))
	//{
	//	pos = VSub(pos, VGet(0.0f, 1.0f, 0.0f));
	//}
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	VECTOR accelVec = VGet(0, 0, 0);
	// 上を押していたら加速.
	if (key & PAD_INPUT_UP)
	{
		accelVec = VScale(dir, Accel);
	}

	//下を押していたら減速.
	if (key & PAD_INPUT_DOWN)
	{
		accelVec = VScale(dir, BreakDecel);
	}
	velocity = VAdd(velocity, accelVec);
	if (VSize(velocity) < 0)
	{
		if (key & PAD_INPUT_RIGHT)
		{
			VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
			dir = VAdd(dir, VScale(right, GripPower));
		}
		if (key & PAD_INPUT_LEFT)
		{
			VECTOR left = VCross(dir, VGet(0.0f, 1.0f, 0.0f));
			dir = VAdd(dir, VScale(left, GripPower));
		}
	}
	if (VSize(velocity) < 5.0f)
	{
		velocity = VGet(0.0f, 0.0f, 0.0f);
	}
	
	// 上下方向にいかないようにvelocityを整える.
	velocity = (VGet(velocity.x, 0, velocity.z));

	// ポジション更新.
	pos = VAdd(pos, velocity * deltaTime);

	// 力をかけ終わったvelocityの方向にディレクションを調整.
	if (VSize(velocity) != 0)
	{
		dir = VNorm(velocity);
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
