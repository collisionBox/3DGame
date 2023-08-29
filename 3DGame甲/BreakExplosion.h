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
private:

};

