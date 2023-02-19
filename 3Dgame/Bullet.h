#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "ObjectTag.h"
class Bullet :
    public ObjectBase
{
public:
    
    Bullet(ObjectTag tag);// �R���X�g���N�^.
    Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag);// �R���X�g���N�^(���C��).
    ~Bullet();// �f�X�g���N�^.
    void Update(float deltaTime);
    void OnCollisionEnter(const ObjectBase* other);// �����蔻�菈��.
    void Draw();


private:
    bool reflectionFlag;// ��x���˂��Ă��邩�ǂ���.
    static const float speed;// �e��.
    VECTOR velocity;// �e���x�N�g��.
    ObjectTag myTag;// �ˌ������^�O��ێ�����^�O.
    static const float DamagePoint;// �_���[�W��.

};

