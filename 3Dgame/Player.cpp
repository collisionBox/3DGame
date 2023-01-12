#include "Player.h"


//-----------------------------------------------------------------------------
// @brief コンストラクタ
// @param[in] initPos	プレイヤーの初期位置.
// @param[in] inputState DX_INPUT_PAD○○.
//-----------------------------------------------------------------------------
Player::Player(VECTOR initPos, VECTOR initDir, int& inputState) :
	ObjectBase(ObjectTag::Player)
{

	// 車体生成.
	PlayerBody* body = new PlayerBody(initPos, initDir, inputState);
	ObjectManager::Entry(body);

	// 主砲生成.
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


