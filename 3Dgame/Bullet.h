#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
class Bullet :
    public ObjectBase
{
public:

    Bullet(class ObjectBase* cannon);
    ~Bullet();

    void Update(float deltaTime);
    void Draw();


private:
    static const float speed;// 弾速.
    VECTOR velocity;// 弾速ベクトル.
    

};

