#include "PlayerBody.h"
#include "AssetManager.h"
#include "Math.h"

// 静的定数.
const float PlayerBody::Accel = 0.03f;// 通常の加速.
const float PlayerBody::MaxSeed = 0.8f;// 最高速度.
const float PlayerBody::DefaultDecel = -0.01f;// なにもしない時の減速.
const float PlayerBody::BreakDecel = -0.05f;// ブレーキ時の減速.
const float PlayerBody::GripDecel = -0.025f;// グリップの減速.
const float PlayerBody::GripPower = 0.1f;// グリップ力.
const float PlayerBody::ColideDecelFac = 0.4f;// 障害物にぶつかったときの減速率.

PlayerBody::PlayerBody()
	:ObjectBase(ObjectTag::Player)
	,rotateNow(false)
{
	velocity = VGet(0, 0, 0);
	// モデル読み込み.
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

	// 3Dモデルのポジション設定.
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

	// 入力があったら加速・ないとき減速.
	if (input)
	{
		// 左右・上下同時押しなどで入力ベクトルが０の時は無視.
		if (VSquareSize(inputVec) < 0.5f)
		{
			return;
		}
		// 方向を正規化
		inputVec = VNorm(inputVec);

		// 入力方向は現在向いている向きと異なるか？.
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
	// 加速処理.
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

	// 止まっている場合は減速しない.
	if (VSize(velocity) > 0)
	{
		// 右か左を押していたらグリップによる減速.
		if (key & PAD_INPUT_RIGHT || key & PAD_INPUT_LEFT)
		{
			accelVec = VAdd(accelVec, VScale(dir, GripDecel));
		}
		// 何も押さなければ減速.
		if (key == 0)
		{
			accelVec = VScale(dir, DefaultDecel);
		}
	}

	// velocity加速計算.
	velocity = VAdd(velocity, accelVec);

	// 反対方向に進む状態になっていたら止める.
	if (VDot(velocity, dir) < 0)
	{
		velocity = VGet(0, 0, 0);
	}
	// 止まっていたら左右移動しない.
	if (VSize(velocity) > 0)
	{
		// velocityの大きさがGRIP_POWERより小さかった場合、Grip_Powerの大きさをvelocityの大きさと同じにする.
		// これによって曲がるときのvelocityが最大でも45°になる. 
		float velSize = VSize(velocity);
		float gripPower = GripPower;
		if (gripPower > velSize)
		{
			gripPower = velSize;
		}

		// 右を押していたら右方向に力をかける.
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

	// 上下方向にいかないようにvelocityを整える.
	velocity = (VGet(velocity.x, 0, velocity.z));

	// ポジション更新.
	pos = VAdd(pos, velocity);

	// 力をかけ終わったvelocityの方向にディレクションを調整.
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
