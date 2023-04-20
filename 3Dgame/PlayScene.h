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
    const VECTOR Player1InitPos = VGet(-742.0f, 0.0f, 335.0f);
    const VECTOR Player1InitDir = VGet(1.0f, 0.0f, -1.0f);
    const VECTOR Player2InitPos = VGet(742.0f, 0.0f, -355.0f);
    const VECTOR Player2InitDir = VGet(-1.0f, 0.0f, 1.0f);

    PlayerBody* player[2];
    int battleNum;
    const int maxBattleNum = 3;// Å‘å‘Îí‰ñ”.
    const int maxWinNum = 2;// Å‘åŸ—˜”.
    const float OnShootingDownWaitTime = 10.0f;// ”íŒ‚’Ä‘Ò‹@ŠÔ.
    float deltaWaitTime;// ‘Ò‹@ŠÔ.
};

