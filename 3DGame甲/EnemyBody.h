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
private:
    EnemyCannon* cannon;
    const float ColRadius = 32.0f;// �����蔻�蔼�a.
    VECTOR initPos;
    VECTOR initDir;
    float MaxHP = 1;

};

