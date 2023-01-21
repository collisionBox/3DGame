#include "Bullet.h"
#include "AssetManager.h"
#include "Math.h"
#include "PlayerCannon.h"

const float Bullet::speed = 300.0f;
const float Bullet::DamagePoint = 10.0f;

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

	velocity = initVec;
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
	myTag = userTag;
}


Bullet::~Bullet()
{
	AssetManager::DeleteMesh(modelHandle);

}

void Bullet::Update(float deltaTime)
{
	pos = VAdd(pos, VScale(VScale(dir, speed), deltaTime));

	// 位置の更新.
	MV1SetPosition(modelHandle, pos);
	
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
	
	if (tag != myTag)
	{
		Sphere colModel = other->GetCollisionSphere();
		if (CollisionPair(colSphere, colModel))
		{
			SetAlive(false);

			CollisionUpdate();
		}
	}

	/*if (tag == ObjectTag::Enemy && myTag != ObjectTag::Enemy)
	{
		Sphere collision = other->GetCollisionSphere();
		if (CollisionPair(colSphere, collision))
		{
			SetAlive(false);

			CollisionUpdate();
		}
	}*/
}