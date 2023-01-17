#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"

#include "PlayerBody.h"
#include "PlayerCannon.h"
#include "BulletManager.h"
class Player
{
public: 
	//-----------------------------------------------------------------------------
// @brief コンストラクタ
// @param[in] initPos	プレイヤーの初期位置.
// @param[in] inputState DX_INPUT_PAD○○.
//-----------------------------------------------------------------------------
    Player(VECTOR initPos, VECTOR initDir, int& inputState)
    {
		// 車体生成.
		PlayerBody* body = new PlayerBody(initPos, initDir, inputState, ObjectTag::Body);
		ObjectManager::Entry(body);

		// 主砲生成.
		PlayerCannon* cannon = new PlayerCannon(body, inputState, ObjectTag::Body, ObjectTag::Cannon);
		ObjectManager::Entry(cannon);

		BulletManager* bullet = new BulletManager(ObjectTag::Cannon, inputState);
		ObjectManager::Entry(bullet);
    }

private:
};

