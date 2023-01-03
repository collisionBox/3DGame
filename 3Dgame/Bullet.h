#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "PlayerCannon.h"
class Bullet :
    public ObjectBase
{
public:

    static Bullet& Instance() { static Bullet bullet; return bullet; }

    Bullet();
    ~Bullet();

    void Initialize(class PlayerCannon* cannon);// 初期化.

    void Update(float deltaTime);
    void Draw();

    void Input();// 入力.

private:
    int duplicateModel;
    static const float speed;

};

