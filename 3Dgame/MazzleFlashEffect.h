#pragma once
#include "SystemConstant.h"
#include "EffekseerForDXLib.h"
#include "EffectBase.h"

class MazzleFlashEffect :
    public EffectBase
{
public:
    MazzleFlashEffect(VECTOR pos, VECTOR dir);
    ~MazzleFlashEffect();
    void Update(float deltaTime);
    void Draw();
private:
    const float barrelHead = 90.0f;// ñCêgêÊí[.
    VECTOR pos;
    VECTOR dir;
    int playingEffectHandle;
};

