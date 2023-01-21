#include "Bullet.h"
#include "AssetManager.h"
#include "Math.h"
#include "PlayerCannon.h"

const float Bullet::speed = 300.0f;
const float Bullet::DamagePoint = 10.0f;

Bullet::Bullet(ObjectTag tag) :
	ObjectBase(ObjectTag::Bullet)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.08f));// �T�C�Y�̕ύX.

	ObjectBase* cannon = ObjectManager::GetFirstObject(tag);
	if (cannon)
	{
		// �ʒu�E������������.
		//pos = VAdd(cannon->GetPos(), VGet(0.0f, 15.0f, 0.0f));// �C�g�ɍ��킹�邽��.
		pos = cannon->GetPos();
		// �ϐ��̏�����.
		dir = cannon->GetDir();
		dir = VNorm(dir);
	}

	pos.x += dir.x * 58;// �C���擪�ɃZ�b�g���邽��.
	pos.z += dir.z * 58;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = 10.0f;

	velocity = initVec;
}

Bullet::Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag) :
	ObjectBase(ObjectTag::Bullet)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.08f));// �T�C�Y�̕ύX.

	// �ʒu�E������������.
	this->dir = dir;
	this->pos = pos;
	this->pos.x += this->dir.x * 58;// �C���擪�ɃZ�b�g���邽��.
	this->pos.z += this->dir.z * 58;
	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = 10.0f;

	// �ϐ��̏�����.
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

	// �ʒu�̍X�V.
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