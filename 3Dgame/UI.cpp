#include "UI.h"
#include "PlayerBody.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Draw(float deltaTime)
{
	Debug();
}

void UI::Debug()
{
	PlayerBody* player = dynamic_cast<PlayerBody*>(ObjectManager::GetFirstObject(ObjectTag::Player));
	VECTOR pPos = player->GetPos();
	DrawFormatString(0, 0, white,
		"pos:\n%f\n%f\n%f\n\ndir:\n%f\n%f\n%f\n\nvel:\n%f\n%f\n%f\n\nsize:%f\ndot:%f",
		pPos.x, pPos.y, pPos.z,
		player->dir.x, player->dir.y, player->dir.z,
		player->velocity.x, player->velocity.y, player->velocity.z,
		VSize(player->velocity), VDot(player->velocity, player->dir));
}
