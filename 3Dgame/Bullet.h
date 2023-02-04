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
    bool reflectionFlag;// ˆê“x”½ŽË‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©.
    static const float speed;// ’e‘¬.
    VECTOR velocity;// ’e‘¬ƒxƒNƒgƒ‹.
    ObjectTag myTag;
    static const float DamagePoint;

};

