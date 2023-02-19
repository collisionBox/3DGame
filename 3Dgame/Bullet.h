#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "ObjectTag.h"
class Bullet :
    public ObjectBase
{
public:
    
    Bullet(ObjectTag tag);// コンストラクタ.
    Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag);// コンストラクタ(メイン).
    ~Bullet();// デストラクタ.
    void Update(float deltaTime);
    void OnCollisionEnter(const ObjectBase* other);// 当たり判定処理.
    void Draw();


private:
    bool reflectionFlag;// 一度反射しているかどうか.
    static const float speed;// 弾速.
    VECTOR velocity;// 弾速ベクトル.
    ObjectTag myTag;// 射撃したタグを保持するタグ.
    static const float DamagePoint;// ダメージ量.

};

