#include "Player2.h"

Player2::Player2(VECTOR initPos, VECTOR initDir, int& inputState)
{
	// 車体生成.
	PlayerBody* body2 = new PlayerBody(initPos, initDir, inputState, ObjectTag::Body2);
	ObjectManager::Entry(body2);

	// 主砲生成.
	PlayerCannon* cannon2 = new PlayerCannon(body2, inputState, ObjectTag::Body2, ObjectTag::Cannon2);
	ObjectManager::Entry(cannon2);

	BulletManager* bullet2 = new BulletManager(ObjectTag::Cannon2, inputState);
	ObjectManager::Entry(bullet2);
}
