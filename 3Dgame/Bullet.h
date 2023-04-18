#pragma once
#include "ObjectBase.h"


class Bullet :
    public ObjectBase
{
public:
    
    Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag);
    ~Bullet();
    void Update(float deltaTime);
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw();


private:
    bool reflectionFlag;// ��x���˂��Ă��邩�ǂ���.
    VECTOR velocity;// �e���x�N�g��.
    ObjectTag myTag;// �g�p�҂̃^�O.
    const float ColRadius = 10.0f;// �����蔻�蔼�a.
    const float BarrelHead = 85.0f;// �C�g��[.
    const float Speed = 800.0f;// �e��.

};

