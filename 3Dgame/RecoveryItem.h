#pragma once
#include "ObjectBase.h"
class RecoveryItem :
    public ObjectBase
{
public:
    RecoveryItem();
    ~RecoveryItem();

    void Update(float deltaTime);
    void Draw();
    void OnCollisionEnter(const ObjectBase* other);
private:
    
};

