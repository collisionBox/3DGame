#include "PlayerCannon.h"



#if 0
#else
PlayerCannon::PlayerCannon(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag userTag, const char* failName) :
	ObjectBase(ObjectTag::Cannon)
{

	// アセットマネージャーからモデルをロード.
	string str = "playerCannon.mv1";
	modelHandle = AssetManager::GetMesh(failName + str);
	MV1SetScale(modelHandle, moveModelScale);

	
	
	// 位置・方向を初期化.
	pos = initPos;
	pos.y = 0.5f;
	dir = initDir;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	
	bulletManager = new BulletManager(userTag, inputState);

	// 変数の初期化.
	aimDir = initVec;
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
	// 引数にdeltaTime以外のものも使いたいから不使用.
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
void PlayerCannon::Updateeeee(VECTOR bodyPos, float deltaTime)
{
	Input(deltaTime);
	Rotate();
	dir = VNorm(dir);
	pos = bodyPos;

	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	bulletManager->Update(pos, dir, deltaTime);


}
void PlayerCannon::Draw()
{
	MV1DrawModel(modelHandle);
	
}

void PlayerCannon::Input(float deltaTime)
{
	// キーボード入力.
	if (CheckHitKey(KEY_INPUT_A))// 右.
	{

		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
	}
	if (CheckHitKey(KEY_INPUT_D))// 左.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
	}

	// ジョイパッド入力.
	GetJoypadXInputState(padInput, &pad);
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


