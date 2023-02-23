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
    Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag);
    ~Bullet();
    void Update(float deltaTime);
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw();


private:
    bool reflectionFlag;// 一度反射しているかどうか.
    VECTOR velocity;// 弾速ベクトル.
    ObjectTag myTag;
    const float speed = 800.0f;// 弾速.
    const float DamagePoint = 20.0f;// ダメージ量.

};

