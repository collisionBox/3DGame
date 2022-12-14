#include "PlayerBody.h"
#include "PlayerCannon.h"
// 静的定数.
const float PlayerBody::Accel = 6.0f;// 通常の加速.
const float PlayerBody::Back = 5.0f;// 後退速度.
const float PlayerBody::MaxSpeed = 200.0f;// 最高前進速度.
const float PlayerBody::MinSpeed = -350.0f;// 最高後退速度.
const float PlayerBody::DefaultDecel = 0.97f;// なにもしない時の減速.
const float PlayerBody::BreakDecel = 0.5f;// ブレーキ時の減速.
const float PlayerBody::GripDecel = -5.0f;// グリップの減速.
const float PlayerBody::GripPower = 2.0f;// グリップ力.
const float PlayerBody::ColideDecelFac = 4.0f;// 障害物にぶつかったときの減速率.
const float PlayerBody::TurnPerformance = 5.0f;// 旋回性能.

PlayerBody::PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag myTag) :
	ObjectBase(myTag)
	, rotateNow(false)
	, accel()
{
	// アセットマネージャーからモデルをロード.
	modelHandle = AssetManager::GetMesh("data/player/reconTankBody.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));
	
	// 位置・方向を初期化.
	// 左下へ配置.
	pos = initPos;// (地面にうまるため13上げる.)今回は無視
	// 中心を向く.
	dir = initDir;
	aimDir = dir;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// 変数の初期化.
	velocity = initVec;
	padInput = inputState;
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

	if (pos.x > 930.0f)//-885,13,159
	{
		pos = VGet(-920.0f, pos.y, pos.z);//920
	}
	if (pos.x < -930.0f)//882,13,88
	{
		pos = VGet(920.0f, pos.y, pos.z);
	}
	if (pos.z > 540)//540
	{
		pos = VGet(pos.x, pos.y, -530.0f);
	}
	if (pos.z < -540)//540
	{
		pos = VGet(pos.x, pos.y, 530.0f);
	}
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
		int colModel = other->GetCollisionModel();

		MV1_COLL_RESULT_POLY_DIM colInfo;
		if (CollisionPair(colSphere, colModel, colInfo))
		{
			// 当たっている場合は押し量を計算.
			VECTOR poshBuckVec = CalcSpherePushBackVecFromMesh(colSphere, colInfo);
			pos = VAdd(pos, poshBuckVec);
			// コリジョン情報の解放.
			MV1CollResultPolyDimTerminate(colInfo);

			CollisionUpdate();
		}

		// 背景と足元線分当たり判定.
		MV1_COLL_RESULT_POLY colInfoLine;
		if (CollisionPair(colLine, colModel, colInfoLine))
		{
			// 当たっている場合は足元を衝突店に合わせる.
			pos = colInfoLine.HitPosition;

			CollisionUpdate();
		}
	}
	if (tag == ObjectTag::Bullet)
	{

	}
}

void PlayerBody::Input(float deltaTime)
{
	// キー入力取得.
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	GetJoypadXInputState(padInput, &pad);
	const VECTOR accelDir = VGet(0.0f,1.0f,0.0f);
	const VECTOR backDir = VScale(dir, -1);
	// 入力許可フラグ.
	bool input = false;

	// 加速処理.
	float dot = VDot(velocity, dir);// 内積.
	if (dot <= MaxSpeed)
	{
		// 上を押していたら加速.
		if (key & PAD_INPUT_UP || pad.RightTrigger != 0)
		{
			accel += Accel;
		}

	}
	if (dot >= MinSpeed)
	{
		//下を押していたら減速.
		if (key & PAD_INPUT_DOWN || pad.LeftTrigger)
		{
			accel -= Back;
		}
	}
	// 自然停止.
	if(!(key & PAD_INPUT_UP) && !(key & PAD_INPUT_DOWN) && pad.LeftTrigger - pad.RightTrigger == 0)
	{
		accel *= DefaultDecel;
		if (VSize(velocity) <= 8.0f)
		{
			accel = 0;
		}
		if (accel <= 0.1f)
		{
			accel = 0;
		}
	}
	
	if (key & PAD_INPUT_RIGHT && !(key & PAD_INPUT_LEFT) || pad.ThumbLX > 0)// 右旋回.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
		//dir = VScale(dir, deltaTime);
	}
	else if (key & PAD_INPUT_LEFT && !(key & PAD_INPUT_RIGHT) || pad.ThumbLX < 0)// 左旋回.
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
		//dir = VScale(dir, deltaTime);
	}
	// グリップ減速.
	if (key & PAD_INPUT_RIGHT || key & PAD_INPUT_LEFT || pad.ThumbLX)
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
	pos = VAdd(pos, VScale(velocity, deltaTime));
	
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
