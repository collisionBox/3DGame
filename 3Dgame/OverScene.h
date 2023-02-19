#pragma once
#include "foundation.h"
#include "SceneBase.h"
#include "PlayScene.h"
class OverScene :
    public SceneBase
{
    SceneBase* Update(float deltaTime);
    void Draw();
};

