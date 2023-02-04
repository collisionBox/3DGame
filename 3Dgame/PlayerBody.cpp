#include "PlayerBody.h"
// 静的定数.
const float PlayerBody::Accel = 6.0f;// 通常の加速.
const float PlayerBody::Back = 5.0f;// 後退速度.
const float PlayerBody::MaxSpeed = 300.0f;// 最高前進速度.
const float PlayerBody::MinSpeed = -200.0f;// 最高後退速度.
const float PlayerBody::DefaultDecel = 0.97f;// なにもしない時の減速.
const float PlayerBody::BreakDecel = 0.5f;// ブレーキ時の減速.
const float PlayerBody::GripDecel = -5.0f;// グリップの減速.
const float PlayerBody::GripPower = 2.0f;// グリップ力.
const float PlayerBody::ColideDecelFac = 4.0f;// 障害物にぶつかったときの減速率.
const float PlayerBody::TurnPerformance = 5.0f;// 旋回性能.
const float PlayerBody::OnShootingDownWaitTime = 5.0f;// 被撃墜時待機時間.

PlayerBody::PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag myTag, const char* failName) :
	ObjectBase(myTag)
	, rotateNow(false)
	, accel()
{
	// アセットマネージャーからモデルをロード.
	string str = "playerBody.mv1";
	modelHandle = AssetManager::GetMesh(failName + str);
	if (modelHandle == -1)
	{
		printfDx("playerBodyを読み込めません");
	}
	MV1SetScale(modelHandle, moveModelScale);

	// 位置・方向を初期化.
	// 左下へ配置.
	pos = initPos;// (地面にうまるため13上げる.)今回は無視
	prevPos = pos;
	// 中心っぽい方向を向く.
	dir = initDir;
	aimDir = dir;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	cannon = new PlayerCannon(initPos, initDir, inputState, myTag, failName);

	// 当たり判定球セット.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = 32.0f;

	// 変数の初期化.
	velocity = initVec;
	padInput = inputState;
	HP = 100;
	hpGauge = new HPGauge(HP);
	deltaWaitTime = 0;
	
}

PlayerBody::~PlayerBody()
{
	AssetManager::DeleteMesh(modelHandle);
}

void PlayerBody::Update(float deltaTime)
{

	//if (HP > 0.0f)
	{
		Input(deltaTime);
	}
	//else
	{
		deltaWaitTime += deltaTime;
		// 爆発エフェクトをいれる.

		if (deltaWaitTime > OnShootingDownWaitTime)// エフェクト再生が終わったらにいつか変更.
		{
			// OVERへシーン遷移.
		}
	}

	if (prevPos.x + colSphere.radius > windowSizeXMax ||
		prevPos.x - colSphere.radius < windowSizeXMin ||
		prevPos.z + colSphere.radius > windowSizeZMax ||
		prevPos.z - colSphere.radius < windowSizeZMin)//-885,13,159
	{
		velocity = initVec;
		prevPos = pos;
	}

	pos = prevPos;
	cannon->Updateeeee(pos, deltaTime);
	hpGauge->Update(pos, HP, deltaTime);
	CollisionUpdate();

	// 3Dモデルのポジション設定.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void PlayerBody::Draw()
{
	MV1DrawModel(modelHandle);

	cannon->Draw();
	hpGauge->Draw();
	DrawCollider();
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

			velocity = initVec;
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
}

void PlayerBody::Input(float deltaTime)
{
	// キー入力取得.
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	GetJoypadXInputState(padInput, &pad);

	// 加速処理.
	if (accel <= MaxSpeed)
	{
		// 上を押していたら加速.
		if (CheckHitKey(KEY_INPUT_UP))
		{
			accel += Accel;
		}
		if (pad.RightTrigger != 0)
		{
			accel += Accel;
		}
	}
	if (accel >= MinSpeed)
	{
		//下を押していたら減速.
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			accel -= Back;
		}
		if (pad.LeftTrigger)
		{
			accel -= Back;
		}
	}
	
	if (CheckHitKey(KEY_INPUT_RIGHT))// 右旋回.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
		//dir = VScale(dir, deltaTime);
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))// 左旋回.
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
	}

	if (pad.ThumbLX > 0)
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
	}
	else if (pad.ThumbLX < 0)
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
	}

	// 自然停止.
	if (!(CheckHitKey(KEY_INPUT_UP)) && !(CheckHitKey(KEY_INPUT_UP)) && pad.LeftTrigger - pad.RightTrigger == 0)
	{
		accel *= DefaultDecel;
		if (abs(VSize(velocity)) <= 8.0f)
		{
			accel = 0;
		}
	}

	// グリップ減速.
	if (key & PAD_INPUT_RIGHT || key & PAD_INPUT_LEFT || pad.ThumbLX != 0)
	{
		if (VSize(velocity) >= 20)
		{
			velocity = VAdd(velocity, VScale(dir, GripDecel));
		}
	}
	dir = VNorm(dir);// 正規化.

	velocity = VScale(dir, accel);// 方向ベクトルに加速力を加えて加速ベクトルとする.
	
	// 上下方向にいかないようにvelocityを整える.
	velocity = VGet(velocity.x, 0, velocity.z);

	// ポジション更新.
	prevPos = VAdd(pos, VScale(velocity, deltaTime));
	
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
