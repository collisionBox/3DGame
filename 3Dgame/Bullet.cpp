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
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.15f));// �T�C�Y�̕ύX.

	ObjectBase* cannon = ObjectManager::GetFirstObject(tag);
	if (cannon)
	{
		// �ʒu�E������������.
		pos = VAdd(cannon->GetPos(), VGet(0.0f, 15.0f, 0.0f));// �C�g�ɍ��킹�邽��.

		// �ϐ��̏�����.
		dir = cannon->GetDir();
		dir = VNorm(dir);
	}

	//pos.x = dir.x * 58;// �C���擪�ɃZ�b�g���邽��.
	//pos.z = dir.z * 58;
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	velocity = initVec;
}

Bullet::Bullet(VECTOR pos, VECTOR dir) :
	ObjectBase(ObjectTag::Bullet)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.15f));// �T�C�Y�̕ύX.

	visible = false;
	// �ʒu�E������������.
	this->pos = VAdd(pos, VGet(0.0f, 15.0f, 0.0f));// �C�g�ɍ��킹�邽��.

	// �ϐ��̏�����.
	this->dir = dir;
	this->dir = VNorm(this->dir);
	this->pos.x = this->dir.x * 58;// �C���擪�ɃZ�b�g���邽��.
	this->pos.z = this->dir.z * 58;
	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	velocity = initVec;

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
	
}

void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
	
}
