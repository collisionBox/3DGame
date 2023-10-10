#pragma once
#include "EffectBase.h"
class BreakExplosion :
    public EffectBase
{
public:
    BreakExplosion(VECTOR pos, VECTOR dir);
    ~BreakExplosion();
    void Update(float deltaTime);

    void Play();
    const bool IsFinish() { return finish; }
private:
    const float Size = 10.0f;
    const float PlayEffectSpeed = 1.0f;
    bool finish;
};

