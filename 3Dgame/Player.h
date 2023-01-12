#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"

#include "PlayerBody.h"
#include "PlayerCannon.h"
#include "BulletManager.h"
class Player :
    public ObjectBase
{
public: 
    Player(VECTOR initPos, VECTOR initDir, int& inputState);
    void Update(float deltaTime) override;
    void Draw() override;

private:
};

