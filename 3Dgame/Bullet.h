#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "ObjectTag.h"
class Bullet :
    public ObjectBase
{
public:
    
    Bullet(ObjectTag tag);
    Bullet(VECTOR pos, VECTOR dir);
    ~Bullet();
    void Update(float deltaTime);
    void Draw();


private:
    static const float speed;// 弾速.
    VECTOR velocity;// 弾速ベクトル.
   
    static const float DamagePoint;

};

