#pragma once
#include "SceneBase.h"

#include "camera.h"
#include "PlayerBody.h"
#include "BreakExplosion.h"

#include "MapManager.h"
#include <string>
class PlayScene :
    public SceneBase
{
public:
    PlayScene(int mapNum);
    ~PlayScene();
    SceneBase* Update(float deltaTime);
    void Draw();
private:
    void CheckWinner();// �����҂����.
    bool IsChangeResultScene();
    bool WaitChangeSceneTime(float deltaTime);
    void PlayerInit();
    const VECTOR Player1InitPos = VGet(-742.0f, 0.0f, 335.0f);
    const VECTOR Player1InitDir = VGet(1.0f, 0.0f, -1.0f);
    const VECTOR Player2InitPos = VGet(742.0f, 0.0f, -355.0f);
    const VECTOR Player2InitDir = VGet(-1.0f, 0.0f, 1.0f);
    
    PlayerBody* player[2];
    BreakExplosion* breakEffect[2];
    bool check;
    int battleNum;
    bool permission2Proceed;// �i�s����.
    const int maxBattleNum = 3;// �ő�ΐ��.
    const int maxWinNum = 2;// �ő叟����.
    const float OnShootingDownWaitTime = 10.0f;// �팂�Ď��ҋ@����.
    const float WaitingTimeBeforStart = 3.0f;// �J�n�O�ҋ@����.
    float deltaWaitTime;// �ҋ@����.
    int loserNum;
    const int WaitTime = 900;
    std::string str;
    const float StringDrawTime = 2.0f;// ������`�悵�Ă�������.
    int fontHandle;
    const int fontSize = 60;// �傫
    const int fontThick = 3;// ����.
};

