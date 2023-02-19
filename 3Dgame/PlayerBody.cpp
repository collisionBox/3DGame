#include "PlayerBody.h"
// 静的定数.
const float PlayerBody::Accel = 6.0f;
const float PlayerBody::Back = 5.0f;
const float PlayerBody::MaxSpeed = 300.0f;
const float PlayerBody::MinSpeed = -200.0f;
const float PlayerBody::OnShootingDownWaitTime = 5.0f;

PlayerBody::PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, PlayerTag myTag, const char* failName) :
	ObjectBase(ObjectTag::Player)
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
	pos = initPos;// (地面にうまるため13上げる.)今回は無視
	prevPos = pos;
	dir = initDir;
	aimDir = dir;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);


	// 当たり判定球セット.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = 32.0f;

	// 変数の初期化.
	velocity = initVec;
	padInput = inputState;
	HP = 100;
	deltaWaitTime = 0;
	playerTag = myTag;
	// 砲を生成.
	cannon = new PlayerCannon(initPos, initDir, inputState, ObjectTag::Player, failName);
	// HPゲージを生成.
	hpGauge = new HPGauge(HP);

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
	// 画面外へ行かないようにする.
	if (prevPos.x + colSphere.radius > windowSizeXMax ||
		prevPos.x - colSphere.radius < windowSizeXMin ||
		prevPos.z + colSphere.radius > windowSizeZMax ||
		prevPos.z - colSphere.radius < windowSizeZMin)//-885,13,159
	{
		velocity = initVec;
		prevPos = pos;
	}
	// 方向ベクトルに加速力を加えて加速ベクトルとする.
	velocity = VScale(dir, accel);

	// 上下方向にいかないようにvelocityを整える.
	velocity = VGet(velocity.x, 0, velocity.z);

	// 予測ポジション更新.
	prevPos = VAdd(pos, VScale(velocity, deltaTime));

	// ポジション更新.
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
	// 背景と当たった時の処理.
	if (tag == ObjectTag::BackGround)
	{
		int colModel = other->GetCollisionModel();

		MV1_COLL_RESULT_POLY_DIM colInfo;
		if (CollisionPair(colSphere, colModel, colInfo))
		{
			// 当たっている場合は押し量を計算.
			VECTOR poshBuckVec = CalcSpherePushBackVecFromMesh(colSphere, colInfo);
			pos = VAdd(prevPos, poshBuckVec);

			// コリジョン情報の解放.
			MV1CollResultPolyDimTerminate(colInfo);

			if (accel > 0)
			{
				accel = 0;
			}

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
	// 減速後退処理.
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
	// 旋回処理.
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

	if (pad.ThumbLX > 0)// 右旋回.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
	}
	else if (pad.ThumbLX < 0)// 左旋回.
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
	// 正規化.
	dir = VNorm(dir);

	
	
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
