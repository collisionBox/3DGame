#pragma once
#include "SceneBase.h"

#include "camera.h"
#include "PlayerBody.h"
#include "EnemyBody.h"
#include "MapManager.h"
#include <string>
#include "SystemConstant.h"
class PlayScene :
    public SceneBase
{
public:
    PlayScene(int mapNum);
    PlayScene(bool mode, int mapNum);
    ~PlayScene();
    SceneBase* Update(float deltaTime);
    void Draw();
private:
    void CheckWinner();// 勝利者を検索.
    bool IsChangeResultScene();
    bool WaitChangeSceneTime(float deltaTime);
    void PlayerInit();
    const VECTOR Player1InitPos = VGet(-742.0f, 0.0f, 335.0f);
    const VECTOR Player1InitDir = VGet(1.0f, 0.0f, -1.0f);
    const VECTOR Player2InitPos = VGet(742.0f, 0.0f, -355.0f);
    const VECTOR Player2InitDir = VGet(1.0f, 0.0f, -1.0f);
    const VECTOR LookLeft = VGet(-1.0f, 0.0f, 0.0f);
    const VECTOR LookRight = VGet(1.0f, 0.0f, 0.0f);
    int imgHandle;
    PlayerBody* player[PlayerNum];
    EnemyBody* enemy;
    int battleNum;
    const int maxBattleNum = 3;// 最大対戦回数.
    const int maxWinNum = 2;// 最大勝利数.
    const float OnShootingDownWaitTime = 10.0f;// 被撃墜時待機時間.
    const float WaitingTimeBeforStart = 3.0f;// 開始前待機時間.
    float deltaWaitTime;// 待機時間.
    int winnerNum;
    const int WaitTime = 900;
    std::string str;
    const float StringDrawTime = 2.0f;// 文字を描画しておく時間.
    int fontHandle;
    const int fontSize = 60;// 大き
    const int fontThick = 3;// 太さ.
};

