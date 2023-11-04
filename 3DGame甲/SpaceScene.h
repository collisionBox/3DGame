#pragma once
#include "SceneBase.h"
class SpaceScene :
    public SceneBase
{
public :
    SpaceScene(int stage);
    ~SpaceScene();
    SceneBase* Update(float deltaTime);
    void Draw();
private:
    const float WaitTime = 300.0f;
    int stageNum;
};

