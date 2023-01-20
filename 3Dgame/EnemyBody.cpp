#include "EnemyBody.h"

// 静的定数.
const float EnemyBody::Accel = 6.0f;// 通常の加速.
const float EnemyBody::Back = 5.0f;// 後退速度.
const float EnemyBody::MaxSpeed = 200.0f;// 最高前進速度.
const float EnemyBody::MinSpeed = -350.0f;// 最高後退速度.
const float EnemyBody::DefaultDecel = 0.97f;// なにもしない時の減速.
const float EnemyBody::BreakDecel = 0.5f;// ブレーキ時の減速.
const float EnemyBody::GripDecel = -5.0f;// グリップの減速.
const float EnemyBody::GripPower = 2.0f;// グリップ力.
const float EnemyBody::ColideDecelFac = 4.0f;// 障害物にぶつかったときの減速率.
const float EnemyBody::TurnPerformance = 5.0f;// 旋回性能.

EnemyBody::EnemyBody(VECTOR initPos, VECTOR initDir):
	ObjectBase(ObjectTag::Enemy)
{
	// アセットマネージャーからモデルをロード.
	modelHandle = AssetManager::GetMesh("data/enemy/enemyBody.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));

	cannon = new EnemyCannon(initPos, initDir);

	// 位置・方向を初期化.
	// 左下へ配置.
	pos = initPos;// (地面にうまるため13上げる.)今回は無視
	// 中心を向く.
	dir = initDir;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// 当たり判定球セット.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.worldCenter.y = 0;
	colSphere.radius = 32.0f;

	// 変数の初期化.
	velocity = initVec;
	rotateNow = false;
	accel = 0;
	time = 4;
}

EnemyBody::~EnemyBody()
{
	AssetManager::DeleteMesh(modelHandle);
	delete cannon;
}

void EnemyBody::Update(float deltaTime)
{
	/*if (VDot(velocity, dir) <= MaxSpeed)
	{
		accel += Accel;
	}*/

	time -= deltaTime;
	if (time < 0 && !rotateNow)
	{
		time = 3;
		rotateNow = true;
		aimDir = VScale(dir, -1);
	}

	Rotate(10);

	dir = VNorm(dir);// 正規化.

	velocity = VScale(dir, accel);
	// 上下方向にいかないようにvelocityを整える.
	velocity = VGet(velocity.x, 0, velocity.z);

	// ポジション更新.
	pos = VAdd(pos, VScale(velocity, deltaTime));

	// 3Dモデルのポジション設定.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	
	cannon->Updateeeee(pos, deltaTime);

	CollisionUpdate();
}



void EnemyBody::Draw()
{
	MV1DrawModel(modelHandle);
	cannon->Draw();
	DrawCollider();

}

void EnemyBody::OnCollisionEnter(const ObjectBase* other)
{

}

void EnemyBody::Rotate(float degree)
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
			interPolateDir = RotateForAimVecYAxis(dir, aimDir, degree);

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
