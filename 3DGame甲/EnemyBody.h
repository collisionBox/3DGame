#pragma once
#include "EnemyBodyBase.h"
#include "EnemyCannon.h"
class EnemyBody :
    public ObjectBase
{
public:
    EnemyBody(VECTOR initPos, VECTOR initDir);
    void Initialize();
    void Update(float deltaTime);
    void Draw();
    void OnCollisionEnter(const ObjectBase* other) override;
private:
    void Behavioral1(float deltaTime);
    void Behavioral2(float deltaTime);
    void Rotate(float deltaTIme);
    EnemyCannon* cannon;
    const float ColRadius = 32.0f;// �����蔻�蔼�a.
    VECTOR initPos;
    VECTOR initDir;
    float MaxHP = 1;
    VECTOR velocity;
    float accel;
    const float Accel = 6.0f;// �ʏ�̉���.
    const float Back = 5.0f;// ��ޑ��x.
    const float MaxSpeed = 300.0f;// �ō��O�i���x.
    const float MinSpeed = -200.0f;// �ō���ޑ��x.
    const float DefaultDecel = 0.97f;// �Ȃɂ����Ȃ����̌���.
    bool rotateNow;
    VECTOR aimDir;
    const float Omega = 35.0f;// ���񑬓x(degree).
    float rollingDegree = 40.0f;
};

