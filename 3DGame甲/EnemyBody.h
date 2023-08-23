#pragma once
#include "EnemyBodyBase.h"
class EnemyBody :
    public ObjectBase
{
public:
    EnemyBody(VECTOR initPos, VECTOR initDir);
    void Initialize();
    void Update(float deltaTime);
    void Draw();
private:
    const float ColRadius = 32.0f;// “–‚½‚è”»’è”¼Œa.

};

