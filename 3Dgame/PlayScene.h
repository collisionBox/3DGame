#pragma once
#include "SceneBase.h"

#include "camera.h"
#include "PlayerBody.h"
#include "MapManager.h"

class PlayScene :
    public SceneBase
{
public:
    PlayScene(int mapNum);
    ~PlayScene();
    SceneBase* Update(float deltaTime);
    void Draw();
private:
    void CheckWinner();// Ÿ—˜Ò‚ğŒŸõ.
    bool IsChangeResultScene();
    bool WaitChangeSceneTime(float deltaTime);
    void PlayerInit();

    PlayerBody* player[2];
    int battleNum;
    const int maxBattleNum = 3;// Å‘å‘Îí‰ñ”.
    const int maxWinNum = 2;// Å‘åŸ—˜”.
    const float OnShootingDownWaitTime = 5.0f;// ”íŒ‚’Ä‘Ò‹@ŠÔ.
    float deltaWaitTime;// ‘Ò‹@ŠÔ.
};

