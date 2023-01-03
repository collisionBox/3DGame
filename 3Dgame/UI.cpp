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
	//VECTOR pPos = player->GetPos();
	/*DrawFormatString(0, 0, white,
		"pos:\n%f\n%f\n%f\n\ndir:\n%f\n%f\n%f\n\nvel:\n%f\n%f\n%f\n\nsize:%f\ndot:%f"
		);*/
}
