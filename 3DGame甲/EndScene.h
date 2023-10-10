#pragma once
#include "SceneBase.h"
#include "DxLib.h"
#include <string>
class EndScene :
    public SceneBase
{
public:
    EndScene(int winnerNum);
    ~EndScene();
    SceneBase* Update(float deltaTime);
    void Draw();

private:
    float alpha;
    float addition = 1;
    int winnerNum;
    int fontHandle;
    const int fontSize = 60;// ‘å‚«‚³.
    const int fontThick = 3;// ‘¾‚³.

    const float  TransitionWaitingTime = 15.0f;// ‘JˆÚ‘Ò‹@ŽžŠÔ.
    float timer;
    const std::string Str = "Rematch with any key or pad any button";
    const std::string Str2 = "Exit with Esc button";
    const int str2Pos = 50;
};

