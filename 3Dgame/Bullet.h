#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "ObjectTag.h"
class Bullet :
    public ObjectBase
{
public:
    
    Bullet(ObjectTag tag);
    Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag);
    ~Bullet();
    void Update(float deltaTime);
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw();


private:
    bool reflectionFlag;// ��x���˂��Ă��邩�ǂ���.
    VECTOR velocity;// �e���x�N�g��.
    ObjectTag myTag;
    const float speed = 800.0f;// �e��.
    const float DamagePoint = 20.0f;// �_���[�W��.

};

