#include "UI.h"
#include "PlayerCannon.h"

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
	//PlayerBody* player = dynamic_cast<PlayerBody*>(ObjectManager::GetFirstObject(ObjectTag::Player));
	//VECTOR pPos = player->GetPos();
	/*DrawFormatString(0, 0, white,
		"pos:\n%f\n%f\n%f\n\ndir:\n%f\n%f\n%f\n\nvel:\n%f\n%f\n%f\n\nsize:%f\ndot:%f"
		);*/
	PlayerCannon* cannon = dynamic_cast<PlayerCannon*>(ObjectManager::GetFirstObject(ObjectTag::Cannon));
	/*DrawFormatString(0, 0, white, "0:%f\n1:%f\n2:%f", cannon->monitorNum[0], cannon->monitorNum[1],
		cannon->monitorNum[2]);*/
	DrawFormatString(0, 0, white, "%d", GetJoypadNum());
}
