#include "Bullet.h"
#include "AssetManager.h"
#include "Math.h"
#include "PlayerCannon.h"

const float Bullet::speed = 300.0f;
const float Bullet::DamagePoint = 20.0f;

Bullet::Bullet(ObjectTag tag) :
	ObjectBase(ObjectTag::Bullet)
{
	// アセットマネージャーからモデルをロード.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.08f));// サイズの変更.

	ObjectBase* cannon = ObjectManager::GetFirstObject(tag);
	if (cannon)
	{
		// 位置・方向を初期化.
		//pos = VAdd(cannon->GetPos(), VGet(0.0f, 15.0f, 0.0f));// 砲身に合わせるため.
		pos = cannon->GetPos();
		// 変数の初期化.
		dir = cannon->GetDir();
		dir = VNorm(dir);
	}

	pos.x += dir.x * 58;// 砲塔先頭にセットするため.
	pos.z += dir.z * 58;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// 当たり判定球セット.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = 10.0f;

	// 変数の初期化.
	velocity = initVec;
	reflectionFlag = false;
}

Bullet::Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag) :
	ObjectBase(ObjectTag::Bullet)
{
	// アセットマネージャーからモデルをロード.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.08f));// サイズの変更.

	// 位置・方向を初期化.
	this->dir = dir;
	this->pos = pos;
	this->pos.x += this->dir.x * 58;// 砲塔先頭にセットするため.
	this->pos.z += this->dir.z * 58;
	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// 当たり判定球セット.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = 10.0f;

	// 変数の初期化.
	velocity = initVec;
	reflectionFlag = false;
	myTag = userTag;
}

Bullet::~Bullet()
{
	AssetManager::DeleteMesh(modelHandle);

}

void Bullet::Update(float deltaTime)
{
	velocity = VScale(VScale(dir, speed), deltaTime);
	pos = VAdd(pos, velocity);

	// 位置の更新.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	CollisionUpdate();
}


void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
	DrawCollider();
	
}

void Bullet::OnCollisionEnter(const ObjectBase* other)
{
	ObjectTag tag = other->GetTag();
	if (tag == ObjectTag::BackGround)
	{
		int colModel = other->GetCollisionModel();

		MV1_COLL_RESULT_POLY_DIM colInfo;
		if (CollisionPair(colSphere, colModel, colInfo))
		{
			if (reflectionFlag)
			{
				SetAlive(false);
			}
			else
			{
				// 当たっている場合は押し量を計算.
				VECTOR poshBuckVec = CalcSpherePushBackVecFromMesh(colSphere, colInfo);
				pos = VAdd(pos, poshBuckVec);

				VECTOR planeNormal;                    // ポリゴン平面法線
				for (int i = 0; i < colInfo.HitNum; ++i)
				{
					// 衝突ポリゴンの辺 
					VECTOR edge1, edge2;
					edge1 = colInfo.Dim[i].Position[1] - colInfo.Dim[i].Position[0];
					edge2 = colInfo.Dim[i].Position[2] - colInfo.Dim[i].Position[0];
					// 衝突ポリゴンの辺より、ポリゴン面の法線ベクトルを求める
					planeNormal = VCross(edge1, edge2);
					planeNormal = VNorm(planeNormal);
					if (planeNormal.x == 1 || planeNormal.z == 1)
					{
						break;
					}
				}
				float a = VDot(VScale(velocity, -1.0f), planeNormal);
				VECTOR b = VScale(planeNormal, 2.0f * a);
				dir = VAdd(velocity, b);
				dir = VNorm(dir);

				// コリジョン情報の解放.
				MV1CollResultPolyDimTerminate(colInfo);
				CollisionUpdate();
				reflectionFlag = true;
			}
		}
	}


}