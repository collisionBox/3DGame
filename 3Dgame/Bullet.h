#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "ObjectTag.h"
class Bullet :
    public ObjectBase
{
public:

    Bullet();
    //Bullet(VECTOR pos, VECTOR dir);
    ~Bullet();
    void Update(float deltaTime);
    void Draw();


private:
    static const float speed;// ’e‘¬.
    VECTOR velocity;// ’e‘¬ƒxƒNƒgƒ‹.
   
    static const float DamagePoint;

};

