#pragma once
#include "ObjectBase.h"


class Bullet :
    public ObjectBase
{
public:
    
    Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag);
    Bullet(ObjectTag userTag);
    ~Bullet();
    void Init();
    void Generate(VECTOR pos, VECTOR dir);
    void Update(float deltaTime);
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw();
    const bool GetPermitUpdate() { return permitUpdate; }
   // void SetPermitUpdate(bool TrueOrFalse) { permitUpdate = TrueOrFalse; }


private:
    bool permitUpdate;// Updateの許可.
    bool reflectionFlag;// 一度反射しているかどうか.
    VECTOR velocity;// 弾速ベクトル.
    ObjectTag myTag;// 使用者のタグ.
    const float ColRadius = 10.0f;// 当たり判定半径.
    const float BarrelHead = 85.0f;// 砲身先端.
    const float Speed = 800.0f;// 弾速.

};

