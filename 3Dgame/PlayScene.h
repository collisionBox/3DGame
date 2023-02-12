#pragma once
#include "foundation.h"
#include "SceneBase.h"

#include "camera.h"
#include "PlayerBody.h"
#include "EnemyBody.h"
#include "MapManager.h"
class PlayScene :
    public SceneBase
{
public:
    PlayScene();
    ~PlayScene();
    SceneBase* Update(float deltaTime);
    void Draw();
};

