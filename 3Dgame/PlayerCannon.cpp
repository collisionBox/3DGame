#include "PlayerCannon.h"

const float PlayerCannon::TurnPerformance = 3.50f;

#if 0
PlayerCannon::PlayerCannon() :
	modelHandle(-1)
{
	modelHandle = AssetManager::GetMesh("data/player/reconTankCannon.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));
	
}
#else
PlayerCannon::PlayerCannon(PlayerBody* body, int inputState, ObjectTag userTag, ObjectTag myTag) :
	ObjectBase(myTag)
{

	// アセットマネージャーからモデルをロード.
	modelHandle = AssetManager::GetMesh("data/player/reconTankCannon.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));

	//if (body)
	{
		// 位置・方向を初期化.
		pos = body->GetPos();
		pos.y = 0.5f;
		dir = body->GetDir();
		MV1SetPosition(modelHandle, pos);
		MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	}
	

	// 変数の初期化.
	dirVec = initVec;
	rotateNow = false;
	padInput = inputState;
	tag = userTag;
}

PlayerCannon::PlayerCannon(VECTOR pos, VECTOR dir, int inputState, ObjectTag myTag) :
	ObjectBase(myTag)
{
	// アセットマネージャーからモデルをロード.
	modelHandle = AssetManager::GetMesh("data/player/reconTankCannon.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));

	// 位置・方向を初期化.
	this->pos = pos;
	this->pos.y = 0.5f;
	this->dir = dir;
	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// 変数の初期化.
	dirVec = initVec;
	rotateNow = false;
	padInput = inputState;
}
#endif
PlayerCannon::~PlayerCannon()
{
	AssetManager::DeleteMesh(modelHandle);
}


#if 1
void PlayerCannon::Update(float deltaTime)
{
	Input(deltaTime);
	Rotate();
	ObjectBase* body = ObjectManager::GetFirstObject(tag);
	
	//VECTOR cameraFront = camDir;
	//cameraFront.y = 0.0f;
	/*if (GetRightDir(cameraFront))
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		
		dir = VAdd(dir, VScale(right, 0.1));
	}
	else
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, 0.3));
	}*/
	//dir = cameraFront;
	dir = VNorm(dir);

	pos = body->GetPos();
	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}
#else
void PlayerCannon::Update(float deltaTime)
{
	ObjectBase* camera = ObjectManager::GetFirstObject(ObjectTag::Camera);
	ObjectBase* body = ObjectManager::GetFirstObject(ObjectTag::Body);
	VECTOR cameraDir = camera->GetDir();

	if (VDot(dir, cameraDir) > 0.99f)
	{
		float rotRadianSpeed = ToRadian(10) * deltaTime;// 角速度.
		// 左なら角速度を負に.
		if (VCross(dir, cameraDir).y < 0.0f)
		{
			rotRadianSpeed *= -1;
		}
		// Y軸回転行列を作成.
		MATRIX rotMat = MGetRotY(rotRadianSpeed);

		// 回転させる.
		VECTOR rotVec = VTransform(dir, rotMat);

		//目標角を超えていないか.
		VECTOR cross1, cross2;
		cross1 = VCross(dir, cameraDir);
		cross2 = VCross(rotVec, cameraDir);

		// 目標角度を超えたら終了.
		if (cross1.y * cross2.y < 0.01f)
		{
			rotVec = cameraDir;
		}
		rotVec.y = 0.0f;// 補正.
		rotVec = VNorm(rotVec);

		// 更新.
		dir = rotVec;
	}

	pos = body->GetPos();
	// 変更を反映.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	monitorNum[0] = VDot(dir,cameraDir);
	
}

#endif
void PlayerCannon::Draw()
{
	MV1DrawModel(modelHandle);
	
}

void PlayerCannon::Input(float deltaTime)
{
	GetJoypadXInputState(padInput, &pad);
	if (CheckHitKey(KEY_INPUT_A))
	{

		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
	}
	VECTOR padVec = VGet(pad.ThumbRX, 0.0f, pad.ThumbRY);
	
	if (VectorSize(padVec) != 0.0f)
	{
		padVec = VNorm(padVec);
		if (IsNearAngle(padVec, dir))
		{
			dir = padVec;
		}
		else
		{
			rotateNow = true;
			aimDir = padVec;
		}
	}
	
}

void PlayerCannon::Rotate()
{
	if (rotateNow)
	{

		if (IsNearAngle(aimDir, dir))
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


