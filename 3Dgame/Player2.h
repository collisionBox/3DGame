#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"

#include "PlayerBody.h"
#include "PlayerCannon.h"
#include "BulletManager.h"
class Player2
{
public:
	Player2(VECTOR initPos, VECTOR initDir, int& inputState)
	{
		//// �ԑ̐���.
		//PlayerBody* body2 = new PlayerBody(initPos, initDir, inputState, ObjectTag::Body2);
		//ObjectManager::Entry(body2);

		//// ��C����.
		//PlayerCannon* cannon2 = new PlayerCannon(body2, inputState, ObjectTag::Body2, ObjectTag::Cannon2);
		//ObjectManager::Entry(cannon2);

		//BulletManager* bullet2 = new BulletManager(ObjectTag::Cannon2, inputState);
		//ObjectManager::Entry(bullet2);
	}


};

