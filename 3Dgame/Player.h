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
// @brief �R���X�g���N�^
// @param[in] initPos	�v���C���[�̏����ʒu.
// @param[in] inputState DX_INPUT_PAD����.
//-----------------------------------------------------------------------------
    Player(VECTOR initPos, VECTOR initDir, int& inputState)
    {
		// �ԑ̐���.
		PlayerBody* body = new PlayerBody(initPos, initDir, inputState, ObjectTag::Body);
		ObjectManager::Entry(body);

		// ��C����.
		PlayerCannon* cannon = new PlayerCannon(body, inputState, ObjectTag::Body, ObjectTag::Cannon);
		ObjectManager::Entry(cannon);

		BulletManager* bullet = new BulletManager(ObjectTag::Cannon, inputState);
		ObjectManager::Entry(bullet);
    }

private:
};

