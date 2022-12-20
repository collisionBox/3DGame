#include "PlayerBody.h"
#include "AssetManager.h"
#include "Math.h"

// 静的定数.
const float PlayerBody::Accel = 10.0f;// 通常の加速.
const float PlayerBody::MaxSpeed = 300.0f;// 最高速度.
const float PlayerBody::DefaultDecel = 3.0f;// なにもしない時の減速.
const float PlayerBody::BreakDecel = -5.0f;// ブレーキ時の減速.
const float PlayerBody::GripDecel = -2.0f;// グリップの減速.
const float PlayerBody::GripPower = 2.0f;// グリップ力.
const float PlayerBody::ColideDecelFac = 4.0f;// 障害物にぶつかったときの減速率.

PlayerBody::PlayerBody()
	:ObjectBase(ObjectTag::Player)
	,rotateNow(false)
	,decel()
{
	velocity = VGet(0.0f, 0.0f, 0.0f);
	// モデル読み込み.
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

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	VECTOR accelVec = VGet(0, 0, 0);
	VECTOR prevVel = VGet(0, 0, 0);
	
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
	if (VSize(velocity) > 0)
	{
		// ベロシティの大きさがGRIP_POWERより小さかった場合、GRIP_POWERの大きさをベロシティの大きさと同じにする.
		// これによって曲がるときのベロシティが最大でも45°になる.
		float velSize = VSize(prevVel);
		float gripPower = GripPower;
		if (gripPower > velSize)
		{
			gripPower = velSize;
		}

		// 右を押していたら右方向に力をかける
		if (key & PAD_INPUT_RIGHT)
		{
			VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
			accelVec = VAdd(accelVec, VScale(right, GripPower));
		}
		// 左を押していたら左方向に力をかける
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
	// 自然停止処理.
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
	スピードがマックスになると左右を判定しない問題を修正
	prevVel = VAdd(velocity, accelVec);

	// 最高速度設定.
	if (VSize(prevVel) <= MaxSpeed && VSize(prevVel) > 0)
	{
		velocity = prevVel;
		
	}
	
	// 上下方向にいかないようにvelocityを整える.
	velocity = VGet(velocity.x, 0, velocity.z);
	
	// ポジション更新.
	pos = VAdd(pos, velocity * deltaTime);

	// 力をかけ終わったvelocityの方向にディレクションを調整・正規化.
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
