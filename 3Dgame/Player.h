#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"

#include "PlayerBody.h"
#include "PlayerCannon.h"
#include "Bullet.h"
class Player :
    public ObjectBase
{
public: 
    Player();
    ~Player();
    void Update(float deltaTime) override;
    void Draw() override;
private:
    PlayerBody* body;
    PlayerCannon* cannon;
    Bullet* bullet[5];
    const int bulletNum = 5;
    const float shotIntervalTime = 1.0f;
    float shotTime;
};

