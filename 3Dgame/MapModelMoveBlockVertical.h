#pragma once
#include "foundation.h"
class MapModelMoveBlockVertical :
    public ObjectBase
{
public:
    MapModelMoveBlockVertical(VECTOR initPos);
    ~MapModelMoveBlockVertical();
    void Update(float deltaTime);
    void Draw();
private:
    const float adjust = 50.0f;
    const float moveSpeed = 80.0f;
    VECTOR velocity;
    const float waitTime = 2.0f;
    float deltaWaitTime;// ‘Ò‹@ŽžŠÔ.
    int selectDirection;// •ûŒü‘I‘ð.
};

