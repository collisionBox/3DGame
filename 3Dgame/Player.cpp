#include "Player.h"


//-----------------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param[in] initPos	�v���C���[�̏����ʒu.
// @param[in] inputState DX_INPUT_PAD����.
//-----------------------------------------------------------------------------
Player::Player(VECTOR initPos, VECTOR initDir, int& inputState) :
	ObjectBase(ObjectTag::Player)
{

	// �ԑ̐���.
	PlayerBody* body = new PlayerBody(initPos, initDir, inputState);
	ObjectManager::Entry(body);

	// ��C����.
	PlayerCannon* cannon = new PlayerCannon(body, inputState);
	ObjectManager::Entry(cannon);

	BulletManager* bullet = new BulletManager(inputState);
	ObjectManager::Entry(bullet);
}

void Player::Update(float deltaTime)
{	
}

void Player::Draw()
{
}


