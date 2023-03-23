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
    void CheckWinner();// �����҂�����.
    bool IsChangeResultScene();
    bool WaitChangeSceneTime(float deltaTime);
    void PlayerInit();

    PlayerBody* player[2];
    int battleNum;
    const int maxBattleNum = 3;// �ő�ΐ��.
    const int maxWinNum = 2;// �ő叟����.
    const float OnShootingDownWaitTime = 5.0f;// �팂�Ď��ҋ@����.
    float deltaWaitTime;// �ҋ@����.
};

